#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<errno.h>
#include<arpa/inet.h>
void main()
{
char *l=0,*k=0;
int comma=0;
int percent=0;
int sockfd,newsockfd,client,number=0;
int o=0; 
int an=0;
char store[1024];
memset(store,0,1024);
char buffer[256];
memset(buffer,0,256);
char special[2]="%";
char special1[2]="@";//initialization. 
struct sockaddr_in serv_addr, cli_addr;
int n;
int i=0;
printf("The edge server is up and running.\n");

sockfd = socket(AF_INET,SOCK_STREAM,0);//I wrote line 30-50 based on the Beej Tutorial.
if(sockfd<0)
perror("ERROR opening the socket");

bzero((char *)&serv_addr,sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr= inet_addr("127.0.0.1");
serv_addr.sin_port=htons(23930);
if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
perror("ERROR on binding");
listen(sockfd,5);
while(1){i++;
client=sizeof(cli_addr);
newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&client);
if(newsockfd<0) perror("ERROR on accept");
bzero(buffer,256);
n = read(newsockfd,buffer,255);
if (n<0) perror("ERROR from reading the socket");
//printf("Here is the message:%s\n",buffer);
//n = write(newsockfd,buffer,sizeof(buffer)); for testing purpose 
if (n<0) perror("ERROR from writing the socket");
strcat(store,buffer);
strcat(store,special);
//printf("%s\n",store);
if(buffer[0]=='o'){o++;} //calculating the number of OR instructions
if(buffer[0]=='a') {an++;}//calculating the number of AND instructions
if(l==0){l = strchr(buffer,'$');}
if(k==0){k = strchr(buffer,'#');}
if((l!=0)&&(k!=0)){
number = o + an;
printf("The edge server has received %d lines from the client using TCP over port %d.",number,htons(serv_addr.sin_port));

if (k!=0){printf("The edge server has successfully sent %d lines to Backend-Server OR.\n",o);}
if (l!=0){printf("The edge server has successfully sent %d lines to Backend-Server AND.\n",an);

}}//the printing message 
int sock,len,fromlen;//tcp part initialization
char buffer1[20]="0000000000000000000\0";//most part of line 67-106 is based on Beej tutorial.
struct sockaddr_in server;
struct sockaddr_in client;
int length = sizeof(struct sockaddr_in);
sock = socket(AF_INET,SOCK_DGRAM,0);
client.sin_port = htons(24930);
if(sock<0){
perror("socket");
exit(-1);
}
client.sin_family = AF_INET;
client.sin_port = htons(24930);
client.sin_addr.s_addr = inet_addr("127.0.0.1");
bzero(&client.sin_zero,8);
if((bind(sock,(struct sockaddr *)&client,length)) == -1)
{
perror("bind");
exit(-1);
}
server.sin_family = AF_INET;
if(buffer[0]=='o')    {server.sin_port = htons(21930);}
if(buffer[0]=='a')    {server.sin_port = htons(22930);}
server.sin_addr.s_addr = inet_addr("127.0.0.1");
bzero(&server.sin_zero,8);
if ((sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&server,length))==-1)
{
perror("sendto");
exit(-1);
}
if((l!=0)&&(k!=0)){printf("The edge server start receiving the computation results from Backend-Server OR and Backend-Server AND using UDP over port %d.\n",htons(client.sin_port));
printf("The computation results are:\n");
//if(buffer[0]=='a') printf("%s",buffer);
//if(buffer[0]=='o') printf("%s",buffer);
}


if ((recvfrom(sock,buffer1,30,0,(struct sockaddr*)&server,&length))==-1)
{
perror("receive");
exit(-1);}


//int c = strlen(buffer1);
//buffer1[c]='\0';
n = write(newsockfd,buffer1,sizeof(buffer1));
//printf("%s\n",buffer1);
strcat(store,buffer1);
strcat(store,special1);//store all the results to one string.
if((l!=0)&&(k!=0)){//printf("%s\n",store);
int len11 = sizeof(store);
store[len11]='\0';
const char s[2] ="@";
const char t[2] ="%";
const char w[2] ="#";
const char v[2] ="$";
char *token;
int comma=0;
int percent=0;
int u=0;
char chr='\0';
token =&chr;
char string1[40]="\0";
char string2[40]="\0";
char string3[40]="\0";
char string4[40]="\0";
char separate[80]="\0";
token =strtok(store,s);//initialization of separating the results.
while  (token !=NULL){
comma=0;
percent=0;
u=0;

while (store[u]!='@'){
u++;
}
strcpy(separate,token);
if(separate[0]=='a'){//for case 'AND'
strcpy(string1,separate+4);
//int len12 = sizeof(string1);
string1[u-4]='\0';
for (int d=0;string1[d]!='\0';d++){
if (string1[d]==',') comma=d;
if (string1[d]=='%') percent=d;}
strncpy(string2,string1,comma);
string2[comma]='\0';
if(strstr(string1,v)){
strncpy(string3,string1+comma+1,percent-comma-2);//the first string to be operated
string3[percent-comma-2]='\0';
}
else{
strncpy(string3,string1+comma+1,percent-comma-1);
string3[percent-comma-1]='\0';}
strcpy(string4,string1+percent+1);//the second string to be operated
int len14 = sizeof(string4);
string4[len14]='\0';
printf("%s and %s = %s\n",string2,string3,string4);
}
if(separate[0]=='o'){//for case 'OR'
strcpy(string1,separate+3);
//int len13 = sizeof(string1);
string1[u-3]='\0';
for (int d1=0;string1[d1]!='\0';d1++){
if (string1[d1]==',') comma=d1;
if (string1[d1]=='%') percent=d1;}
strncpy(string2,string1,comma);
string2[comma]='\0';
if (strstr(string1,w)){strncpy(string3,string1+comma+1,percent-comma-2);
string3[percent-comma-2]='\0';}
else {strncpy(string3,string1+comma+1,percent-comma-1);
string3[percent-comma-1]='\0';}
strcpy(string4,string1+percent+1);
int len15 = sizeof(string4);
string4[len15]='\0';
printf("%s or %s = %s\n",string2,string3,string4);
}
token = strtok(NULL,s);//take the next string 
}
printf("The edge server has successfully finished receiving all computation results from the Backend-Server OR and Backend-Server AND.\n");
printf("The edge server has successfully finished sending all computation results to the client.\n");
memset(store,0,1024);
memset(buffer,0,256);
l=0,k=0;
i=0;
number=0;//reinitialize the values
}
//printf("%d\n",ntohs(client.sin_port));

close(sock);
close(newsockfd);//close the socket 

}

}
