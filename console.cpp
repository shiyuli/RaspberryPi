#include "terminal.h"

void Console::info(char* message)
{
    print(message, color::white);
}

void Console::error(char* message)
{
    print(message, color::red);
}

void Console::print(char* message, std::ostream& color)
{
    std::cout << color << message << std::endl;
}

std::ostream& Color::grey(std::ostream& stream);
{
    stream << "\033[30m";
    return stream;
}

std::ostream& Color::red(std::ostream& stream);
{
    stream << "\033[31m";
    return stream;
}

std::ostream& Color::green(std::ostream& stream);
{
    stream << "\033[32m";
    return stream;
}

std::ostream& Color::yellow(std::ostream& stream);
{
    stream << "\033[33m";
    return stream;
}

std::ostream& Color::blue(std::ostream& stream);
{
    stream << "\033[34m";
    return stream;
}

std::ostream& Color::magenta(std::ostream& stream);
{
    stream << "\033[35m";
    return stream;
}

std::ostream& Color::cyan(std::ostream& stream);
{
    stream << "\033[36m";
    return stream;
}

std::ostream& Color::white(std::ostream& stream);
{
    stream << "\037[37m";
    return stream;
}