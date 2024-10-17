#pragma once
#include <memory>

class EthercatBus
{
public:
    EthercatBus();
    ~EthercatBus();

    void printMessage();

private:
    class EthercatBusImpl;
    std::unique_ptr<EthercatBusImpl> ptrEthercatBusImpl;

};
