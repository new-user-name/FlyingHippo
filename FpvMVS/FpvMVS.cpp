#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
# include <stdio.h>
# include <stdint.h>
# include "Unistd.h"
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <winsock2.h>
//# include <arpa/inet.h>



#pragma pack(push, 1)
struct fpv
{
    uint32_t        		len;
    uint8_t         		type;
    uint32_t        		ms;
    uint8_t         		pad[8];
};
#pragma pack(pop)

size_t out(int fd, struct sockaddr_in* to, char* data, size_t len)
{
    int res = 0;

    while (len > 0) {
        size_t n = len;

        if (n > 1400) {
            n = 1400;
        }

        if ((n = sendto(fd, data, n, 0, (struct sockaddr*)to, sizeof(struct sockaddr_in))) > 0) {
            len -= n;
            data += n;
            res += n;
        }
        else {
            if (errno != EAGAIN) {
                printf("write: %s\n", strerror(errno));
            }
            else {
                continue;
            }
            break;
        }
    }
    return res;
}

size_t in(int fd, char* data, size_t len)
{
    int res = 0;

    while (len > 0) {
        size_t n = _read(fd, data, len);
        if (n > 0) {
            len -= n;
            data += n;
            res += n;
        }
        else {
            if (n < 0) {
                if (errno != EAGAIN) {
                    printf("read: %s\n", strerror(errno));
                }
                else {
                    continue;
                }
            }
            break;
        }
    }
    return res;
}

int main(int argc, char* argv[])
{
    struct fpv fpv;
    static char data[8 * 1024 * 1024];
    int i;

    struct sockaddr_in all;
    int on = 1;
    int udp;

    memset(&all, 0, sizeof(all));
    all.sin_family = AF_INET;
    all.sin_addr.s_addr = inet_addr("127.255.255.255");
    all.sin_port = htons(0);

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);

    udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int e = WSAGetLastError();
    int g = setsockopt(udp, SOL_SOCKET, SO_BROADCAST, (const char*)&on, sizeof(on));

    /*int fd = _open("D:/CPP/QTfpv3/QTfpv3/02-05-2021-16-14-53.fpv", O_RDONLY);

    size_t n = _read(fd, (uint8_t*)&fpv, sizeof(fpv));*/

    for (i = 0; i < argc; i++) { // 1*****************
        int fd = _open("D:/CPP/QTfpv3/QTfpv3/02-05-2021-16-14-53.fpv", _O_BINARY, O_RDONLY);
        //                int fd = open(argv[i], O_RDONLY);
        int ms = 0;

        if (fd >= 0) {
            while (1) {
                if (in(fd, (char*)&fpv, sizeof(fpv)) > 0) {
                    int sleep = fpv.ms - ms;
                    if (sleep > 0) {
                        Sleep(sleep);
                    }
                    ms = fpv.ms;

                    if (in(fd, data, fpv.len) > 0) {
                        switch (fpv.type) {
                        case 0:
                            all.sin_port = htons(5000);
                            break;

                        case 2:
                            all.sin_port = htons(14550);
                            break;

                        case 5:
                            all.sin_port = htons(5003);
                            break;

                        default:
                            continue;
                        }

                        out(udp, &all, data, fpv.len);
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            _close(fd);
        }
    }
    return 0;

}
