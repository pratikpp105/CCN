#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#define BUFLEN 256
#define MAX 80
void func(int sockfd){
char buff[MAX];
int n;
for(;;){
bzero(buff,sizeof(buff));
printf("Enter message to be sent: \n");
n=0;
fgets(buff, sizeof(buff), stdin);
if(strcmp(buff, "Exit") == 0){
printf("Client Exit..\n");
break;
}
n=strlen(buff);
write(sockfd,buff,n);
bzero(buff,sizeof(buff));
read(sockfd,buff,sizeof(buff));
printf("Message From Server : %s",buff);
}
}
int main(int argc, char **argv){
int n;
int sd,port;
char buff[BUFLEN];
struct sockaddr_in server;
port=atoi(argv[1]);
if((sd=socket(AF_INET,SOCK_STREAM,0))==-1){
fprintf(stderr,"can't create a socket\n");
exit(1);
}
bzero((char *)&server,sizeof(struct sockaddr_in));
server.sin_family=AF_INET;
server.sin_port=port;
server.sin_addr.s_addr=inet_addr("172.16.30.59");
if(connect(sd,(struct sockaddr *)&server, sizeof(server))==-1){
fprintf(stderr,"can't connect\n");
exit(1);
}
func(sd);
close(sd);
return(0);

}
