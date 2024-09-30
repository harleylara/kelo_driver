#include <iostream>
#include <soem/ethercat.h>

int main() {
    // Initialize SOEM
    if (ec_init("eth0") == 0) { // Adjust the interface as needed
        std::cerr << "Failed to initialize EtherCAT" << std::endl;
        return -1;
    }

    std::cout << "EtherCAT initialized successfully." << std::endl;

    // Additional SOEM operations go here

    ec_close();
    return 0;


    return 0;
}
