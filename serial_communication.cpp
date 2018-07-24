#include "serial_communication.h"

Serial::Serial()
{
}

Serial::~Serial()
{
}

bool Serial::open(char* port_name)
{
    m_fd = open(port_name, O_RDWR | O_NOCTTY | O_SYNC);
    if(m_fd < 0)
    {
        printf("error %d opening %s: %s", errno, port_name, strerror(errno));
        return;
    }

    set_interface_attribs(m_fd, B115200, 0); //set speed to 115, 200 bps, 8n1 (no parity)
    set_blocking(m_fd, 0); //set no blocking
                           //receive 25: approx 100 uS per char transmit
}

void Serial::write(char* message)
{
    char *data = message += "\n";
    int data_length = sizeof(message) + 1;

    write(m_fd, data, data_length);     //send message
    usleep((data_length + 25) * 100); //sleep enough to transmit the message
}

char* Serial::read(int buffer_length)
{
    if(buffer_length < 1)
    {
        return NULL;
    }

    char message[buffer_length];
    int n = read(m_fd, message, sizeof(message)); //read up to 100 characters if ready to read

    return message;
}

int Serial::set_interface_attribs(int fd, int speed, int parity)
{
    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if(tcgetattr(fd, &tty) != 0)
    {
        printf("error %d from tcgetattr", errno);
        return -1;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CSB; //8-bit chars
    //disable IGNBRK for mismatched speed tests, otherwise receive break
    //as \000 chars
    tty.c_iflag &= ~IGNBRK; //disable break processing
    tty.c_lflag = 0;        //no signaling char, no echo
                            //nocaonical processing
    tty.c_oflag = 0;        //no remapping, no delays
    tty.c_cc[VMIN] = 0;     //read doesn't block
    tty.c_cc[VTIME] = 5;    //0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); //shut off xon/xoff ctrl
    tty.c_cfoag |= (CLOCAL | CREAD);        //ignore modem controls,
                                            //enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      //shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if(tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        printf("error %d from tcsetattr", errno);
        return -1;
    }

    return 0;
}

void Serial::set_blocking(int fd, int should_block)
{
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if(tcgetattr(fd, &tty) != 0)
    {
        printf("error %d from tggetattr", errno);
        return;
    }

    tty.c_cc[VMIN] = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5; //0.5 seconds read timeout

    if(tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        printf("error %d setting term attributes", errno);
    }
}
