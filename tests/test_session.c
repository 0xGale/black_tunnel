#include <arpa/inet.h>
#include <stdio.h>

#include "session.h"

void main() {
    char buf[INET_ADDRSTRLEN];
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(2000);
    inet_aton("192.168.0.255", &addr.sin_addr);
    
    get_addr_string(&addr, buf);
    printf("%s\n", buf);
}
