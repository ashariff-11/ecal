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

#pragma once

#include "ecal_udp_receiver_attr.h"

#ifdef _MSC_VER
#pragma warning(push, 0) // disable proto warnings
#endif
#include <ecal/core/pb/ecal.pb.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <functional>

namespace eCAL
{
  namespace UDP
  {
    class CSampleReceiver
    {
    public:
      using HasSampleCallbackT   = std::function<bool(const std::string& sample_name_)>;
      using ApplySampleCallbackT = std::function<void(const eCAL::pb::Sample& ecal_sample_, eCAL::pb::eTLayerType layer_)>;

      CSampleReceiver(const IO::UDP::SReceiverAttr& attr_, HasSampleCallbackT has_sample_callback_, ApplySampleCallbackT apply_sample_callback_);

      bool AddMultiCastGroup(const char* ipaddr_);
      bool RemMultiCastGroup(const char* ipaddr_);

    protected:
      HasSampleCallbackT   m_has_sample_callback;
      ApplySampleCallbackT m_apply_sample_callback;
    };
  }
}
