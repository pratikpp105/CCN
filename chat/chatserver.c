#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#define SERVER_TCP_PORT 4778
#define BUFLEN 256
#define MAX 90
int flag=0;
int func(int sockfd){
char buff[MAX];
int n;
for(;;){
if(flag==1)
break;
bzero(buff,MAX);
n=read(sockfd,buff,sizeof(buff));
printf("The message received by client : %s\n",buff);
bzero(buff,MAX);
n=0;
printf("Enter the message to be sent to client: \n");
fgets(buff, sizeof(buff), stdin);
n=strlen(buff);
if(strcmp(buff, "Exit") == 0){
printf("Server Exit");
flag=1;
break;
}
else{
write(sockfd,buff,sizeof(buff));
bzero(buff,MAX);
}
}
}
int main(int argc, char **argv){
int n;
int yes=1;
int sd, new_sd, client_len, port;
struct sockaddr_in server,client;
char buf[BUFLEN];
port=atoi(argv[1]);
if((sd=socket(AF_INET,SOCK_STREAM,0))==-1){
fprintf(stderr,"can't create a socket\n");
exit(1);
}
bzero((char *)&server,sizeof(struct sockaddr_in));
server.sin_family=AF_INET;
server.sin_port=port;
server.sin_addr.s_addr=htons(INADDR_ANY);
if(setsockopt(sd,SOL_SOCKET,SO_REUSEADDR, &yes, sizeof(yes))==-1){
perror("setsockopt");
exit(1);
}
if(bind(sd,(struct sockaddr *)&server,sizeof(server))==-1){
fprintf(stderr,"can't bind name to the socket\n");
exit(1);
}
listen(sd,5);
while(1){
client_len= sizeof(client);
if((new_sd=accept(sd,(struct sockaddr *)&client,&client_len))==-1){
fprintf(stderr,"can't accept client\n");
exit(1);
}
func(new_sd);
close(new_sd);
}
close(sd);
return(0);
}
