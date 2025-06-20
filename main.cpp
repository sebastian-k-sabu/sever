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
#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>

#define PORT 8080

using namespace std;

const int threadSize = 8;
vector<thread> threadPool;
queue<int> clientQueue;
mutex mainLock; //this lock when server pushs data
mutex mtx;  // this lock when thread access data
condition_variable cv;
void stopThreadPool() {
    cv.notify_one();
    for(auto& t : threadPool) {
        if(t.joinable()) t.join();
    }
}
void handleClinet(int i);
int createThreadPool() {
    for (int i = 0; i < threadSize; i++) {
        threadPool.emplace_back(handleClinet,i);
    }
    return 0;
}


void handleClinet(int i){
    while(true){//keeps looping for checking element in queue
            unique_lock<mutex> lock(mtx);
            cv.wait(lock,[] {return !clientQueue.empty();});
            int clientSocket = clientQueue.front();
            clientQueue.pop();
            lock.unlock();
            
            while (true)//keeps looping to server client 
            {
                
                char buffer[1024] = {0};
                recv(clientSocket,buffer,sizeof(buffer),0);
                cout<< "thread "<<i<<" is handaling"<<endl;
                cout << buffer<<endl;
                string sentData = processData(buffer);
                //removeSpace(buffer);
                    if(sentData == "quit")
                        break;
                 send(clientSocket, sentData.c_str(),sentData.length(),0);
            }
    
    close(clientSocket);

    }
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
createThreadPool();
while (serverRun)
{   
    //client address
    sockaddr_in clientAddress;
    int addrlen = sizeof(clientAddress);
     
    int clientSocket = accept(serverSocket,(struct sockaddr*)&clientAddress,(socklen_t*)&addrlen);
    mainLock.lock();
    clientQueue.push(clientSocket);
    cv.notify_all();
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);

    char formattedTime[80];
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", localTime);
    cout << formattedTime<<" "<<clientIP<<" connected"<<endl;

    //serverRun = 0;
    //handleClinet(&clientSocket);
}
  stopThreadPool();
} 