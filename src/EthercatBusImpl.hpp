#pragma once
#include <iostream>
#include <functional>

std::function<void(const std::string&)> debugHandler = nullptr;
std::function<void(const std::string&)> infoHandler = nullptr;
std::function<void(const std::string&)> warningHandler = nullptr;
std::function<void(const std::string&)> errorHandler = nullptr;

class EthercatBus::EthercatBusImpl
{
public:
    EthercatBusImpl(const std::string& ifname) : ifname_(ifname) {
        info("Starting driver with interface: " + ifname_);
    }

    static void setDebugHandler(const std::function<void(const std::string&)>& handler) {
        debugHandler = handler;
    }

    static void setInfoHandler(const std::function<void(const std::string&)>& handler) {
        infoHandler = handler;
    }

    static void setWarningHandler(const std::function<void(const std::string&)>& handler) {
        warningHandler = handler;
    }

    static void setErrorHandler(const std::function<void(const std::string&)>& handler) {
        errorHandler = handler;
    }

    void printMessage() {
        std::cout << "Test impl\n";
    }

private:
    std::string ifname_;

    static void debug(const std::string& message) {
        if (debugHandler) {
            debugHandler(message);
        } else {
            std::cout << "[DEBUG] [EthercatBus]: " << message << std::endl;
        }
    }

    static void info(const std::string& message) {
        if (infoHandler) {
            infoHandler(message);
        } else {
            std::cout << "[INFO] [EthercatBus]: " << message << std::endl;
        }
    }

    static void warning(const std::string& message) {
        if (warningHandler) {
            warningHandler(message);
        } else {
            std::cout << "[WARNING] [EthercatBus]: " << message << std::endl;
        }
    }

    static void error(const std::string& message) {
        if (errorHandler) {
            errorHandler(message);
        } else {
            std::cout << "[ERROR] [EthercatBus]: " << message << std::endl;
        }
    }

};
