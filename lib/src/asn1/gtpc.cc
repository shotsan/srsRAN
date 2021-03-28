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
#include "srsran/asn1/gtpc.h"
#include "srsran/common/byte_buffer.h"
#include <stdint.h>

namespace srsran {

const char* gtpc_msg_type_to_str(uint8_t type)
{
  switch (type) {
    case GTPC_MSG_TYPE_RESERVED:
      return "GTPC_MSG_TYPE_RESERVED";
    case GTPC_MSG_TYPE_ECHO_REQUEST:
      return "GTPC_MSG_TYPE_ECHO_REQUEST";
    case GTPC_MSG_TYPE_ECHO_RESPONSE:
      return "GTPC_MSG_TYPE_ECHO_RESPONSE";
    case GTPC_MSG_TYPE_VERSION_SUPPORT:
      return "GTPC_MSG_TYPE_VERSION_SUPPORT";
    case GTPC_MSG_TYPE_CREATE_SESSION_REQUEST:
      return "GTPC_MSG_TYPE_CREATE_SESSION_REQUEST";
    case GTPC_MSG_TYPE_CREATE_SESSION_RESPONSE:
      return "GTPC_MSG_TYPE_CREATE_SESSION_RESPONSE";
    case GTPC_MSG_TYPE_DELETE_SESSION_REQUEST:
      return "GTPC_MSG_TYPE_DELETE_SESSION_REQUEST";
    case GTPC_MSG_TYPE_DELETE_SESSION_RESPONSE:
      return "GTPC_MSG_TYPE_DELETE_SESSION_RESPONSE";
    case GTPC_MSG_TYPE_MODIFY_BEARER_REQUEST:
      return "GTPC_MSG_TYPE_MODIFY_BEARER_REQUEST";
    case GTPC_MSG_TYPE_MODIFY_BEARER_RESPONSE:
      return "GTPC_MSG_TYPE_MODIFY_BEARER_RESPONSE";
    case GTPC_MSG_TYPE_CHANGE_NOTIFICATION_REQUEST:
      return "GTPC_MSG_TYPE_CHANGE_NOTIFICATION_REQUEST";
    case GTPC_MSG_TYPE_CHANGE_NOTIFICATION_RESPONSE:
      return "GTPC_MSG_TYPE_CHANGE_NOTIFICATION_RESPONSE";
    case GTPC_MSG_TYPE_RESUME_NOTIFICATION:
      return "GTPC_MSG_TYPE_RESUME_NOTIFICATION";
    case GTPC_MSG_TYPE_RESUME_ACKNOWLEDGE:
      return "GTPC_MSG_TYPE_RESUME_ACKNOWLEDGE";
    case GTPC_MSG_TYPE_MODIFY_BEARER_COMMAND:
      return "GTPC_MSG_TYPE_MODIFY_BEARER_COMMAND";
    case GTPC_MSG_TYPE_MODIFY_BEARER_FAILURE_INDICATION:
      return "GTPC_MSG_TYPE_MODIFY_BEARER_FAILURE_INDICATION";
    case GTPC_MSG_TYPE_DELETE_BEARER_COMMAND:
      return "GTPC_MSG_TYPE_DELETE_BEARER_COMMAND";
    case GTPC_MSG_TYPE_DELETE_BEARER_FAILURE_INDICATION:
      return "GTPC_MSG_TYPE_DELETE_BEARER_FAILURE_INDICATION";
    case GTPC_MSG_TYPE_BEARER_RESOURCE_COMMAND:
      return "GTPC_MSG_TYPE_BEARER_RESOURCE_COMMAND";
    case GTPC_MSG_TYPE_BEARER_RESOURCE_FAILURE_INDICATION:
      return "GTPC_MSG_TYPE_BEARER_RESOURCE_FAILURE_INDICATION";
    case GTPC_MSG_TYPE_DOWNLINK_DATA_NOTIFICATION_FAILURE_INDICATION:
      return "GTPC_MSG_TYPE_DOWNLINK_DATA_NOTIFICATION_FAILURE_INDICATION";
    case GTPC_MSG_TYPE_TRACE_SESSION_ACTIVATION:
      return "GTPC_MSG_TYPE_TRACE_SESSION_ACTIVATION";
    case GTPC_MSG_TYPE_TRACE_SESSION_DEACTIVATION:
      return "GTPC_MSG_TYPE_TRACE_SESSION_DEACTIVATION";
    case GTPC_MSG_TYPE_STOP_PAGING_INDICATION:
      return "GTPC_MSG_TYPE_STOP_PAGING_INDICATION";
    case GTPC_MSG_TYPE_CREATE_BEARER_REQUEST:
      return "GTPC_MSG_TYPE_CREATE_BEARER_REQUEST";
    case GTPC_MSG_TYPE_CREATE_BEARER_RESPONSE:
      return "GTPC_MSG_TYPE_CREATE_BEARER_RESPONSE";
    case GTPC_MSG_TYPE_UPDATE_BEARER_REQUEST:
      return "GTPC_MSG_TYPE_UPDATE_BEARER_REQUEST";
    case GTPC_MSG_TYPE_UPDATE_BEARER_RESPONSE:
      return "GTPC_MSG_TYPE_UPDATE_BEARER_RESPONSE";
    case GTPC_MSG_TYPE_DELETE_BEARER_REQUEST:
      return "GTPC_MSG_TYPE_DELETE_BEARER_REQUEST";
    case GTPC_MSG_TYPE_DELETE_BEARER_RESPONSE:
      return "GTPC_MSG_TYPE_DELETE_BEARER_RESPONSE";
    case GTPC_MSG_TYPE_DELETE_PDN_CONNECTION_SET_REQUEST:
      return "GTPC_MSG_TYPE_DELETE_PDN_CONNECTION_SET_REQUEST";
    case GTPC_MSG_TYPE_DELETE_PDN_CONNECTION_SET_RESPONSE:
      return "GTPC_MSG_TYPE_DELETE_PDN_CONNECTION_SET_RESPONSE";
    case GTPC_MSG_TYPE_IDENTIFICATION_REQUEST:
      return "GTPC_MSG_TYPE_IDENTIFICATION_REQUEST";
    case GTPC_MSG_TYPE_IDENTIFICATION_RESPONSE:
      return "GTPC_MSG_TYPE_IDENTIFICATION_RESPONSE";
    case GTPC_MSG_TYPE_CONTEXT_REQUEST:
      return "GTPC_MSG_TYPE_CONTEXT_REQUEST";
    case GTPC_MSG_TYPE_CONTEXT_RESPONSE:
      return "GTPC_MSG_TYPE_CONTEXT_RESPONSE";
    case GTPC_MSG_TYPE_CONTEXT_ACKNOWLEDGE:
      return "GTPC_MSG_TYPE_CONTEXT_ACKNOWLEDGE";
    case GTPC_MSG_TYPE_FORWARD_RELOCATION_REQUEST:
      return "GTPC_MSG_TYPE_FORWARD_RELOCATION_REQUEST";
    case GTPC_MSG_TYPE_FORWARD_RELOCATION_RESPONSE:
      return "GTPC_MSG_TYPE_FORWARD_RELOCATION_RESPONSE";
    case GTPC_MSG_TYPE_FORWARD_RELOCATION_COMPLETE_NOTIFICATION:
      return "GTPC_MSG_TYPE_FORWARD_RELOCATION_COMPLETE_NOTIFICATION";
    case GTPC_MSG_TYPE_FORWARD_RELOCATION_COMPLETE_ACKNOWLEDGE:
      return "GTPC_MSG_TYPE_FORWARD_RELOCATION_COMPLETE_ACKNOWLEDGE";
    case GTPC_MSG_TYPE_FORWARD_ACCESS_CONTEXT_NOTIFICATION:
      return "GTPC_MSG_TYPE_FORWARD_ACCESS_CONTEXT_NOTIFICATION";
    case GTPC_MSG_TYPE_FORWARD_ACCESS_CONTEXT_ACKNOWLEDGE:
      return "GTPC_MSG_TYPE_FORWARD_ACCESS_CONTEXT_ACKNOWLEDGE";
    case GTPC_MSG_TYPE_RELOCATION_CANCEL_REQUEST:
      return "GTPC_MSG_TYPE_RELOCATION_CANCEL_REQUEST";
    case GTPC_MSG_TYPE_RELOCATION_CANCEL_RESPONSE:
      return "GTPC_MSG_TYPE_RELOCATION_CANCEL_RESPONSE";
    case GTPC_MSG_TYPE_CONFIGURATION_TRANSFER_TUNNEL:
      return "GTPC_MSG_TYPE_CONFIGURATION_TRANSFER_TUNNEL";
    case GTPC_MSG_TYPE_RAN_INFORMATION_RELAY:
      return "GTPC_MSG_TYPE_RAN_INFORMATION_RELAY";
    case GTPC_MSG_TYPE_DETACH_NOTIFICATION:
      return "GTPC_MSG_TYPE_DETACH_NOTIFICATION";
    case GTPC_MSG_TYPE_DETACH_ACKNOWLEDGE:
      return "GTPC_MSG_TYPE_DETACH_ACKNOWLEDGE";
    case GTPC_MSG_TYPE_CS_PAGING_INDICATION:
      return "GTPC_MSG_TYPE_CS_PAGING_INDICATION";
    case GTPC_MSG_TYPE_ALERT_MME_NOTIFICATION:
      return "GTPC_MSG_TYPE_ALERT_MME_NOTIFICATION";
    case GTPC_MSG_TYPE_ALERT_MME_ACKNOWLEDGE:
      return "GTPC_MSG_TYPE_ALERT_MME_ACKNOWLEDGE";
    case GTPC_MSG_TYPE_UE_ACTIVITY_NOTIFICATION:
      return "GTPC_MSG_TYPE_UE_ACTIVITY_NOTIFICATION";
    case GTPC_MSG_TYPE_UE_ACTIVITY_ACKNOWLEDGE:
      return "GTPC_MSG_TYPE_UE_ACTIVITY_ACKNOWLEDGE";
    case GTPC_MSG_TYPE_SUSPEND_NOTIFICATION:
      return "GTPC_MSG_TYPE_SUSPEND_NOTIFICATION";
    case GTPC_MSG_TYPE_SUSPEND_ACKNOWLEDGE:
      return "GTPC_MSG_TYPE_SUSPEND_ACKNOWLEDGE";
    case GTPC_MSG_TYPE_CREATE_FORWARDING_TUNNEL_REQUEST:
      return "GTPC_MSG_TYPE_CREATE_FORWARDING_TUNNEL_REQUEST";
    case GTPC_MSG_TYPE_CREATE_FORWARDING_TUNNEL_RESPONSE:
      return "GTPC_MSG_TYPE_CREATE_FORWARDING_TUNNEL_RESPONSE";
    case GTPC_MSG_TYPE_CREATE_INDIRECT_DATA_FORWARDING_TUNNEL_REQUEST:
      return "GTPC_MSG_TYPE_CREATE_INDIRECT_DATA_FORWARDING_TUNNEL_REQUEST";
    case GTPC_MSG_TYPE_CREATE_INDIRECT_DATA_FORWARDING_TUNNEL_RESPONSE:
      return "GTPC_MSG_TYPE_CREATE_INDIRECT_DATA_FORWARDING_TUNNEL_RESPONSE";
    case GTPC_MSG_TYPE_DELETE_INDIRECT_DATA_FORWARDING_TUNNEL_REQUEST:
      return "GTPC_MSG_TYPE_DELETE_INDIRECT_DATA_FORWARDING_TUNNEL_REQUEST";
    case GTPC_MSG_TYPE_DELETE_INDIRECT_DATA_FORWARDING_TUNNEL_RESPONSE:
      return "GTPC_MSG_TYPE_DELETE_INDIRECT_DATA_FORWARDING_TUNNEL_RESPONSE";
    case GTPC_MSG_TYPE_RELEASE_ACCESS_BEARERS_REQUEST:
      return "GTPC_MSG_TYPE_RELEASE_ACCESS_BEARERS_REQUEST";
    case GTPC_MSG_TYPE_RELEASE_ACCESS_BEARERS_RESPONSE:
      return "GTPC_MSG_TYPE_RELEASE_ACCESS_BEARERS_RESPONSE";
    case GTPC_MSG_TYPE_DOWNLINK_DATA_NOTIFICATION:
      return "GTPC_MSG_TYPE_DOWNLINK_DATA_NOTIFICATION";
    case GTPC_MSG_TYPE_DOWNLINK_DATA_NOTIFICATION_ACKNOWLEDGE:
      return "GTPC_MSG_TYPE_DOWNLINK_DATA_NOTIFICATION_ACKNOWLEDGE";
    case GTPC_MSG_TYPE_PGW_RESTART_NOTIFICATION:
      return "GTPC_MSG_TYPE_PGW_RESTART_NOTIFICATION";
    case GTPC_MSG_TYPE_PGW_RESTART_NOTIFICATION_ACKNOWLEDGE:
      return "GTPC_MSG_TYPE_PGW_RESTART_NOTIFICATION_ACKNOWLEDGE";
    case GTPC_MSG_TYPE_UPDATE_PDN_CONNECTION_SET_REQUEST:
      return "GTPC_MSG_TYPE_UPDATE_PDN_CONNECTION_SET_REQUEST";
    case GTPC_MSG_TYPE_UPDATE_PDN_CONNECTION_SET_RESPONSE:
      return "GTPC_MSG_TYPE_UPDATE_PDN_CONNECTION_SET_RESPONSE";
    case GTPC_MSG_TYPE_MODIFY_ACCESS_BEARERS_REQUEST:
      return "GTPC_MSG_TYPE_MODIFY_ACCESS_BEARERS_REQUEST";
    case GTPC_MSG_TYPE_MODIFY_ACCESS_BEARERS_RESPONSE:
      return "GTPC_MSG_TYPE_MODIFY_ACCESS_BEARERS_RESPONSE";
    case GTPC_MSG_TYPE_MBMS_SESSION_START_REQUEST:
      return "GTPC_MSG_TYPE_MBMS_SESSION_START_REQUEST";
    case GTPC_MSG_TYPE_MBMS_SESSION_START_RESPONSE:
      return "GTPC_MSG_TYPE_MBMS_SESSION_START_RESPONSE";
    case GTPC_MSG_TYPE_MBMS_SESSION_UPDATE_REQUEST:
      return "GTPC_MSG_TYPE_MBMS_SESSION_UPDATE_REQUEST";
    case GTPC_MSG_TYPE_MBMS_SESSION_UPDATE_RESPONSE:
      return "GTPC_MSG_TYPE_MBMS_SESSION_UPDATE_RESPONSE";
    case GTPC_MSG_TYPE_MBMS_SESSION_STOP_REQUEST:
      return "GTPC_MSG_TYPE_MBMS_SESSION_STOP_REQUEST";
    case GTPC_MSG_TYPE_MBMS_SESSION_STOP_RESPONSE:
      return "GTPC_MSG_TYPE_MBMS_SESSION_STOP_RESPONSE";
  }
  return "GTPC_MSG_TYPE_INVALID";
}

int gtpc_pack_create_session_request(struct gtpc_create_session_request* cs_req, srsran::byte_buffer_t)
{
  // TODO
  return 0;
}
} // namespace srsran
