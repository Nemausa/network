// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <spdlog/cfg/log_levels.h>

namespace spdlog {
namespace cfg {
namespace helpers {
//
// Init levels from given string
//
// Examples:
//
// set global level to debug: "debug"
// turn off all logging except for logger1: "off,logger1=debug"
// turn off all logging except for logger1 and logger2: "off,logger1=debug,logger2=info"
//
SPDLOG_API log_levels extract_levels(const std::string &txt);
} // namespace helpers

} // namespace cfg
} // namespace spdlog