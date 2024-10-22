#include "kelo_driver/EthercatBus.hpp"
#include <string>
#include <iostream>

void customDebugHandler(const std::string& message) {
    std::cout << "[CUSTOM] [DEBUG]: " << message << std::endl;
}

void customInfoHandler(const std::string& message) {
    std::cout << "[CUSTOM] [INFO]: " << message << std::endl;
}

int main(int argc, char* argv[]) {

    // you can pass a custom logging to the driver.
    // This allow the driver to write the messages
    // into you own logging system.
    // EthercatBus::setDebugHandler(customDebugHandler);
    // EthercatBus::setInfoHandler(customInfoHandler);

    EthercatBus bus("eth0");
    return 0;
}
