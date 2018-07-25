#include <iostream>
#include "serial_communication.h"
#include "console.h"
#include "commands.h"

#define DEBUG
#define SHOW_NUMBER_AUTO -1 //show Arduino numbers auto
#define longstring(a, b) a##b

Serial *serial;

bool test_serial(Serial* serial);
bool test_console();
void print_logo();
bool parse_command();
void show_number(int number);

bool test_serial(Serial* serial)
{
    std::cout << "run test_serial" << std::endl;
    
    // for(;;)
    // {
    //     char *received_message = serial->Read(100);
    //     std::cout << "receiving message from serial: " << received_message << std::endl;
    // }

    std::cout << "end test_serial" << std::endl;
    return true;
}

bool test_console()
{
    std::cout << "start test_console" << std::endl;

    Console::info("testing console->info");
    Console::error("testing console->error");

    std::cout << "end test_console" << std::endl;
    return true;
}

void print_logo()
{
    const char *logo = longstring(
    " ____               _       _             \n"
    "|  _ \ __ _ ___  __| |_   _(_)_ __   ___  \n"
    "| |_) / _` / __|/ _` | | | | | '_ \ / _ \ \n"
    "|  _ < (_| \__ \ (_| | |_| | | | | | (_) |\n"
    "|_| \_\__,_|___/\__,_|\__,_|_|_| |_|\___/ \n"
    "                                          \n"
    );
    Console::println(logo, ConsoleColor::white);
}

bool parse_command()
{
    char *commands[2] = { new char, new char };
    std::cin >> commands[0];
    std::cin >> commands[1];

    //std::cout << "command: " << command << std::endl;
    //std::cout << "command len: " << sizeof(command) << std::endl;

    if(strcmp(commands[0], CMD_SHOW_NUMBER) == 0)
    {
        if(strcmp(commands[1], ARG_AUTO) == 0)
        {
            show_number(SHOW_NUMBER_AUTO);
        }
        else
        {
            show_number((int)commands[1]);
        }
    }

    return true;
}

void show_number(int number)
{
    byte message_to_send[5] = {
        0x00, 0xFF, 0xFF, 0xFF, (byte)'\n'
    };

    if(number == SHOW_NUMBER_AUTO)
    {
        message_to_send[1] = 0x01;
    }
    else
    {
        message_to_send[1] = 0x00;
    }

    message_to_send[3] = (byte)number;

    serial->Write(message_to_send);

    // Console::info("sending message to serial:");
    // char convert_buffer[100];
    // for(int i(0); i < 4; ++i)
    // {
    //     sprintf(convert_buffer, "%x", message_to_send[i]);
    //     std::cout << convert_buffer << std::endl;
    // }
    // std::cout << std::endl;
}

int main()
{
#ifdef DEBUG
    std::cout << "run app" << std::endl;
#endif
    print_logo();

    serial = new Serial();
    const char *port_name = "/dev/ttyACM0";
    serial->Open(port_name);

#ifdef DEBUG
    if(!test_serial(serial))
    {
        std::cout << ConsoleColor::red << "test_serial failed" << std::endl;
        return -1;
    }

    if(!test_console())
    {
        std::cout << ConsoleColor::red << "test_console failed" << std::endl;
        return -1;
    }
#endif

    for(;;)
    {
        Console::print("command>");
        if(!parse_command())
        {
            break;
        }
    }

    serial->Close();

    delete serial;
    serial = NULL;

    Console::debug("end app");
    return 0;
}
