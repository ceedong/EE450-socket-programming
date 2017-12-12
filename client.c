#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
void error(char *msg){
perror(msg);
exit(-1);
}//This part(line 11-14) is based on Beej Tutorial

int main(int argc,char *argv[])
{
int sockfd,n;
struct sockaddr_in serv_addr;
struct hostent *server;
char buffer[256];
char string[20];//initialization

int i=0,ss=0,count=0,o=0,an=0;
printf("The client is up and running.\n");
FILE *fp;

fp = fopen(argv[1],"r");//open the file by argv[1]
while ((i=getc(fp))!=EOF){
if (i =='\n') count++;
if (i =='o') o++;
if (i =='a') an++;//count the numbers of OR and AND instruction
}


int count1=count;
int o1=o;
int an1=an;
//printf("%d\n",count); for testing purpose 
fp = fopen(argv[1],"r");
printf("The client has successfully finished sending %d lines to the edge server.\n",count);
printf("The client has successfully finished receiving all computation results from the edge server.\n");
printf("The final computation results are:\n");
while(count-- !=0){//scan the string one line a time
fscanf(fp,"%s",string);
sockfd =socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
error("SOCKET");
bzero((char *)&serv_addr,sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
serv_addr.sin_port=htons(23930);//Line 48-52  were based on Beej Tutorial
if(string[0]=='a') {an1--;
if(an1==0){
char string7[20]="$";
strcat(string,string7);
}
}
if(string[0]=='o'){o1--;
if(o1==0){
char string8[20]="#";
strcat(string,string8);
}
}
if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)//line 65-73 was based on Beej Tutorial
error("Connect");
bzero(buffer,256);
n = write(sockfd,string,strlen(string));
if(n<0) error("WRITE");
//bzero(string,20);
n = read(sockfd,buffer,20);
if(n<0) error("READ");
printf("%s\n",buffer);}
return 0;
}
