#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<errno.h>
#include<string.h>
void main()
{
int sock,len,len1,fromlen,count=0;
char string[50]="\0";
struct sockaddr_in server;
struct sockaddr_in from;
if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
{
perror("socket: ");
exit(-1);
}
server.sin_family = AF_INET;
server.sin_port = htons(22930);
server.sin_addr.s_addr = inet_addr("127.0.0.1");
bzero(&server.sin_zero,8);//line 18-26 were based on Beej Tutorial
printf("The Server AND is up and running using UDP on port %d.\n",htons(server.sin_port));
len = sizeof(struct sockaddr_in);  

if ((bind(sock,(struct sockaddr *)&server, len)) == -1)
{
perror("bind");
exit(-1);
}//line 30-34 were based on Beej Tutorial

while(1)
{count++;
if(count == 1){printf("The Server AND start receiving lines from the edge server for AND computation.The computation results are:\n");}
int num11;
if ((num11= (recvfrom(sock,string,1024,0,(struct sockaddr*)&from,&len)))== -1)
{perror("receive");
exit(-1);}//line 40-42 were based on Beej Tutorial
string[num11]='\0';
char string11[20];
if (string[0]=='a') strcpy(string11,string+4);
if (string[0]=='o') strcpy(string11,string+3);
//printf("%s",string11);
int number=0,length=0,comma=0,enter=0;//separating the two strings
length = strlen(string11);

for(int i=0; string11[i] != '\0';i++)
{
if (string11[i] == ',') comma = i;
enter = strlen(string11);
}
//printf("%d,%d,%d\n",comma,enter,length);//The code is for testing purpose.
char string1[20]="\0";
strncpy(string1,string11,comma);
string1[comma]='\0';
//printf("%s\n",string1);//The string1 prints.

int binary1=0;

for(int k=0;string1[k] !='\0';++k)
{
binary1= (binary1*2 + string1[k] - '0'); 
}
//printf("%d\n",binary1);//String1 converts to binary1(printf for testing purpose).
char *cd;
char string2[20]="\0";
int binary2=0;
cd = strchr(string11,'$');
if(cd == 0){strncpy(string2,string11+comma+1,enter-comma);
string2[enter-comma]='\0';


for(int m=0;m != (enter-comma-1);++m)
{
binary2= (binary2*2 + string2[m] - '0'); 
}}
if(cd !=0) {strncpy(string2,string11+comma+1,enter-comma-2);
string2[enter-comma-1]='\0';


for(int m=0;m != (enter-comma-2);++m)
{
binary2= (binary2*2 + string2[m] - '0'); 
}}


//printf("%s\n",string2);//The string2 prints.


//printf("%d\n",binary2);//String2 converts to binary2(printf for testing purpose).

int and_result;

and_result = binary1 & binary2; //and binary1,binary2,get the and_result.

//printf("%d\n",and_result);//testing purpose.
int n,i=0;//This part is to convert the number into its binary representation.
n = and_result;
char string3[20]="\0";
if(n==0) string3[0]='0'; 
while(n!=0)//convertes the binary into ASCII
{
string3[i]=(n%2+48);
i++;
n=n/2;
}
int length1;
length1 = strlen(string3);
int f;
for(int j=0;j<length1/2;j++)//to print in the right order
{
f = string3[j];
string3[j] = string3[length1-j-1];
string3[length1-j-1] = f;
}
//printf("%s\n",string3);
printf("%s and %s = %s\n",string1,string2,string3);//print the results message
char *cc;
cc = strchr(string,'$');
if(cc){
printf("The Server AND has successfully received %d lines from the edge server and finished all AND computations.\n",count);
printf("The Server AND has successfully finished sending all computation results to the edge server.\n");} 
if((sendto(sock,string3,20,0,(struct sockaddr*)&from,len))==-1)
{perror("Sendto");
exit(-1);}//line 127-129 were based on Beej Tutorial
} 
}
