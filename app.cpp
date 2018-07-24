#include <iostream>
#include <stdlib.h>
#include "serial_communication.h"
#include "terminal.h"

int main()
{
    Serial *serial = new Serial();

    terminal->open("/dev/bus/usb/001/006"); //001~006

    char *message_to_send << std::cin;
    terminal->write(message_to_send);
    char *received_message = terminal->read(100);

    std::cout << "receive message from serial": received_message << std::endl;

    delete terminal;
    delete serial;
    terminal = NULL;
    serial = NULL;
    
    system("pause");
    return 0;
}
