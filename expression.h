//
// Created by Isla Lowe on 7/29/24.
//

#ifndef INFIX_TO_POSTFIX_PROJECT_EXPRESSION_H
#define INFIX_TO_POSTFIX_PROJECT_EXPRESSION_H

#include <string>
using std::string;

class Expression {
private:
    string _infix;
    string _postfix;
public:
    Expression();
    Expression(const string& infix);
    void ConvertToPostfix();
    string GetInfix()const;
    string GetPostfix()const;
    string ToJSON()const;
    double Evaluate(bool& error)const;
    bool Precedence (char operator1, char operator2) const;
    string Next(string& infixString, int& pos) const;
};
string trim(const string& str, const string& whitespace = " \t");


#endif //INFIX_TO_POSTFIX_PROJECT_EXPRESSION_H
