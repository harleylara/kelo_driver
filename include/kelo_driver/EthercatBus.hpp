#pragma once
#include <memory>
#include <string>
#include <functional>

class EthercatBus
{
public:

    /*
    * Allow you to set your own `debug` handler function.
    *
    * @param handler function to handle your **debug** messages.
    */
    static void setDebugHandler(const std::function<void(const std::string&)>& handler);

    /*
    * Allow you to set your own `info` handler function.
    *
    * @param handler function to handle your **information** messages.
    */
    static void setInfoHandler(const std::function<void(const std::string&)>& handler);

    /*
    * Allow you to set your own `warning` handler function.
    *
    * @param handler function to handle your **warning** messages.
    */
    static void setWarningHandler(const std::function<void(const std::string&)>& handler);

    /*
    * Allow you to set your own `error` handler function.
    *
    * @param handler function to handle your **error** messages.
    */
    static void setErrorHandler(const std::function<void(const std::string&)>& handler);

    /*
    * Set the interface name for the EthercatBus.
    *
    * @param ifname Name of the ethercat interface
    */
    EthercatBus(const std::string ifname);
    ~EthercatBus();

    void printMessage();

private:
    class EthercatBusImpl;
    std::unique_ptr<EthercatBusImpl> ptrEthercatBusImpl;

};
