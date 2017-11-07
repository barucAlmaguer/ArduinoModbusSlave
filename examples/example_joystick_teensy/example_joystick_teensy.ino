#include <ModbusSlave.h>

#define JOY_SW      A2
#define JOY_X       A1
#define JOY_Y       A0
#define MODBUS_RT   2
#define MODBUS_PORT Serial1

// explicitly set stream to use the Serial serialport
Modbus slave(MODBUS_PORT, 2, MODBUS_RT); // stream = Serial, slave id = 1, rs485 control-pin = 8

void setup() {
    // register handler functions
    slave.cbVector[CB_READ_REGISTERS] = ReadAnalogIn;
    
    // start slave at baud 9600 on Serial
    Serial.begin( 9600 ); // baud = 9600
    MODBUS_PORT.begin(9600);
    slave.begin( 9600 );
    delay(5000);
    Serial.println("modbus Init");
}

void loop() {
    // listen for modbus commands con serial port
    slave.poll();
//   while(MODBUS_PORT.available()){
//    Serial.write(MODBUS_PORT.read());
//  }
}

// Handel Read Input Registers (FC=04)
void ReadAnalogIn(uint8_t fc, uint16_t address, uint16_t length) {
    //Serial.println("Modbuseando!");
    // we only answer to function code 4
    if (fc != FC_READ_INPUT_REGISTERS) return;
    
    // write registers into the answer buffer
    for (int i = 0; i < length; i++) {
      slave.writeRegisterToBuffer(i, analogRead(address + i));
    }
}
