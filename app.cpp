#include <iostream>
#include "serial_communication.h"
// #include "terminal.h"

int main()
{
    std::cout << "run app" << std::endl;

    Serial *serial = new Serial();
    const char *port_name = "/dev/bus/usb/001/006"; //001~006
    serial->Open(port_name);

    const char *message_to_send = "1";
    serial->Write(message_to_send);
    std::cout << "sending message to serial: " << message_to_send << std::endl;

    // char *received_message = serial->Read(100);
    // std::cout << "receive message from serial: " << received_message << std::endl;

    // delete terminal;
    delete serial;
    // terminal = NULL;
    serial = NULL;

    std::cout << "quit app" << std::endl;
    return 0;
}
