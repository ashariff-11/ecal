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
 * @brief  UDP sample sender to send messages of type eCAL::pb::Sample
**/

#include "ecal_udp_sample_sender.h"

#include <ecal/ecal_log.h>

namespace eCAL
{
  namespace UDP
  {
    CSampleSender::CSampleSender(const IO::UDP::SSenderAttr& attr_)
    {
    }

    size_t CSampleSender::Send(const std::string& sample_name_, const eCAL::pb::Sample& ecal_sample_)
    {
      // return value
      size_t sent_sum(0);

      const size_t data_size = CreateSampleBuffer(sample_name_, ecal_sample_, m_udp_message);
      if (data_size > 0)
      {
        // and send it
        //sent_sum = SendTheUDPMessageViaEcalUDP(m_udp_message.data(), m_udp_message.size());

#ifndef NDEBUG
        // log it
        eCAL::Logging::Log(log_level_debug4, "UDP Sample Buffer Sent (" + std::to_string(sent_sum) + " Bytes)");
#endif
      }

      // return bytes sent
      return(sent_sum);
    }

    size_t CSampleSender::CreateSampleBuffer(const std::string& sample_name_, const eCAL::pb::Sample& ecal_sample_, std::vector<char>& payload_)
    {
      // size of the sample name (e.g. "person")
      const unsigned short sample_name_size = (unsigned short)sample_name_.size() + 1;
      // size of the serialized sample content
      const size_t         sample_size      = ecal_sample_.ByteSizeLong();
      // complet size of the udp message to send
      const size_t         data_size        = sizeof(sample_name_size) + sample_name_size + sample_size;

      // create payload buffer
      payload_.resize(data_size);
      char* payload_data = payload_.data();

      // write topic name size
      ((unsigned short*)payload_data)[0] = sample_name_size;
      // write topic name
      memcpy(payload_data + sizeof(sample_name_size), sample_name_.c_str(), sample_name_size);

      // write payload
      if (ecal_sample_.SerializeWithCachedSizesToArray((google::protobuf::uint8*)payload_data + sizeof(sample_name_size) + sample_name_size))
      {
        return data_size;
      }

      return (0);
    }
  }
}
