#include "jsonParser.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>

// jsonValue member implementations
jsonParser::jsonValue::jsonValue() : type(INT), intValue(0) {}

jsonParser::jsonValue::jsonValue(int val) : type(INT), intValue(val) {}

jsonParser::jsonValue::jsonValue(double val) : type(DOUBLE), doubleValue(val) {}

jsonParser::jsonValue::jsonValue(const std::string& val) : type(STRING) {
    stringValue = new std::string(val);
}

jsonParser::jsonValue::jsonValue(std::map<std::string, jsonValue>* val) : type(JSON_OBJECT) {
    objectValue = val;
}

jsonParser::jsonValue::jsonValue(const jsonValue& other) : type(other.type) {
    switch(type) {
        case INT: intValue = other.intValue; break;
        case DOUBLE: doubleValue = other.doubleValue; break;
        case STRING: stringValue = new std::string(*other.stringValue); break;
        case JSON_OBJECT: objectValue = new std::map<std::string, jsonValue>(*other.objectValue); break;
    }
}

jsonParser::jsonValue& jsonParser::jsonValue::operator=(const jsonValue& other) {
    if (this != &other) {
        this->~jsonValue();
        type = other.type;
        switch(type) {
            case INT: intValue = other.intValue; break;
            case DOUBLE: doubleValue = other.doubleValue; break;
            case STRING: stringValue = new std::string(*other.stringValue); break;
            case JSON_OBJECT: objectValue = new std::map<std::string, jsonValue>(*other.objectValue); break;
        }
    }
    return *this;
}

jsonParser::jsonValue::~jsonValue() {
    if (type == STRING) {
        delete stringValue;
    } else if (type == JSON_OBJECT) {
        delete objectValue;
    }
}

// jsonParser member implementations
jsonParser::jsonParser(const std::string& jsonData) : position(0), data(jsonData) {}

jsonParser::~jsonParser() = default;

void jsonParser::skipSpace() {
    while (position < data.size() && isspace(data[position])) {
        position++;
    }
}

char jsonParser::peek() const {
    if (position >= data.size()) throw std::runtime_error("Unexpected end of input");
    return data[position];
}

char jsonParser::next() {
    if (position >= data.size()) throw std::runtime_error("Unexpected end of input");
    return data[position++];
}

bool jsonParser::isNumberChar(char c) const {
    return isdigit(c) || c == '-' || c == '+' || c == '.';
}

jsonParser::jsonValue jsonParser::parseString() {
    std::string str;
    while (true) {
        char c = next();
        if (c == '"') break;
        str += c;
    }
    return jsonValue(str);
}

jsonParser::jsonValue jsonParser::parseNumber() {
    std::string numStr;
    char c = peek();
    while (isNumberChar(c)) {
        numStr += next();
        c = peek();
    }

    if (numStr.find('.') != std::string::npos || numStr.find('e') != std::string::npos) {
        return jsonValue(std::stod(numStr));
    } else {
        return jsonValue(std::stoi(numStr));
    }
}

jsonParser::jsonValue jsonParser::parseObject() {
    auto* obj = new std::map<std::string, jsonValue>();
    skipSpace();

    if (next() != '{') {
        delete obj;
        throw std::runtime_error("Expected '{' at start of object");
    }
    skipSpace();

    while (peek() != '}') {
        if (peek() != '"') {
            delete obj;
            throw std::runtime_error("Expected string key");
        }
        next(); // Skip opening quote
        
        jsonValue keyValue = parseString();
        if (keyValue.type != STRING || !keyValue.stringValue) {
            delete obj;
            throw std::runtime_error("Invalid string key");
        }
        std::string key = *keyValue.stringValue;
        
        skipSpace();
        if (next() != ':') {
            delete obj;
            throw std::runtime_error("Expected ':' after key");
        }
        skipSpace();
        
        jsonValue value = parseValue();
        (*obj)[key] = value;
        
        skipSpace();
        if (peek() == ',') {
            next();
            skipSpace();
        }
    }
    next(); // Skip closing '}'
    return jsonValue(obj);
}

jsonParser::jsonValue jsonParser::parseValue() {
    skipSpace();
    char c = peek();
    
    if (c == '{') return parseObject();
    if (c == '"') {
        next(); // Skip opening quote
        return parseString();
    }
    if (isNumberChar(c)) return parseNumber();
    
    throw std::runtime_error("Unexpected character");
}

jsonParser::jsonValue jsonParser::parse() {
    try {
        return parseValue();
    } catch (const std::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return jsonValue(); // Return default value on error
    }
}
