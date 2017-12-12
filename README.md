# EE450-socket-programming
This repo is for my socket programming in EE450 by Pro. Ali Zahid during 2017 Spring semester.

## High Level Description 
The assignment requires to implement a simple model of computational offloading where a single client offloads some computation to a server (edge server) which in turn distributes the load over 2 backend servers. The server facing the client then collects the result from the back-end and communicates the same to the client in the required format. As a result, the system is comprised with three different parts:<br>
1) Client: Submit jobs to Google Compute Engine for processing;<br>
2) Edge Server: Communicate with the client, receive the job, dispatch the job to back-end servers, receive their response, build the final output and send the result back to the client;<br>
3) Backend Server: They perform specific computations they are assigned to. In our case, one of the servers performs bitwise "and" and the other performs bitwise "or" operations.<br>
Three servers together constitute "Google Compute Engine" (1 Edge Server and 2 Back End Server). The client and the Edge Server communicates over a TCP connection while the communication between the Edge Server and the Back End Server is connectless and over UDP. This is illustrated in figure below:<br>
![alt text](/figure.png)

## Original Readme.md File (For Grading Purpose)
Implementation: The client.c reads a line from the text file, then transfers it to the edge server over UDP. The edge server then works as a client and transfers the message to Back-End server for further processing. Also the edge server needs to figure out what kind of calculation is the message asking for, OR or AND, to send the message to the corresponding Back-End server over TCP. At back-end server, it converts ASCII message to binary strings and calculate the results, then converts the result again as ASCII and returns it back to the edge server. Finally the edge server will transfer the result message to client over UDP and all messages should be on screen correctly. 

client.c sends text file and receives results after calculating.

edge.c is used for receiving message from client.c over UDP and sends the message to the corresponding back-end server over TCP.

server_and.c and server_or.c are used to receive messages from edge.c over TCP and calculate the results, then transmits the results to the edge server over TCP.

To run the program, my designated TA needs to run server_and.c and server_or.c edge.c respectively(in any order), and then runs the client.c program and types the name of input text file in the command line, which is shown as the following:
./client 1.txt

In my implementation, the strings are sent line by line, data type for transmitting are all ASCII strings but the process in Back-End server involves converting ASCII to binary numbers and vice versa to calculate the results of AND/OR.

Under two cases my project may NOT work well:

CASE 1:the last line ends with a '\n' will not work well.

CASE 2:too large text file may crush because of limited buffer size.

## Credits

Reused Code: For TCP and UDP part in client.c/edge.c/server_or.c/server_and.c, I wrote the relevant codes based on Beej Tutorial. I just comment it in codes and you can see clearly from it.

Specially:<br>
client.c line 11-14 line 48-52 line 65-73<br>
edge.c line 30-50 line 67-106(most part of it)<br>
server_and.c line 18-26 line 30-34 line 40-42 line 127-129<br>
server_or.c line 18-26 line 30-34 line 40-42 line 127-129<br>

They are all from the Beej Tutorial which is provided by TA. 

The Makefile is written based on the link provided by the TA, because I cannot comment on makefile, I just announce here that the structure of makefile is directly from the link.

