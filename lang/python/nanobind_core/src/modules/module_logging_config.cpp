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
 * @brief  Add Logging config structs to nanobind module
**/


#include <modules/module_logging_config.h>
#include <ecal/config/logging.h>

void AddLoggingConfigStructToModule(nanobind::module_& m)
{
    // Bind the Console::Configuration structure
    nanobind::class_<eCAL::Logging::Sinks::Console::Configuration>(m, "ConsoleConfiguration")
        .def(nanobind::init<>())  // Constructor binding
        .def_rw("enable", &eCAL::Logging::Sinks::Console::Configuration::enable)
        .def_rw("filter_log_con", &eCAL::Logging::Sinks::Console::Configuration::filter_log_con);

    // Bind the File::Configuration structure
    nanobind::class_<eCAL::Logging::Sinks::File::Configuration>(m, "FileConfiguration")
        .def(nanobind::init<>())  // Constructor binding
        .def_rw("enable", &eCAL::Logging::Sinks::File::Configuration::enable)
        .def_rw("path", &eCAL::Logging::Sinks::File::Configuration::path)
        .def_rw("filter_log_file", &eCAL::Logging::Sinks::File::Configuration::filter_log_file);

    // Bind the UDP::Configuration structure
    nanobind::class_<eCAL::Logging::Sinks::UDP::Configuration>(m, "UDPConfiguration")
        .def(nanobind::init<>())  // Constructor binding
        .def_rw("enable", &eCAL::Logging::Sinks::UDP::Configuration::enable)
        .def_rw("port", &eCAL::Logging::Sinks::UDP::Configuration::port)
        .def_rw("filter_log_udp", &eCAL::Logging::Sinks::UDP::Configuration::filter_log_udp);

    // Bind the Sinks::Configuration structure
    nanobind::class_<eCAL::Logging::Sinks::Configuration>(m, "SinksConfiguration")
        .def(nanobind::init<>())  // Constructor binding
        .def_rw("console", &eCAL::Logging::Sinks::Configuration::console)
        .def_rw("file", &eCAL::Logging::Sinks::Configuration::file)
        .def_rw("udp", &eCAL::Logging::Sinks::Configuration::udp);

    // Bind the Logging::Configuration structure
    nanobind::class_<eCAL::Logging::Configuration>(m, "LoggingConfiguration")
        .def(nanobind::init<>())  // Constructor binding
        .def_rw("sinks", &eCAL::Logging::Configuration::sinks);

}

