#include <ModbusSlave.h>

// implicitly set stream to use the Serial serialport
Modbus slave(1, 8); // [stream = Serial,] slave id = 1, rs485 control-pin = 8

void setup() {
    // register one handler functions
    // if a callback handler is not assigned to a modbus command 
    // the default handler is called. 
    // default handlers return a valid but empty replay.
    slave.cbVector[CB_WRITE_COIL] = writeDigitlOut;
    
    // start slave at baud 9600 on Serial
    Serial.begin( 9600 ); // baud = 9600
    slave.begin( 9600 );
    pinMode(13,OUTPUT);
}

void loop() {
    // listen for modbus commands con serial port
    slave.poll();
}

// Handel Force Single Coil (FC=05)
void writeDigitlOut(uint8_t fc, uint16_t address, uint16_t status) {
    if (status == HIGH) {
        digitalWrite(address, HIGH);
    } else {
        digitalWrite(address, LOW);
    }
}
