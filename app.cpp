#include <iostream>
#include <stdlib.h>
#include "serial_communication.h"
// #include "terminal.h"

int main()
{
    Serial *serial = new Serial();
    const char *port_name = "/dev/bus/usb/001/006"; //001~006
    serial->Open(port_name);

    // char *message_to_send;
    // strcpy(message_to_send, "");
    // std::cin >> message_to_send;
    serial->Write("1");

    char *received_message = serial->Read(100);
    std::cout << "receive message from serial: " << received_message << std::endl;

    // delete terminal;
    delete serial;
    // terminal = NULL;
    serial = NULL;
    
    system("pause");
    return 0;
}
