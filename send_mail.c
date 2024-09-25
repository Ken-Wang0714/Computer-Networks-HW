#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

int main(int argc, char** argv) 
{
    int i;
    struct sockaddr_in addr;
    //commands for server
    //char* commands[] = {"eclo localhost\n", "mail from:send@example.com\n", "rcpt to:M11115026@mail.ntust.edu.tw\n", "data\n", "Subject: send test\n\nKen qazwsx\n", "\n.\n", "quit\n"};

    //creating socket
    int sock = socket(AF_INET, SOCK_STREAM , 0);
    if(sock < 0)
    {
        perror("error with creation of socket");
        return -errno;
    }

    //parameters
    addr.sin_family = AF_INET;
    //port 25
    addr.sin_port = htons(25);

    // Inet 127.0.0.1.
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //connecting to server
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
    {
    perror("error with creation of socket");
        return -errno;
    }

    //sending commands

    char* link[] = {"eclo localhost\n"};
    char sender[40];
    char recv[40];
    char data[200];
    char str1[] = "mail from:";
    char str2[] = "rcpt to:";
    char str3[] = "\n";
    char str4[] = "\n.\n";
    char str5[] = "quit\n";
    char str6[] = "data\n";
    
    send(sock, link[0], strlen(link[0]), 0);

    printf("Enter your mail addr:");
    scanf("%s",sender);
    int len = strlen(str1) + strlen(sender) + strlen(str3) +1;
    char sender_info[len];
    memset(sender_info, '\0', len);
    strcat(sender_info, str1);
    strcat(sender_info, sender);
    strcat(sender_info, str3);
    //printf("%s",sender_info);
    send(sock, sender_info, strlen(sender_info), 0);
    
    printf("Enter rcpt addr:");
    scanf("%s",recv);
    int len_rev = strlen(str2) + strlen(recv) + strlen(str3) +1;
    char recv_info[len_rev];
    memset(recv_info, '\0', len);
    strcat(recv_info, str2);
    strcat(recv_info, recv);
    strcat(recv_info, str3);
    //printf("%s",recv_info);
    send(sock, recv_info, strlen(recv_info), 0);

    send(sock, str6, strlen(str6), 0);
    printf("Enter data(Enter * to end):\n");
    scanf("%[^*]",data);
    //printf("%s",data);
    int len_data =+ strlen(data) + strlen(str3) +1;
    char data_info[len_data];
    memset(data_info, '\0', len);
    strcat(data_info, data);
    strcat(data_info, str3);
    send(sock, data_info, strlen(data_info), 0);

    send(sock, str4, strlen(str4), 0);
    send(sock, str5, strlen(str5), 0);

    close(sock);

    return (EXIT_SUCCESS);
}