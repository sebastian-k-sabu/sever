#include <string>
#include <string.h>
#include <iostream>
#include "dataParser.hpp"
#include "urlRouting.hpp"
using namespace std;

string processData(char* data){
     string data_s(data);
     int fristSpace = data_s.find(" ");
     string methodType = data_s.substr(0,fristSpace);

     int firstQuestionMark = data_s.find("?");
     int secondSpace = data_s.find(" ",fristSpace+1);
     int endOfURL = (firstQuestionMark != -1&&firstQuestionMark<secondSpace)? firstQuestionMark : secondSpace ;
     string URL = data_s.substr(fristSpace+1,endOfURL-fristSpace-1);
     
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char formattedTime[80];
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", localTime);
     cout << formattedTime <<" ";
     cout << methodType<<" ";
     cout << URL<< " requested"<<endl;

     if(methodType == "GET")
        return checkRoute(URL);
    else return " ";
}