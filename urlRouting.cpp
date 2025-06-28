#include "urlRouting.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "log.hpp"
using namespace std;
string web = "static/";

string getFILE(string URL){
    ifstream f(URL);
    int dotPosition = URL.find(".");
    string contentType = URL.substr(dotPosition,URL.length()-dotPosition);
    map<string, string> contentTypeList = {
    {".html", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".png", "image/png"},
    {".jpg", "image/jpeg"}
    };
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return " ";
    }
    string s;
    string temp;

    while (getline(f, temp))
        s += temp;

    f.close();

    string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type:"+contentTypeList.at(contentType)+"\r\n";
    response += "Content-Length: " + std::to_string(s.length()) + "\r\n";
    response += "\r\n";
    response +=  s;
    cout<<getCurrentTime()<<" "<<response<<" response sent"<<endl;
    return response;

       
}
string checkRoute(string URL){
    vector<string> acceptedRoutes = {"/","/home","/home.html","/app.js","/style.css","/contacts","/contacts.html","/about","/about.html"};
    int validURL = 0;
    for (int i = 0; i < acceptedRoutes.size(); i++)
    {
        if(URL == acceptedRoutes.at(i))
        {
            validURL = 1;
            break;
        }
    }
    if(validURL){
      if(URL == "/"||URL == "/home"||URL == "/home.html")
      {
        return getFILE(web+"home.html");
      }else if(URL == "/contacts"||URL == "/contacts.html")
       {
        return getFILE(web+"contacts.html");
       }
       else if(URL == "/about"||URL == "/about.html")
       {
        return getFILE(web+"about.html");
       }
       else if(URL == "/app.js")
       {
        return getFILE(web+"app.js");
       }
       else if(URL == "/style.css")
       {
        return getFILE(web+"style.css");
       }
    }
    return getFILE(web+"404.html");
}