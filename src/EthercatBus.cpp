// src/EthercatBus.cpp
#include "kelo_driver/EthercatBus.hpp"
#include "EthercatBusImpl.hpp"

// Constructor
EthercatBus::EthercatBus() 
    : ptrEthercatBusImpl(std::make_unique<EthercatBusImpl>()) {}

// Destructor
EthercatBus::~EthercatBus() = default; // Required when using PImpl with unique_ptr

void EthercatBus::printMessage() {
    ptrEthercatBusImpl->printMessage();  // Delegate to the implementation
}
