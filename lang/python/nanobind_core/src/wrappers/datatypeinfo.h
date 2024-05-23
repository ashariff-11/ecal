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
 * @file   datatypeinfo.h
 * @brief  Nanobind wrapper SDataTypeInformation struct
**/

#pragma once

#include <ecal/ecal.h>
#include <stdint.h>
#include <string>
#include <functional>
#include <cstddef>
#include <mutex>
#include <ecal/ecal_types.h>

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/tuple.h>

namespace eCAL
{
    class CNBDataTypeInformation
    {
    public:
        std::string name;
        std::string encoding;
        nanobind::bytes descriptor;
    };

    SDataTypeInformation convert(const CNBDataTypeInformation& nb_info);
}