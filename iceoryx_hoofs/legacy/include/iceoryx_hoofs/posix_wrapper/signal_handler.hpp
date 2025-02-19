
// Copyright (c) 2021 - 2022 by Apex.AI Inc. All rights reserved.
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

#ifndef IOX_HOOFS_POSIX_WRAPPER_SIGNAL_HANDLER_HPP
#define IOX_HOOFS_POSIX_WRAPPER_SIGNAL_HANDLER_HPP

#include "iox/detail/deprecation_marker.hpp"
#include "iox/signal_handler.hpp"

IOX_DEPRECATED_HEADER_SINCE(3, "Please include 'iox/signal_handler.hpp' instead.")

namespace iox
{
namespace posix
{
using SignalHandlerCallback_t IOX_DEPRECATED_SINCE(
    3, "Please use 'iox::SignalHandlerCallback_t' from 'iox/signal_handler.hpp' instead.") = SignalHandlerCallback_t;

using Signal IOX_DEPRECATED_SINCE(3,
                                  "Please use 'iox::PosixSignal' from 'iox/signal_handler.hpp' instead.") = PosixSignal;

using SignalGuardError IOX_DEPRECATED_SINCE(
    3, "Please use 'iox::SignalGuardError' from 'iox/signal_handler.hpp' instead.") = SignalGuardError;

using SignalGuard
    IOX_DEPRECATED_SINCE(3, "Please use 'iox::SignalGuard' from 'iox/signal_handler.hpp' instead.") = SignalGuard;

IOX_DEPRECATED_SINCE(3, "Please use 'iox::registerSignalHandler' from 'iox/signal_handler.hpp' instead.")
inline expected<SignalGuard, SignalGuardError> registerSignalHandler(const Signal signal,
                                                                     const SignalHandlerCallback_t callback) noexcept
{
    return iox::registerSignalHandler(signal, callback);
}

} // namespace posix
} // namespace iox

#endif // IOX_HOOFS_POSIX_SYNC_SIGNAL_HANDLER_HPP
