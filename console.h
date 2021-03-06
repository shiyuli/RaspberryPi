#include <iostream>

#ifndef CONSOLE_H_
#define CONSOLE_H_

typedef std::ostream&(*color_t)(std::ostream&);
// using color_t = std::ostream&(*)(std::ostream&);

class Console
{
public:
    static void info(const char* message);
    static void error(const char* message);
    static void debug(const char* message);
    static void print(const char* message);
    static void print(const char* message, color_t color);
    static void println(const char* message);
    static void println(const char* message, color_t color);

private:
    static void reset();
};

class ConsoleColor
{
public:
    static std::ostream& normal(std::ostream& stream);
    static std::ostream& grey(std::ostream& stream);
    static std::ostream& red(std::ostream& stream);
    static std::ostream& green(std::ostream& stream);
    static std::ostream& yellow(std::ostream& stream);
    static std::ostream& blue(std::ostream& stream);
    static std::ostream& magenta(std::ostream& stream);
    static std::ostream& cyan(std::ostream& stream);
    static std::ostream& white(std::ostream& stream);
};

#else
#endif //CONSOLE_H_
