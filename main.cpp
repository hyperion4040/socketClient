/*
    C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include <zconf.h>
#include <fstream>


int wyslijPlik(){
    int sfd =0, n=0, b;
    char rbuff[1024];
    char sendbuffer[100];

    struct sockaddr_in serv_addr;

    memset(rbuff, '0', sizeof(rbuff));
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    b=connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (b==-1) {
        perror("Connect");
        return 1;
    }
    std::ofstream outfile("prova.jpg");



    FILE *fp = fopen("prova.jpg", "rb");
    if(fp == NULL){
        perror("File");
        return 2;
    }

    while( (b = fread(sendbuffer, 1, sizeof(sendbuffer), fp))>0 ){
        send(sfd, sendbuffer, b, 0);
    }

    fclose(fp);
    return 0;
}


int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 5000 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    //keep communicating with server
    while(1)
    {
        printf("Wybierz 1 by wysłać tekst, wybierz 2 by wysłać plik : ");
        scanf("%s" , message);
        if (message == "1"){
            printf("Enter message");
            scanf("%s",message);
        } else{
            wyslijPlik();
            break;
        }

        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }

        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }

        puts("Server reply :");
        puts(server_reply);
    }

    close(sock);
    return 0;
}
