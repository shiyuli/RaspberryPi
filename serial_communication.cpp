#include "serial_communication.h"

Serial::Serial()
{
}

Serial::~Serial()
{
}

bool Serial::Open(const char* port_name)
{
    struct termios options;
    memset(&options, 0, sizeof(options));
    int status;

    if((m_fd = open(port_name, O_RDWR | O_NDELAY | O_NONBLOCK)) == -1)
    {
        // printf("error %d opening %s: %s", errno, port_name, strerror(errno));
        return false;
    }

    fcntl(m_fd, F_SETFL, O_RDWR);

    if(tcgetattr(m_fd, &options) != 0)
    {
        // printf("error %d from tcgetattr", errno);
        return false;
    }

    cfmakeraw(&options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    options.c_cflag |= (CLOCAL | CREAD);        //ignore modem controls,
    options.c_cflag &= ~PARENB;      //shut off parity
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;

    options.c_cc[VMIN] = 0;    //read doesn't block
    options.c_cc[VTIME] = 100; //10 seconds read timeout

    if(tcsetattr(m_fd, TCSANOW, &options) != 0)
    {
        // printf("error %d from tcsetattr", errno);
        return false;
    }

    ioctl(m_fd, TIOCMGET, &status);

    status |= TIOCM_DTR;
    status |= TIOCM_RTS;

    ioctl(m_fd, TIOCMSET, &status);

    usleep(10000); //10ms

    // set_blocking(m_fd, 0); //set no blocking

    return true;
}

void Serial::Close()
{
    close(m_fd);
}

void Serial::Write(const byte message[5])
{
    // byte *data;
    // strcpy(data, message);
    // strcat(data, "\n");
    // int data_length = sizeof(message);

    write(m_fd, message, 5);     //send message
    usleep((5 + 25) * 100); //sleep enough to transmit the message
}

char* Serial::Read(int buffer_length)
{
    if(buffer_length < 1)
    {
        return NULL;
    }

    char message[buffer_length];
    int n = read(m_fd, message, sizeof(message)); //read up to 100 characters if ready to read

    return message;
}
