#include <iostream>
#include <soem/ethercat.h>

void usage() {

  ec_adapter *adapter = NULL;
  
  std::cout << "\nUsage: slaves ifname\n";
  std::cout << "- ifname: network interface\n";
  
  adapter = ec_find_adapters();
  
  std::cout << "\nListing availables interfaces\n";
  
  while (adapter != NULL) {
    std::cout << "  Interface: " << adapter->name << std::endl;
    adapter = adapter->next;
  }
  

}

void scan(const char* ifname) {
  
  if (ec_init(ifname) > 0) {
    if (ec_config_init(FALSE) > 0) {
      ec_configdc();
      
      ec_statecheck(0, EC_STATE_SAFE_OP, EC_TIMEOUTSTATE * 4);

      ec_send_processdata();
      ec_receive_processdata(EC_TIMEOUTRET);
      ec_writestate(0);
      
      for (int i = 1; i <= ec_slavecount; i++) {
        std::cout << "Slave " << i << "\n";
        std::cout << "  Name: " << ec_slave[i].name << "\n";
        
        if (std::string(ec_slave[i].name) == "KELO_ROBILE") {
          std::cout << "  Device type: " << "BMS module\n";
        } else if (std::string(ec_slave[i].name) == "KELOD105") {
          std::cout << "  Device type: " << "Smart wheel\n";
        } else if (std::string(ec_slave[i].name) == "SWMC") {
          std::cout << "  Device type: " << "Smart wheel (old version)\n";
        } else if (std::string(ec_slave[i].name) == "KeloEcPd") {
          std::cout << "  Device type: " << "Power board in dual-arm robot\n";
        } else {
          std::cout << "  Device type: " << "Unknown\n";
        }
        
        std::cout << "  Address: " << ec_slave[i].configadr << "\n";
        std::cout << "  ID: " << ec_slave[i].eep_id << "\n";
        std::cout << "  Manufacturer: 0x" << std::hex << ec_slave[i].eep_man << "\n";
        std::cout << "  Product Code: 0x" << std::hex << ec_slave[i].eep_id << "\n";
        std::cout << "  Revision Number: 0x" << std::hex << ec_slave[i].eep_rev << "\n";
        std::cout << "\n";
      }
      
      ec_close();
    }
  
  } else {
    std::cout << "Failure to start the connection with the interface " << ifname << "\n";
    std::cout << "Make sure you are running this as sudo\n";
  }
  
}

int main(int argc, char* argv[]) {

  if (argc > 1) {
    scan(argv[1]);
  } else {
    std::cout << "The network interface is required! please provide the interface name.\n";
    usage();
  }
  
  return 0;
}
