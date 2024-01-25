#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
main( )
{
int s, r, recb,sntb, x;
int ca;
printf(”INPUT port number: ”);
scanf(”%d ”,&x);
socklen_t len;
struct sockaddr in server , client;
char buff[50];
s=socket(AF_INET , SOCK_DGRAM, 0 ) ;
if(s==−1)
{
printf(”\nSocket creation error.”);
exit(0);
}
printf(”\nSocket created.”);
server.sin_family =AF_INET ;
server.sin_port=htons(x);
server.sin_addr.s_addr=htonl(INADDR_ANY) ;
len= sizeof(client);
ca= sizeof(client);
r = bind( s , (struct sock_addr∗)&server , sizeof(server));
if(r==−1)
{
printf(”\nBinding error.”);
exit(0);
}
printf(”\nSocket binded.”);
while(1){
recb=recvfrom(s , buff, sizeof(buff), 0, (struct sock_addr∗)&client,&ca);
if(recb==−1)
{
printf(”\nMessage Recieving Failed”);
close(s);
exit(0);
}
printf(”\nMessage Recieved:”);
printf(”%s”,buff);
if(!strcmp(buff,”stop”))
break;
printf(”\n\n”);
printf(”Type Message:”);
scanf(”%s”,buff);
sntb=sendto(s,buff,sizeof(buff),0,(struct sock_addr∗)&client,len);
if(sntb==−1)
{
printf(”\nMessage SendingFailed”);
close(s);
exit(0);
}
if(!strcmp(buff,”stop”))
break;
}
close(s);
}
