#include <string>
#include <string.h>
#include <iostream>
#include "dataParser.hpp"
#include "jsonParser.hpp"
#include "urlRouting.hpp"
#include "log.hpp"
using namespace std;
void processValue(const jsonParser::jsonValue& val) {
    switch(val.type) {
        case jsonParser::INT:
            std::cout << "Integer: " << val.intValue << std::endl;
            break;
            
        case jsonParser::DOUBLE:
            std::cout << "Double: " << val.doubleValue << std::endl;
            break;
            
        case jsonParser::STRING:
            if (val.stringValue) { // Always check pointer
                std::cout << "String: " << *val.stringValue << std::endl;
            }
            break;
            
        case jsonParser::JSON_OBJECT:
            if (val.objectValue) { 
                for (const auto& [key, value] : *val.objectValue) {
                    std::cout << "Key: " << key << " => ";
                    processValue(value); 
                }
            }
            break;
    }
}

string processData(char* data){
     string data_s(data);
     int fristSpace = data_s.find(" ");
     string methodType = data_s.substr(0,fristSpace);

     int firstQuestionMark = data_s.find("?");
     int secondSpace = data_s.find(" ",fristSpace+1);
     int endOfURL = (firstQuestionMark != -1&&firstQuestionMark<secondSpace)? firstQuestionMark : secondSpace ;
     string URL = data_s.substr(fristSpace+1,endOfURL-fristSpace-1);
     int headerEnd = data_s.find("\r\n\r\n");
     string jsonData = data_s.substr(headerEnd);
     jsonParser jp(jsonData);
     jsonParser::jsonValue result = jp.parse();
     processValue(result);
     cout << getCurrentTime() <<" ";
     cout << methodType<<" ";
     cout << URL<< " requested"<<endl;

     if(methodType == "GET")
        return checkRoute(URL);
    else return " ";
}