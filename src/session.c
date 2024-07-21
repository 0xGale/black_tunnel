#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#include "session.h"


void get_addr_string(struct sockaddr_in addr, char buf[INET_ADDRSTRLEN]) {
    char *addr_str;
    addr_str = inet_ntoa(addr.sin_addr);
    strcpy(buf, addr_str);
}