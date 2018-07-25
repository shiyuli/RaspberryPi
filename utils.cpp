#include "utils.h"

int str_to_int(char* s)
{
    std::stringstream ss;
    ss << s;
    int i;
    ss >> i;

    return i;
}
