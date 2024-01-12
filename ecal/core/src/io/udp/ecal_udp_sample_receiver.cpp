/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2019 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

/**
 * @brief  UDP sample receiver to receive messages of type eCAL::pb::Sample
**/

#include "ecal_udp_sample_receiver.h"

#include <ecal/ecal_log.h>

namespace eCAL
{
  namespace UDP
  {
    CSampleReceiver::CSampleReceiver(const IO::UDP::SReceiverAttr& attr_, HasSampleCallbackT has_sample_callback_, ApplySampleCallbackT apply_sample_callback_) :
      m_has_sample_callback(has_sample_callback_), m_apply_sample_callback(apply_sample_callback_)
    {
    }

    bool CSampleReceiver::AddMultiCastGroup(const char* ipaddr_)
    {
      return false;
    }

    bool CSampleReceiver::RemMultiCastGroup(const char* ipaddr_)
    {
      return false;
    }

    bool CSampleReceiver::OnCompleteMessage(std::vector<char>&& m_udp_message_)
    {
      // read sample_name size
      const unsigned short sample_name_size = ((unsigned short*)(m_udp_message_.data()))[0];
      // read sample_name
      const std::string    sample_name(m_udp_message_.data() + sizeof(sample_name_size));

      if (m_has_sample_callback(sample_name))
      {
        // read sample
        if (!m_ecal_sample.ParseFromArray(m_udp_message_.data() + sizeof(sample_name_size) + sample_name_size, static_cast<int>(m_udp_message_.size() - (sizeof(sample_name_size) + sample_name_size)))) return false;
#ifndef NDEBUG
        // log it
        eCAL::Logging::Log(log_level_debug3, sample_name + "::UDP Sample Completed");

        // log it
        switch (m_ecal_sample.cmd_type())
        {
        case eCAL::pb::bct_none:
          eCAL::Logging::Log(log_level_debug4, sample_name + "::UDP Sample Command Type - NONE");
          break;
        case eCAL::pb::bct_set_sample:
          eCAL::Logging::Log(log_level_debug4, sample_name + "::UDP Sample Command Type - SAMPLE");
          break;
        case eCAL::pb::bct_reg_publisher:
          eCAL::Logging::Log(log_level_debug4, sample_name + "::UDP Sample Command Type - REGISTER PUBLISHER");
          break;
        case eCAL::pb::bct_reg_subscriber:
          eCAL::Logging::Log(log_level_debug4, sample_name + "::UDP Sample Command Type - REGISTER SUBSCRIBER");
          break;
        case eCAL::pb::bct_reg_process:
          eCAL::Logging::Log(log_level_debug4, sample_name + "::UDP Sample Command Type - REGISTER PROCESS");
          break;
        case eCAL::pb::bct_reg_service:
          eCAL::Logging::Log(log_level_debug4, sample_name + "::UDP Sample Command Type - REGISTER SERVER");
          break;
        case eCAL::pb::bct_reg_client:
          eCAL::Logging::Log(log_level_debug4, sample_name + "::UDP Sample Command Type - REGISTER CLIENT");
          break;
        default:
          eCAL::Logging::Log(log_level_debug4, sample_name + "::UDP Sample Command Type - UNKNOWN");
          break;
        }
#endif
        // get layer if this is a payload sample
        eCAL::pb::eTLayerType layer = eCAL::pb::eTLayerType::tl_none;
        if (m_ecal_sample.cmd_type() == eCAL::pb::eCmdType::bct_set_sample)
        {
          if (m_ecal_sample.topic().tlayer_size() > 0)
          {
            layer = m_ecal_sample.topic().tlayer(0).type();
          }
        }
        // apply sample
        m_apply_sample_callback(m_ecal_sample, layer);
      }
      return true;
    }
  }
}
