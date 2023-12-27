#include "csvparser.h"

CSVParser::CSVParser(char separator)
    : m_separator(separator)
{
}

CSVParser::~CSVParser()
{
}

string CSVParser::getPart(string &input) const
{
    string tmp;
    int currentIndex{0};
    while (true) {
        char currentCharacter = input[currentIndex];
        if (currentCharacter == '\0' || currentCharacter == EOF) {
            --currentIndex;
            break;
        }
        if (currentCharacter == '\0' || currentCharacter == m_separator || currentCharacter == EOF) {
            break;
        }
        tmp += currentCharacter;
        ++currentIndex;
    }
    input = input.substr(currentIndex + 1);
    return tmp;
}
