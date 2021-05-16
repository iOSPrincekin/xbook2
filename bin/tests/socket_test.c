#include "test.h"

#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 4096
int socket_test(int argc, char *argv[])
{
    int sockfd; 
    char sendline[4096]; 
    struct sockaddr_in servaddr; 
    
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { 
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        exit(0); 
    }

    printf("socket ID: %d\n", sockfd); 

    memset(&servaddr, 0, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port =htons(8080); 
    servaddr.sin_addr.s_addr = inet_addr("192.168.0.104");
    printf("connecting...\n"); 
    
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    { 
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno); 
        exit(0); 
    } 
    printf("send msg to server: \n"); 
    strcpy(sendline, "helllo!\n");
    if( send(sockfd, sendline, strlen(sendline), 0) < 0) 
    { 
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
     exit(0); 
    } 
    memset(sendline, 0, 4096);
    if (recv(sockfd, sendline, 256, 0) < 0) {
        printf("recv msg error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0); 
    }
    printf("recv: %s\n", sendline);
    close(sockfd); 
    exit(0);
    return 0;
}

int socket_test2(int argc, char *argv[])
{
    printf("socket2 test start!\n");
        
    int err;
    int my_socke = socket(AF_INET, SOCK_STREAM, 0);
    if (my_socke < 0) {
        printf("create socket failed!\n");
        return -1;
    }
    printf("create socket %d\n", my_socke);
    struct sockaddr_in myaddr;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    myaddr.sin_addr.s_addr = htonl(0);
    myaddr.sin_port = htons(8080);
    myaddr.sin_family = AF_INET;
    
    err = bind(my_socke, (struct sockaddr *) &myaddr, sizeof(struct sockaddr));
    if (err < 0) {
        printf("socket bind failed!\n");
        return -1;
    }

    err = listen(my_socke, 5);
    if (err < 0) {
        printf("socket listen failed!\n");
        return -1;
    }
    printf("listen %d done!\n", my_socke);
    
    int client_sock;
    int count = 0;
    while (count < 3) {
        client_sock = accept(my_socke, NULL, NULL);
        printf("accept %d done!\n", client_sock);
        if (client_sock >= 0) {
            char buf[512];
            memset(buf, 0, 512);
            recv(client_sock, buf, 512, 0);
            printf("recv done %s!\n", buf);
            
            send(client_sock, buf, strlen(buf), 0);
            printf("send done!\n");

            close(client_sock);
            count++;
        }
    }
    return 0;
}

#define SERVER_IP   "192.168.0.104"
#define BUF_LEN 512
int socket_test3(int argc, char *argv[])
{
    printf("socket3 test start!\n");
    /* udp连接 */
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        printf("create socket failed!\n");
        return -1;
    }
    printf("create socket %d\n", fd);

    struct sockaddr_in serv_addr;
    
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_addr.s_addr = IPADDR_ANY;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_len = sizeof(struct sockaddr_in);
    printf("binding socket %d\n", fd);
    if (bind(fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0) {
        printf("bind socket %d failed!\n", fd);
        return -1;
    }
    printf("binding socket %d done\n", fd);
    
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_addr.s_addr = inet_addr("192.168.0.104");
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_len = sizeof(struct sockaddr_in);
    
    struct sockaddr src;
    socklen_t srclen;
    char *sndbuf = "hello! Test!\n";
    
    while (1) {
        char buf[BUF_LEN] = {0};
        recvfrom(fd, buf, BUF_LEN, 0, &src, &srclen);
        printf("recvfrom: %s\n", buf);
        
        if (!strcmp(buf, "quit")) {
            break;
        }

        printf("sendto: %s\n", sndbuf);
        if (sendto(fd, sndbuf, strlen(sndbuf), 0, (struct sockaddr *)&src, srclen) < 0)
            fprintf(stderr, "sendto: error\n");
    }
    close(fd);
    return 0;
}

int socket_test4(int argc, char *argv[])
{
    printf("socket4 test start!\n");
    
    /* 地址转换函数测试 */
    printf("htonl: %x -> %x\n", 0x1234abef, htonl(0x1234abef));
    printf("htons: %x -> %x\n", 0x1234, htons(0x1234));
    printf("ntohl: %x -> %x\n", 0x1234abef, ntohl(0x1234abef));
    printf("ntohs: %x -> %x\n", 0x1234, ntohs(0x1234));
    
    struct in_addr inp;
    inp.s_addr = inet_addr("192.168.0.1");
    printf("inet_addr: %s -> %x\n", "192.168.0.1", inp.s_addr);
    printf("inet_ntoa: %x -> %s\n", inp.s_addr, inet_ntoa(inp));

    inet_aton("127.0.0.1", &inp);
    printf("inet_aton: %s -> %x\n", "127.0.0.1", inp.s_addr);
    printf("inet_ntoa: %x -> %s\n", inp.s_addr, inet_ntoa(inp));

    
    const char *ip = "127.0.0.1";
    struct sockaddr_in address;
    address.sin_port = htons(8080);//little to big
    inet_pton(AF_INET, ip, &address.sin_addr);
    printf("inet_pton: %s -> %x\n", ip, address.sin_addr);

    char dest[100] ;
    inet_ntop(AF_INET, &address.sin_addr,dest,100);
    printf("inet_ntop: %x -> %s\n", address.sin_addr, dest);
    return 0;
}