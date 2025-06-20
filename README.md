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
example Log

```bash 
bind succesful
2025-06-20 17:11:29 server started
2025-06-20 17:11:29 127.0.0.1 connected
thread 0 is handaling
GET /home HTTP/1.1
User-Agent: PostmanRuntime/7.44.1
Accept: */*
Cache-Control: no-cache
Postman-Token: 6ac3492b-0ee1-49dd-885a-0939d8fd5a16
Host: localhost:8080
Accept-Encoding: gzip, deflate, br
Connection: keep-alive


2025-06-20 17:11:35 GET /home requested
2025-06-20 17:11:35 HTTP/1.1 200 OK
Content-Type:text/html
Content-Length: 237

<!DOCTYPE html><html><head>    <title>My Page</title>    <link rel="stylesheet" href="/style.css"></head><body>    <h1>Welcome to my server!</h1>    <button id="myButton">Click me</button>    <script src="/app.js"></script></body></html> response sent
thread 0 is handaling
GET /app.js HTTP/1.1
User-Agent: PostmanRuntime/7.44.1
Accept: */*
Cache-Control: no-cache
Postman-Token: dada7a73-d980-4856-82ab-778037dfc7ef
Host: localhost:8080
Accept-Encoding: gzip, deflate, br
Connection: keep-alive


2025-06-20 17:11:42 GET /app.js requested
2025-06-20 17:11:42 HTTP/1.1 200 OK
Content-Type:application/javascript
Content-Length: 32

console.log("js script loaded"); response sent
thread 0 is handaling
GET /style.css HTTP/1.1
User-Agent: PostmanRuntime/7.44.1
Accept: */*
Cache-Control: no-cache
Postman-Token: 0cfc57b0-27ab-49a3-b418-558127616e52
Host: localhost:8080
Accept-Encoding: gzip, deflate, br
Connection: keep-alive


2025-06-20 17:11:49 GET /style.css requested
2025-06-20 17:11:49 HTTP/1.1 200 OK
Content-Type:text/css
Content-Length: 19

h1{    color: red;} response sent
thread 0 is handaling
GET /about HTTP/1.1
User-Agent: PostmanRuntime/7.44.1
Accept: */*
Cache-Control: no-cache
Postman-Token: 04df3677-0780-4f9a-8a2c-eb8b5dc08ef3
Host: localhost:8080
Accept-Encoding: gzip, deflate, br
Connection: keep-alive


2025-06-20 17:11:54 GET /about requested
2025-06-20 17:11:54 HTTP/1.1 200 OK
Content-Type:text/html
Content-Length: 14

<h1>ABOUT</h1> response sent
 ```

# work remaining

## 4 Json Parser: 
#### Therefore donot complie jsonParser.cpp

