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

#ifndef SRSUE_LTE_SF_WORKER_H
#define SRSUE_LTE_SF_WORKER_H

#include "cc_worker.h"
#include "srsran/common/thread_pool.h"
#include "srsran/srsran.h"
#include "srsue/hdr/phy/phy_common.h"
#include <string.h>

namespace srsue {
namespace lte {

/**
 * The sf_worker class handles the PHY processing, UL and DL procedures associated with 1 subframe.
 * It contains multiple cc_worker objects, one for each component carrier which may be executed in
 * one or multiple threads.
 *
 * A sf_worker object is executed by a thread within the thread_pool.
 */

class sf_worker : public srsran::thread_pool::worker
{
public:
  sf_worker(uint32_t max_prb, phy_common* phy_, srslog::basic_logger& logger);
  virtual ~sf_worker();

  void reset_cell_unlocked(uint32_t cc_idx);
  bool set_cell_unlocked(uint32_t cc_idx, srsran_cell_t cell_);

  /* Functions used by main PHY thread */
  cf_t*    get_buffer(uint32_t cc_idx, uint32_t antenna_idx);
  uint32_t get_buffer_len();
  void     set_tti(uint32_t tti);
  void     set_tx_time(const srsran::rf_timestamp_t& tx_time);
  void     set_prach(cf_t* prach_ptr, float prach_power);
  void     set_cfo_unlocked(const uint32_t& cc_idx, float cfo);

  void set_tdd_config_unlocked(srsran_tdd_config_t config);
  void set_config_unlocked(uint32_t cc_idx, srsran::phy_cfg_t phy_cfg);
  void set_crnti_unlocked(uint16_t rnti);
  void enable_pregen_signals_unlocked(bool enabled);

  ///< Methods for plotting called from GUI thread
  int      read_ce_abs(float* ce_abs, uint32_t tx_antenna, uint32_t rx_antenna);
  uint32_t get_cell_nof_ports()
  {
    // wait until cell is initialized
    std::unique_lock<std::mutex> lock(cell_mutex);
    while (!cell_initiated) {
      cell_init_cond.wait(lock);
    }
    return cell.nof_ports;
  }
  uint32_t get_rx_nof_antennas() { return phy->args->nof_rx_ant; }
  int      read_pdsch_d(cf_t* pdsch_d);
  float    get_cfo();
  void     start_plot();

private:
  /* Inherited from thread_pool::worker. Function called every subframe to run the DL/UL processing */
  void work_imp() final;

  void update_measurements();
  void reset_uci(srsran_uci_data_t* uci_data);

  std::vector<cc_worker*> cc_workers;

  phy_common* phy = nullptr;

  srslog::basic_logger& logger;

  srsran_cell_t       cell = {};
  std::mutex          cell_mutex;
  srsran_tdd_config_t tdd_config = {};

  std::condition_variable cell_init_cond;
  bool                    cell_initiated = false;

  cf_t* prach_ptr   = nullptr;
  float prach_power = 0;

  uint32_t               tti     = 0;
  srsran::rf_timestamp_t tx_time = {};
};

} // namespace lte
} // namespace srsue

#endif // SRSUE_LTE_SF_WORKER_H
