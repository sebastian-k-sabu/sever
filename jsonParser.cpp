#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
#include "jsonParser.hpp"
using namespace std;

union jsonValue
{
    int n;
    double d;
    string* s;
    map<string,jsonValue>* json;
};


string removeSpace(string s){
    int start = s.find("\r\n\r\n");
    string body = s.substr(start+4,s.length());
    body.erase(remove_if(body.begin(), body.end(),::isspace), body.end());
    cout<<body<<endl;
    return body;

}

jsonValue fristJsonParser(string s){
    int valueEnd;
    jsonValue jsonParsed;

    if(s.at(0) == '{')
      if (s.at(1) == '\"')
      {
        string key = "";
        int keyStart = s.find('\"');
        int keyEnd = s.find('\"',keyStart+1);
        key += s.substr(keyStart,keyEnd-keyStart);
        
        if(s.at(keyEnd+2) == '\"'){
           string value = "";
           int valueStart = s.find('\"',keyEnd+1);
           valueEnd = s.find('\"',valueStart+1);
           value += s.substr(valueStart,valueEnd-valueStart);
           jsonValue json_1;
           json_1.s = &value;
           map<string,jsonValue> currentElemtent = {{key,json_1}};
           jsonParsed.json = &currentElemtent;

        }

      }else if(s.at(valueEnd) == '}'){
        return jsonParsed;
      }
      else if(s.at(valueEnd) == ',')
        return jsonParsed;
    return jsonParsed;
}

string secondJsonParser(string s,jsonValue * jsonParsed){

}