#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
#include "jsonParser.hpp"
using namespace std;

class jsonParser
{
private:
    enum type{
        INT,
        DOUBLE,
        STRING,
        JSON,

    };
    struct jsonValue
    {
        type Type;
        union 
        {
            int n;
            double d;
            string s;
            jsonValue* json;
        };
        jsonValue() {
            Type = type(INT);
            n = 0;
        }

        jsonValue(int value){
            Type = type(INT);
            n = value;
        }

        jsonValue(double value){
            Type = type(DOUBLE);
            d = value;
        }

        jsonValue(const std::string& value){
            Type = type(STRING); 
            new(&s) std::string(value); 
        }

        jsonValue(jsonValue* value){
            Type = type(JSON);
            json = value;
        }
        jsonValue(const jsonValue& other){
            Type = other.Type;
            switch(Type) {
                case INT:    n = other.n; break;
                case DOUBLE: d = other.d; break;
                case STRING: new(&s) std::string(other.s); break;
                case JSON:   json = other.json; break;
            }
        }
        jsonValue& operator=(const jsonValue& other) {
        if (this != &other) {
            this->~jsonValue();

            Type = other.Type;
            switch (Type) {
                case INT:    n = other.n; break;
                case DOUBLE: d = other.d; break;
                case STRING: new (&s) std::string(other.s); break;
                case JSON:   json = new jsonValue(*other.json); break;
            }
        }
        return *this;
    }
        ~jsonValue() {
        if (Type == STRING) {
            s.~basic_string();
        }
    }
    };

    int position;
    string data;
    void skipSpace();
    jsonValue parseINT();
    jsonValue parseOBJECT();
    jsonValue parseSTRING();
    char peek();
    char next();

public:
    jsonParser(string data);
    jsonValue parse();
    ~jsonParser();
};

jsonParser::jsonParser(string data)
{
    jsonParser::position = 0;
    jsonParser::data = data;

}
jsonParser::jsonValue jsonParser::parseINT(){
    string numStr;
        char c = peek();
        while (isNumberChar(c)) {
            numStr += next();
            c = peek();
        }

        if (numStr.find('.') != string::npos || 
            numStr.find('e') != string::npos) {
            double val= stod(numStr);
            return jsonValue(val);
        } else {
            int val = stoi(numStr);
            return jsonValue(val);
        }
}
jsonParser::jsonValue jsonParser::parseOBJECT(){
    
}
char jsonParser::peek()
{
    return data[position];
}

void jsonParser::skipSpace()
{
    while (isspace(jsonParser::data[position]))
    {
        position++;
    }
}

char jsonParser::next(){
    position++;
    return data[position];
}
bool isNumberChar(char c) {
        return isdigit(c) || c == '-' || c == '+' || c == '.';
}
jsonParser::jsonValue jsonParser::parse(){
        skipSpace();
        char c = peek();

        switch (c) {
            case '{': 
                next();
                return parseOBJECT(); 

            case '\"': 
                next();
                return parseSTRING();

            default:
                if (isNumberChar(c)) {
                    return parseINT(); 
                } else {
                    cerr << "Unexpected character: " << c << endl;
                    return jsonValue(); 
                }
        }
}
    

jsonParser::~jsonParser()
{
}

