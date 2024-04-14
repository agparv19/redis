#pragma once

#include "common.h"

#define CONFIG_FILE "config.json"

namespace redis {
    struct config{
        int port;
        std::string statefile;
        int snapshot_period;
    };
    extern config GlobalConfig;
    bool read_config();
}
