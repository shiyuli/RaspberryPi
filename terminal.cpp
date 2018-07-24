#include "terminal.h"

Terminal::Terminal()
{
}

Terminal::~Terminal()
{
}

void Terminal::info(char* message)
{
}

void Terminal::error(char* message)
{
    std::cout << message << std::endl;
}
