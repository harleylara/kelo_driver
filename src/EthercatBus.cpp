#include "kelo_driver/EthercatBus.hpp"
#include "EthercatBusImpl.hpp"

// Constructor
EthercatBus::EthercatBus(const std::string ifname)
    : ptrEthercatBusImpl(std::make_unique<EthercatBusImpl>(ifname)) {}

void EthercatBus::setDebugHandler(const std::function<void(const std::string&)>& handler) {
    EthercatBusImpl::setDebugHandler(handler);
}

void EthercatBus::setInfoHandler(const std::function<void(const std::string&)>& handler) {
    EthercatBusImpl::setInfoHandler(handler);
}

void EthercatBus::setWarningHandler(const std::function<void(const std::string&)>& handler) {
    EthercatBusImpl::setWarningHandler(handler);
}

void EthercatBus::setErrorHandler(const std::function<void(const std::string&)>& handler) {
    EthercatBusImpl::setErrorHandler(handler);
}

// Destructor
EthercatBus::~EthercatBus() = default; // Required when using PImpl with unique_ptr

void EthercatBus::printMessage() {
    ptrEthercatBusImpl->printMessage();  // Delegate to the implementation
}
