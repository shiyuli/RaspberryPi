#include <iostream>

class Terminal
{
public:
    Terminal();
    ~Terminal();

    void info(char* message);
    void error(char* message);
} *terminal;
