/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2021 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#ifndef SRSRAN_SCHED_NR_SIM_UE_H
#define SRSRAN_SCHED_NR_SIM_UE_H

#include "srsenb/test/mac/sched_sim_ue.h"
#include "srsgnb/hdr/stack/mac/sched_nr.h"
#include "srsran/adt/circular_array.h"
#include "srsran/common/test_common.h"
#include <condition_variable>
#include <semaphore.h>

namespace srsran {
class task_worker;
}

namespace srsenb {

const static uint32_t MAX_GRANTS = mac_interface_phy_nr::MAX_GRANTS;

struct ue_nr_harq_ctxt_t {
  bool                  active    = false;
  bool                  ndi       = false;
  uint32_t              pid       = 0;
  uint32_t              nof_txs   = 0;
  uint32_t              nof_retxs = std::numeric_limits<uint32_t>::max();
  uint32_t              riv       = 0;
  srsran_dci_location_t dci_loc   = {};
  uint32_t              tbs       = 0;
  slot_point            last_slot_tx, first_slot_tx, last_slot_ack;
};
struct sched_nr_cc_result_view {
  slot_point                          slot;
  uint32_t                            cc = 0;
  const sched_nr_interface::dl_res_t* dl = nullptr;
  const sched_nr_interface::ul_res_t* ul = nullptr;
};

struct ue_nr_cc_ctxt_t {
  std::array<ue_nr_harq_ctxt_t, SCHED_NR_MAX_HARQ> dl_harqs;
  std::array<ue_nr_harq_ctxt_t, SCHED_NR_MAX_HARQ> ul_harqs;
  srsran::circular_array<uint32_t, TTIMOD_SZ>      pending_acks;
};

struct ue_nr_slot_events {
  struct ack_t {
    uint32_t pid;
    bool     ack;
  };
  struct cc_data {
    bool                                      configured = false;
    srsran::bounded_vector<ack_t, MAX_GRANTS> dl_acks;
    srsran::bounded_vector<ack_t, MAX_GRANTS> ul_acks;
  };
  slot_point           slot_rx;
  std::vector<cc_data> cc_list;
};

struct sim_nr_ue_ctxt_t {
  uint16_t                     rnti;
  uint32_t                     preamble_idx;
  slot_point                   prach_slot_rx;
  sched_nr_interface::ue_cfg_t ue_cfg;
  std::vector<ue_nr_cc_ctxt_t> cc_list;

  bool is_last_dl_retx(uint32_t ue_cc_idx, uint32_t pid) const
  {
    auto& h = cc_list.at(ue_cc_idx).dl_harqs[pid];
    return h.nof_retxs + 1 >= ue_cfg.maxharq_tx;
  }
};
struct sim_nr_enb_ctxt_t {
  srsran::span<const sched_nr_impl::cell_params_t> cell_params;
  std::map<uint16_t, const sim_nr_ue_ctxt_t*>      ue_db;
};

class sched_nr_ue_sim
{
public:
  sched_nr_ue_sim(uint16_t                            rnti_,
                  const sched_nr_interface::ue_cfg_t& ue_cfg_,
                  slot_point                          prach_slot_rx,
                  uint32_t                            preamble_idx);

  int update(const sched_nr_cc_result_view& cc_out);

  const sim_nr_ue_ctxt_t& get_ctxt() const { return ctxt; }
  sim_nr_ue_ctxt_t&       get_ctxt() { return ctxt; }

private:
  void update_dl_harqs(const sched_nr_cc_result_view& sf_out);

  srslog::basic_logger& logger;
  sim_nr_ue_ctxt_t      ctxt;
};

/// Implementation of features common to parallel and sequential sched nr testers
class sched_nr_base_tester
{
public:
  struct cc_result_t {
    sched_nr_cc_result_view  res;
    std::chrono::nanoseconds cc_latency_ns;
  };

  sched_nr_base_tester(const sched_nr_interface::sched_args_t&            sched_args,
                       const std::vector<sched_nr_interface::cell_cfg_t>& cell_params_,
                       std::string                                        test_name,
                       uint32_t                                           nof_workers = 1);
  virtual ~sched_nr_base_tester();

  void run_slot(slot_point slot_tx);
  void stop();

  slot_point get_slot_tx() const { return current_slot_tx; }

  int add_user(uint16_t rnti, const sched_nr_interface::ue_cfg_t& ue_cfg_, slot_point tti_rx, uint32_t preamble_idx);

  void user_cfg(uint16_t rnti, const sched_nr_interface::ue_cfg_t& ue_cfg_);

  srsran::const_span<sched_nr_impl::cell_params_t> get_cell_params() { return cell_params; }

  // configurable by simulator concrete implementation
  virtual void set_external_slot_events(const sim_nr_ue_ctxt_t& ue_ctxt, ue_nr_slot_events& pending_events) {}

  // configurable by simulator concrete implementation
  virtual void process_slot_result(const sim_nr_enb_ctxt_t& enb_ctxt, srsran::const_span<cc_result_t> cc_out) {}

protected:
  void              generate_cc_result(uint32_t cc);
  sim_nr_enb_ctxt_t get_enb_ctxt() const;

  int set_default_slot_events(const sim_nr_ue_ctxt_t& ue_ctxt, ue_nr_slot_events& pending_events);
  int apply_slot_events(sim_nr_ue_ctxt_t& ue_ctxt, const ue_nr_slot_events& events);

  /// Runs general tests to verify result consistency, and updates UE state
  void process_results();

  std::unique_ptr<srsran::test_delimit_logger> test_delimiter;
  srslog::basic_logger&                        logger;
  srslog::basic_logger&                        mac_logger;
  std::unique_ptr<sched_nr>                    sched_ptr;
  std::vector<sched_nr_impl::cell_params_t>    cell_params;

  std::vector<std::unique_ptr<srsran::task_worker> > cc_workers;

  std::map<uint16_t, sched_nr_ue_sim> ue_db;

  // slot-specific
  slot_point                            current_slot_tx;
  std::chrono::steady_clock::time_point slot_start_tp;
  sim_nr_enb_ctxt_t                     slot_ctxt;
  std::vector<cc_result_t>              cc_results;

  std::atomic<bool>     stopped{false};
  mutable sem_t         slot_sem;
  std::atomic<uint32_t> nof_cc_remaining{0};
};

} // namespace srsenb

#endif // SRSRAN_SCHED_NR_SIM_UE_H
