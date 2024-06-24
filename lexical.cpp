#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
using namespace std;

string lexem = "";
vector<string> lexemArray;
string rightPortionOfLine = "";
string leftPortionOFLine = "";
char codeCharacter;
bool equalFound = false;
bool endSignal = false;
bool spaceFound = false;
void cleanVariables()
{
    rightPortionOfLine = "";
    leftPortionOFLine = "";
    codeCharacter;
    equalFound = false;
    endSignal = false;
    spaceFound = false;
}
bool is_number(const string &s)
{
    for (char c : s)
    {
        if (!isdigit(c))
            return false;
    }
    return !s.empty();
}

void lexemPrinter()
{
    for (const string &lexem : lexemArray)
    {
        std::cout << lexem << endl;
    }
}

string initializationHandler(string expression)
{
    spaceFound = false;
    bool startsWithNumber = false;
    lexem = "";

    for (size_t charPos = 0; charPos < expression.length(); charPos++)
    {
        codeCharacter = expression[charPos];
        if (codeCharacter == ' ' && !spaceFound)
        {
            spaceFound = true;
            lexemArray.push_back(lexem);
            lexem = "";
            continue;
        }

        if (spaceFound && isdigit(codeCharacter) && lexem.length() == 0) //if space found and a digit also first char of lexem is a digit
        {
            startsWithNumber = true;
        }

        lexem += codeCharacter;
    }

    if (startsWithNumber)
    {
        lexemArray.push_back(lexem + " < -lexical error in this line, starts with number");
    }
    else
    {
        lexemArray.push_back(lexem);
    }

    return "null";
}

void rightSideExpressionHandler(string expression)
{
    lexem = "";
    string cleanExpression = "";

    for (char c : expression)
    {
        if (c != ' ')
        {
            cleanExpression += c;
        }
    }

    for (size_t charPos = 0; charPos < cleanExpression.length(); charPos++)
    {
        codeCharacter = cleanExpression[charPos];

        if (codeCharacter == '+' || codeCharacter == '-' || codeCharacter == '*' || codeCharacter == '/')
        {
            lexemArray.push_back(lexem);
            lexem = codeCharacter;
            lexemArray.push_back(lexem);
            lexem = "";
            continue;
        }

        lexem += codeCharacter;
    }

    if (!lexem.empty())
    {
        lexemArray.push_back(lexem);
    }
}

int main()
{
    string userCode;
    ifstream MyReadFile("text.mylang");
    while (getline(MyReadFile, userCode))
    {
        cleanVariables();
        for (size_t charPos = 0; charPos < userCode.length(); charPos++)
        {
            codeCharacter = userCode[charPos];
            if (codeCharacter == ';')
            {
                rightSideExpressionHandler(rightPortionOfLine);
                lexemArray.push_back(";");
                endSignal = true;
                break;
            }
            if (codeCharacter == '=')
            {
                equalFound = true;
                initializationHandler(leftPortionOFLine);
                lexemArray.push_back("=");
                continue;
            }
            if (!equalFound)
            {
                leftPortionOFLine += codeCharacter;
                continue;
            }
            rightPortionOfLine += codeCharacter;
        }
    }

    std::cout << "All lexems: " << endl;
    lexemPrinter();
    std::cout << "Right portion of line: " << rightPortionOfLine << endl;
    std::cout << "Left portion of line: " << leftPortionOFLine << endl;

    return 0;
}
