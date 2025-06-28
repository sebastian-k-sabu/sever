#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <map>
#include <string>
#include <stdexcept>

class jsonParser {
public:
    enum Type {
        INT,
        DOUBLE,
        STRING,
        JSON_OBJECT
    };

    struct jsonValue {
        Type type;
        union {
            int intValue;
            double doubleValue;
            std::string* stringValue;
            std::map<std::string, jsonValue>* objectValue;
        };

        // Constructors
        jsonValue();
        jsonValue(int val);
        jsonValue(double val);
        jsonValue(const std::string& val);
        jsonValue(std::map<std::string, jsonValue>* val);
        
        // Copy constructor and assignment
        jsonValue(const jsonValue& other);
        jsonValue& operator=(const jsonValue& other);
        
        // Destructor
        ~jsonValue();
    };

    explicit jsonParser(const std::string& jsonData);
    jsonValue parse();
    ~jsonParser();

private:
    size_t position;
    std::string data;

    void skipSpace();
    char peek() const;
    char next();
    bool isNumberChar(char c) const;
    jsonValue parseString();
    jsonValue parseNumber();
    jsonValue parseObject();
    jsonValue parseValue();
};

#endif