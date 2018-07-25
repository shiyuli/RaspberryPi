#include <iostream>

class Console
{
public:
    void info(char* message);
    void error(char* message);

private:
    void print(char* message, std::ostream& color);
} *console;

class Color
{
public:
    static std::ostream& grey(std::ostream& stream);
    static std::ostream& red(std::ostream& stream);
    static std::ostream& green(std::ostream& stream);
    static std::ostream& yellow(std::ostream& stream);
    static std::ostream& blue(std::ostream& stream);
    static std::ostream& magenta(std::ostream& stream);
    static std::ostream& cyan(std::ostream& stream);
    static std::ostream& white(std::ostream& stream);
} color;
