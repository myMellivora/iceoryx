// Copyright (c) 2019 - 2020 by Robert Bosch GmbH. All rights reserved.
// Copyright (c) 2020 - 2022 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include "iceoryx_posh/roudi/roudi_app.hpp"

#include "iceoryx_platform/getopt.hpp"
#include "iceoryx_platform/resource.hpp"
#include "iceoryx_platform/semaphore.hpp"
#include "iceoryx_platform/signal.hpp"
#include "iceoryx_posh/internal/popo/building_blocks/unique_port_id.hpp"
#include "iceoryx_posh/roudi/cmd_line_args.hpp"
#include "iox/logging.hpp"
#include "iox/optional.hpp"
#include "iox/signal_watcher.hpp"

namespace iox
{
namespace roudi
{
RouDiApp::RouDiApp(const config::CmdLineArgs_t& cmdLineArgs, const RouDiConfig_t& config) noexcept
    : m_logLevel(cmdLineArgs.logLevel)
    , m_monitoringMode(cmdLineArgs.monitoringMode)
    , m_run(checkAndOptimizeConfig(config))
    , m_config(config)
    , m_compatibilityCheckLevel(cmdLineArgs.compatibilityCheckLevel)
    , m_processTeminationDelay(cmdLineArgs.processTerminationDelay)
    , m_processKillDelay(cmdLineArgs.processKillDelay)
{
    // the "and" is intentional, just in case the the provided RouDiConfig_t is empty
    m_run &= cmdLineArgs.run;
    if (cmdLineArgs.uniqueRouDiId)
    {
        popo::UniquePortId::setUniqueRouDiId(cmdLineArgs.uniqueRouDiId.value());
    }

    // be silent if not running
    if (m_run)
    {
        iox::log::Logger::setLogLevel(m_logLevel);

        IOX_LOG(TRACE, "Command line parameters are:\n" << cmdLineArgs);
    }
}

bool RouDiApp::checkAndOptimizeConfig(const RouDiConfig_t& config) noexcept
{
    if (config.m_sharedMemorySegments.empty())
    {
        IOX_LOG(ERROR, "A RouDiConfig without segments was specified! Please provide a valid config!");
        return false;
    }

    for (const auto& segment : config.m_sharedMemorySegments)
    {
        if (segment.m_mempoolConfig.m_mempoolConfig.empty())
        {
            IOX_LOG(ERROR,
                    "A RouDiConfig with segments without mempools was specified! Please provide a valid config!");
            return false;
        }
    }

    return true;
}

bool RouDiApp::waitForSignal() noexcept
{
    iox::waitForTerminationRequest();
    return true;
}

} // namespace roudi
} // namespace iox
