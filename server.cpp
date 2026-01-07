#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>


int main() {
    int status = 1, sockfd, option = 1;
    struct addrinfo hints, *node, *workingaddr;
    struct sigaction sa;
    memset(node, 0, sizeof(node));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((status = getaddrinfo(NULL, "3490", &hints, &node)) != 0) {
        return -1;
    }

    for(workingaddr = node; workingaddr != nullptr; workingaddr = workingaddr->ai_next) {
        if((sockfd = socket(workingaddr->ai_family, workingaddr->ai_socktype, workingaddr->ai_protocol)) == -1) {
            continue;
        }

        if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1) {
            return -1;
        }

        if(bind(sockfd, workingaddr->ai_addr, workingaddr->ai_addrlen) == -1) {
            continue;
        }

        break;
    }

    freeaddrinfo(node);

    if(workingaddr == nullptr) {
        return -1;
    }
}