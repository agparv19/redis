#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include "config.h"


namespace fs = std::filesystem;

redis::config redis::GlobalConfig;

bool redis::read_config() {

    fs::path current_path = fs::current_path();

    for (const auto& entry : fs::directory_iterator(current_path)) {

        if (entry.path().filename() == CONFIG_FILE) {
            std::ifstream config(entry.path());
            if (config.is_open()) {
                // found the config file!
                nlohmann::json json = nlohmann::json::parse(config);

                if (json.find("snapshot_period") == json.end()) {
                    std::cout << "Unable to read snapshot config! " << std::endl;
                    return false;
                } else {
                    redis::GlobalConfig.snapshot_period = json["snapshot_period"];
                }

                if (json.find("port") == json.end()) {
                    std::cout << "Unable to read port config! " << std::endl;
                    return false;
                } else {
                    redis::GlobalConfig.port = json["port"];
                }

                // all config read
                return true;
            } else {
                // error opening file
                break;
            }
        }
    }
    return false;
}
