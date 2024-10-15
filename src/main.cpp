#include <iostream>
#include <soem/ethercat.h>
#include <stdio.h>
#include <string.h>

char IOmap[4096];
bool forceByteAligment = TRUE;

// Process Data Inputs
struct __attribute__((packed)) MasterBatteryPDI {
    uint64_t TimeStamp;  	 	 // EtherCAT timestamp ms
    uint16_t Status;     	 	 // Status bits
    uint16_t Error;					 // Error bits: bit0:LowBAT,bit1:EMPTYFRAM,bit2:WrongFRAM,bit3:WrongCHGARGER,bit4:OverloadCHG,bit5:OverCurrentError,bit6:Watchdog
    uint16_t Warning;				 // Warning bits:bit0:OverCurrentWarning,bit1:Shutdown
    float    OutputCurrent;  // Total current consumption
    float    OutputVoltage;  // System Voltage
    float    OutputPower;    // Total power consumption of the system
    float    AuxPortCurrent; // Current consumption at Auxiliary port
    float    GenericData1; 	 // Generic data, might be used for different purposes
    uint32_t  GenericData2;	 // Generic data, might be used for different purposes
    uint16_t bmsm_PwrDeviceId;
    uint16_t bmsm_Status;
    float    bmsm_Voltage;
    float    bmsm_Current;
    float    bmsm_Temperature;
    uint16_t bmsm_SOC;
    uint32_t bmsm_SN;
    uint32_t bmsm_BatData1;
    float    bmsm_BatData2;
};

// Process Data Outputs for Master Battery module
struct __attribute__((packed)) MasterBatteryPDO {
    uint32_t Command1;
    uint32_t Command2;
    uint16_t Shutdown;
    uint16_t PwrDeviceId;
};

int main() {

    // Initialize SOEM
    if (ec_init("eno1")) {
        std::cout << "ec_init succeeded" << std::endl;

        if (ec_config_init(FALSE) > 0) {
            std::cout << "Found and configured " << ec_slavecount << " slaves" << std::endl;

            for (int i = 1; i <= ec_slavecount; i++) {
                std::cout << "Slave: " << i << "\n";
                std::cout << "	Name: " << ec_slave[i].name << "\n";
                std::cout << "	ID: " << ec_slave[i].eep_id << "\n";
            }

            if (forceByteAligment) {
                ec_config_map_aligned(&IOmap);
            } else {
                ec_config_map(&IOmap);
            }

            // configure the distributed clocks
            ec_configdc();
            ec_statecheck(0, EC_STATE_SAFE_OP, EC_TIMEOUTSTATE * 4);

            // request operational state for all slaves
            int expectedWKC = (ec_group[0].outputsWKC * 2) + ec_group[0].inputsWKC;
            std::cout << "Calculated WKC " << expectedWKC << std::endl;
            ec_slave[0].state = EC_STATE_OPERATIONAL;
            ec_send_processdata();
            ec_receive_processdata(EC_TIMEOUTRET);
            ec_writestate(0);

            int chk = 200;

            do {
                ec_send_processdata();
                ec_receive_processdata(EC_TIMEOUTRET);
                ec_statecheck(0, EC_STATE_OPERATIONAL, 50000);

            } while(chk-- && (ec_slave[0].state != EC_STATE_OPERATIONAL));

            //while (1) {
            //	ec_send_processdata();
            //    ec_receive_processdata(EC_TIMEOUTRET);


            MasterBatteryPDO outputs;
            MasterBatteryPDI* inputs;
            inputs = (MasterBatteryPDI*)ec_slave[1].inputs;


            outputs.Command1 = 0;
            outputs.Command2 = 0;
            outputs.Shutdown = 0;
            outputs.PwrDeviceId = 0;

            memcpy(ec_slave[1].outputs, &outputs, sizeof(outputs));

            ec_send_processdata();
            ec_receive_processdata(EC_TIMEOUTRET);
            ec_send_processdata();

            std::cout << "TimeStamp: " << inputs->TimeStamp << std::endl;
            std::cout << "Status: " << inputs->Status << std::endl;
            std::cout << "Error: " << inputs->Error << std::endl;
            std::cout << "Warning: " << inputs->Error << std::endl;
            std::cout << "OutputCurrent: " << inputs->OutputCurrent << std::endl;
            std::cout << "OutputVoltage: " << inputs->OutputVoltage << std::endl;
            std::cout << "OutputPower: " << inputs->OutputPower << std::endl;
            std::cout << "AuxPortCurrent: " << inputs->AuxPortCurrent << std::endl;
            std::cout << "GenericData1: " << inputs->GenericData1 << std::endl;
            std::cout << "GenericData2: " << inputs->GenericData2 << std::endl;
            std::cout << "bmsm_PwrDeviceId: " << inputs->bmsm_PwrDeviceId << std::endl;
            std::cout << "bmsm_Status: " << inputs->bmsm_Status << std::endl;
            std::cout << "bmsm_Voltage: " << inputs->bmsm_Voltage << std::endl;
            std::cout << "bmsm_Current: " << inputs->bmsm_Current << std::endl;
            std::cout << "bmsm_Temperature: " << inputs->bmsm_Temperature << std::endl;
            std::cout << "bmsm_SOC: " << inputs->bmsm_SOC << std::endl;
            std::cout << "bmsm_SN: " << inputs->bmsm_SN << std::endl;
            std::cout << "bmsm_BatData1: " << inputs->bmsm_BatData1 << std::endl;
            std::cout << "bmsm_BatData2: " << inputs->bmsm_BatData2 << std::endl;

        }

        ec_close();
    } else {
        std::cout << "Failed to start master" << std::endl;
    }
    return 0;

}
