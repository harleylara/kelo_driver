#pragma once
#include <iostream>
#include <functional>
#include <soem/ethercat.h>

std::function<void(const std::string&)> debugHandler = nullptr;
std::function<void(const std::string&)> infoHandler = nullptr;
std::function<void(const std::string&)> warningHandler = nullptr;
std::function<void(const std::string&)> errorHandler = nullptr;

class EthercatBus::EthercatBusImpl
{
public:
    EthercatBusImpl(const std::string& ifname) {

        isValidInterface = checkInterface(ifname);

        if (isValidInterface) {
            debug("the interface: " + ifname + ", has been found.");
            ifname_ = ifname;
        } else {
            // TODO: how to handle this situation
            // stop execution? exception ?
            debug("the interface: " + ifname + ", has NOT been found.");
            listInterfaces();
        }

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
    bool isValidInterface = false;

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

    bool checkInterface(std::string ifname) {
        ec_adaptert* interface = ec_find_adapters();

        while (interface != NULL) {
            if (interface->name == ifname) {
                return true;
            }
            interface = interface->next;
        }

        return false;
    }

    void listInterfaces() {
        ec_adaptert* interface = ec_find_adapters();

        if (!interface) {
            error("No network interfaces found.");
        }

        info("Available network interfaces: ");
        while (interface != NULL) {
            info(interface->name);
            interface = interface->next;
        }
    }

};
