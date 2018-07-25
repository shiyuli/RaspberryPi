#include "console.h"

void Console::info(const char* message)
{
    println(message, ConsoleColor::green);
    reset();
}

void Console::error(const char* message)
{
    println(message, ConsoleColor::red);
    reset();
}

void Console::debug(const char* message)
{
#ifdef DEBUG
    println(message, ConsoleColor::yellow);
    reset();
#endif
}

void Console::print(const char* message)
{
    print(message, ConsoleColor::normal);
}

void Console::print(const char* message, color_t color)
{
    std::cout << color << message;
    reset();
}

void Console::println(const char* message)
{
    println(message, ConsoleColor::normal);
}

void Console::println(const char* message, color_t color)
{
    std::cout << color << message << std::endl;
    reset();
}

void Console::reset()
{
    std::cout << ConsoleColor::normal;
}

std::ostream& ConsoleColor::normal(std::ostream& stream)
{
    stream << "\033[00m";
    return stream;
}

std::ostream& ConsoleColor::grey(std::ostream& stream)
{
    stream << "\033[30m";
    return stream;
}

std::ostream& ConsoleColor::red(std::ostream& stream)
{
    stream << "\033[31m";
    return stream;
}

std::ostream& ConsoleColor::green(std::ostream& stream)
{
    stream << "\033[32m";
    return stream;
}

std::ostream& ConsoleColor::yellow(std::ostream& stream)
{
    stream << "\033[33m";
    return stream;
}

std::ostream& ConsoleColor::blue(std::ostream& stream)
{
    stream << "\033[34m";
    return stream;
}

std::ostream& ConsoleColor::magenta(std::ostream& stream)
{
    stream << "\033[35m";
    return stream;
}

std::ostream& ConsoleColor::cyan(std::ostream& stream)
{
    stream << "\033[36m";
    return stream;
}

std::ostream& ConsoleColor::white(std::ostream& stream)
{
    stream << "\037[37m";
    return stream;
}
