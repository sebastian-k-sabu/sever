#include "urlRouting.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>


using namespace std;
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
        //cerr << "Error opening the file!";
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
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char formattedTime[80];
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", localTime);
    cout<<formattedTime<<" "<<response<<" response sent"<<endl;
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
        return getFILE("home.html");
      }else if(URL == "/contacts"||URL == "/contacts.html")
       {
        return getFILE("contacts.html");
       }
       else if(URL == "/about"||URL == "/about.html")
       {
        return getFILE("about.html");
       }
       else if(URL == "/app.js")
       {
        return getFILE("app.js");
       }
       else if(URL == "/style.css")
       {
        return getFILE("style.css");
       }
    }
    return getFILE("error.html");
}