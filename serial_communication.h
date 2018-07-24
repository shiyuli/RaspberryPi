#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

typedef unsigned char byte;

class Serial
{
public:
    Serial();
    ~Serial();

    bool Open(const char* port_name);
    void Write(const byte message[5]);
    char* Read(int buffer_length);

private:
    int set_interface_attribs(int fd, int speed, int parity);
    void set_blocking(int fd, int should_block);

private:
    int m_fd;
};

/*
enum speed
{
    B115200,
    B230400,
    B9600,
    B19200,
    B38400,
    B57600,
    B1200,
    B2400,
    B4800
  //...
};
*/
