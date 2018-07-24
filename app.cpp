#include <iostream>
#include "serial_communication.h"
// #include "terminal.h"

int main()
{
    std::cout << "run app" << std::endl;

    Serial *serial = new Serial();
    const char *port_name = "/dev/bus/usb/001/006"; //001~006
    serial->Open(port_name);

    int number = 1;

    const byte message_to_send[5] = {
        0x00, 0x00, 0x00, (byte)number, (byte)'\n'
    };
    serial->Write(message_to_send);

    std::cout << "sending message to serial:" << std::endl;
    for(int i(0); i < 5; ++i)
    {
        std::cout << message_to_send[i] << std::endl;
    }

    // char *received_message = serial->Read(100);
    // std::cout << "receive message from serial: " << received_message << std::endl;

    // delete terminal;
    delete serial;
    // terminal = NULL;
    serial = NULL;

    std::cout << "quit app" << std::endl;
    return 0;
}
