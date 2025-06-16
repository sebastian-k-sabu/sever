#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include "dataParser.hpp"
#include "urlRouting.hpp"
#include "jsonParser.hpp"
#include <thread>
#include <ctime>

#define PORT 8080

using namespace std;

void handleClinet(int* clientSocket){
    while(*clientSocket > 0){
    char buffer[1024] = {0};

    recv(*clientSocket,buffer,sizeof(buffer),0);
    string sentData = processData(buffer);
    //removeSpace(buffer);

    
    send(*clientSocket, sentData.c_str(),sentData.length(),0);


    }
    close(*clientSocket);
}

int main(){
//Main socket that lsitens to client
int serverSocket = socket(AF_INET,SOCK_STREAM, 0);

//stores server address and deatils in sockaddr_in later we have to convert it to sockaddr type
sockaddr_in serverAddress;

serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(PORT);
serverAddress.sin_addr.s_addr = INADDR_ANY; //usualy localhost


//bind
if(bind(serverSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
 cout << "falied to bind"<< endl;
 return 0;
}
else { 
 cout<<"bind succesful"<<endl;
}

if (listen(serverSocket,5)<0)
{
 cout<<"falied to listen"<< endl;
 return 0;
}

time_t now = time(0);
tm* localTime = localtime(&now);

char formattedTime[80];
strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", localTime);
cout << formattedTime <<" server started"<<endl;
int serverRun = 1;

while (serverRun)
{   
    //client address
    sockaddr_in clientAddress;
    int addrlen = sizeof(clientAddress);
     
    int clientSocket = accept(serverSocket,(struct sockaddr*)&clientAddress,(socklen_t*)&addrlen);
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);

    char formattedTime[80];
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", localTime);
    cout << formattedTime<<" "<<clientIP<<" connected"<<endl;

    //serverRun = 0;
    thread(handleClinet,&clientSocket).detach();
    //handleClinet(&clientSocket);
}

} 