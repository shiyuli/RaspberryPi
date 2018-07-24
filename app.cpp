#include <iostream>
#include "serial_communication.h"
// #include "terminal.h"

int main()
{
    std::cout << "run app" << std::endl;

    Serial *serial = new Serial();
    const char *port_name = "/dev/ttyACM0";
    serial->Open(port_name);

    // int number;
    char convert_buffer[100];

    const byte message_to_send[5] = {
        0x00, 0x01, 0x00, 0x00, (byte)'\n'
    };
    serial->Write(message_to_send);

    std::cout << "sending message to serial:" << std::endl;
    for(int i(0); i < 4; ++i)
    {
        sprintf(convert_buffer, "%x", message_to_send[i]);
        std::cout << convert_buffer << std::endl;
    }
    std::cout << std::endl;

    for(;;)
    {
        char *received_message = serial->Read(100);
        std::cout << "receiving message from serial: " << received_message << std::endl;
    }

    serial->Close();

    // delete terminal;
    delete serial;
    // terminal = NULL;
    serial = NULL;

    std::cout << "quit app" << std::endl;
    return 0;
}
