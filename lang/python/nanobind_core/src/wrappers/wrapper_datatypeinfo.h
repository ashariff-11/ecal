/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2024 Continental Corporation
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
 * @file   wrapper_datatypeinfo.h
 * @brief  Nanobind wrapper SDataTypeInformation struct
**/

#pragma once

#include <ecal/ecal.h>
#include <stdint.h>
#include <string>
#include <cstddef>

#include <ecal/ecal_types.h>
#include <nanobind/nanobind.h>

namespace eCAL
{
    class CNBDataTypeInformation
    {
    public:
        std::string name;
        std::string encoding;
        nanobind::bytes descriptor;
    };

    /**
     * @brief Convert function for SDataTypeInformation
     *
     * @param nb_info      CNBDataTypeInformation struct
     *
     * @return  SDataTypeInformation struct after convertion
    **/
    SDataTypeInformation convert(const CNBDataTypeInformation& nb_info);
}