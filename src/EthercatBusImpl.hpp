#pragma once
#include <iostream>

class EthercatBus::EthercatBusImpl
{
public:
    void printMessage() {
        std::cout << "Test impl\n";
    }
};
