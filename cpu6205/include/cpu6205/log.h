#pragma once
#include "spdlog/spdlog.h"

#define C6205_DEFAULT_LOGGER_NAME "cpulogger"

#ifndef C6205_CONFIG_RELEASE
#define C6205_TRACE(...)    if(spdlog::get(C6205_DEFAULT_LOGGER_NAME)!= nullptr) {spdlog::get(C6205_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);}
#else
#define C6205_TRACE(...)    (void)0
#endif