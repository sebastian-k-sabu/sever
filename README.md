For setup compile all the source file with .cpp extention for linux
g++ -std=c++11 -pthread main.cpp urlRouting.cpp dataParser.cpp
Run this in ur terminal
then run
./a.out or the file that is created
if the acces to any static file is denied make it give permission to the file

use postman for testing

make sure to use urls 
"/",
"/home",
"/home.html",
"/app.js",
"/style.css",
"/contacts",
"/contacts.html",
"/about",
"/about.html"

work completed:

## 1 Basic Server
handles get request for now

## 2 MultiThreading
has a threadpool may still lack some security featues.Uses mutex and conditional_varibles for accesing clientQueue

## 3 Loging events
Logs client request method type and respose.
needs to be polished

# work remaining

## 4 Json Parser: 
#### Therefore donot complie jsonParser.cpp
