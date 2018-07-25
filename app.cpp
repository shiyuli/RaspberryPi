#include <iostream>
#include "serial_communication.h"
#include "console.h"

bool test_serial(Serial* serial)
{
    std::cout << "run test" << std::endl;

    // int number;
    char convert_buffer[100];

    //show Arduino numbers auto
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

    // for(;;)
    // {
    //     char *received_message = serial->Read(100);
    //     std::cout << "receiving message from serial: " << received_message << std::endl;
    // }

    std::cout << "end test" << std::endl;

    return true;
}

bool test_console(Console* console)
{
    console->info("testing console->info");
    console->error("testing console->error");

    return true;
}

int main()
{
    std::cout << "run app" << std::endl;

    Serial *serial = new Serial();
    const char *port_name = "/dev/ttyACM0";
    serial->Open(port_name);

    if(!test_serial(serial))
    {
        std::cout << "test_serial failed" << std::endl;
        return -1;
    }

    if(!test_console(console))
    {
        std::cout << "test_console failed" << std::endl;
        return -1;
    }

    serial->Close();

    delete serial;
    serial = NULL;

    delete console;
    console = NULL;

    std::cout << "end app" << std::endl;
    return 0;
}
