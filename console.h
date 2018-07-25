#include <iostream>

#ifndef CONSOLE_H_
#define CONSOLE_H_

typedef std::ostream&(*getColor)(std::ostream&);

getColor colors[2] = { normal, red };

class Console
{
public:
    static void info(char* message);
    static void error(char* message);

private:
    static void print(char* message, std::ostream& color);
};

class Color
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

#endif //CONSOLE_H_
