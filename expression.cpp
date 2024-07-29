//
// Created by Isla Lowe on 7/29/24.
//

#include "expression.h"
#include <iostream>
#include <sstream>
#include <stack>
using std::stack;
using std::stringstream;

/**
 * Default constructor
 */
Expression::Expression() {
}

/**
 * Constructor that initializes the class data members
 * @param infix is the value that the infix data member will be initialized with - and then converted
 */
Expression::Expression(const string& infix) {
    _infix = infix;
    _postfix = "";
}

/**
 * This will convert the infix expression stored in the data member _infix
 * and place the converted postfix expression in the data member _postfix.
 */
void Expression::ConvertToPostfix() {
    stack<char> myStack;
    _postfix.clear();
    string sym;
    char character = '\n';
    int pos = 0;
    int infixLength = _infix.length();

    while (pos < infixLength) {
        sym = Next(_infix, pos);

        if (sym.empty()) {
            break;
        }

        character = sym.at(0);
        // if sym is an operand (not an operator), append sym to postfix
        if (isalpha(character) || isdigit(character)) {
            // append the current operand to the postfix expression
            _postfix += sym;
            _postfix += " ";
        }
        else {
            // if sym is (, push sym into the stack
            if (character == '(') {
                myStack.push(character);
            }
                // if sym is ), pop and append all the symbols from the stack until
                // the most recent left parentheses
            else if (character == ')') {
                while (!myStack.empty() && myStack.top() != '(') {
                    _postfix += myStack.top();
                    _postfix += " ";
                    myStack.pop();
                }
                // pop and discard the left parentheses
                if (!myStack.empty()) {
                    myStack.pop();
                }
            }
            else {
                // if sym is an operator:
                // pop and append all the operators from the stack to postfix that
                // are above the most recent left parentheses and have precedence
                // greater than or equal to sym
                while (!myStack.empty() && myStack.top() != '(' && Precedence(myStack.top(), character)) {
                    _postfix += myStack.top();
                    _postfix += " ";
                    myStack.pop();
                }
                // push sym onto the stack
                myStack.push(character);
            }
        }
    }
    // pop and append to postfix everything from the stack
    while (!myStack.empty()) {
        if (myStack.top() != '(') {
            _postfix += myStack.top();
            _postfix += " ";
        }
        myStack.pop();
    }
    _postfix.pop_back();
}

/**
 * Returns a string holding the infix expression
 */
string Expression::GetInfix() const {
    return _infix;
}

/**
 * Returns a string holding the postfix expression
 */
string Expression::GetPostfix() const {
    return _postfix;
}

/**
 * This method creates and returns a JSON string from the information in
 * the string infix and postfix data members.
 */
string Expression::ToJSON() const {
    stringstream json;
    json << "{\"infix\":\"" << _infix << "\", \"postfix\":\"" << _postfix << "\"}";
    return json.str();
}

/**
 * This method returns the evaluated total of the expression.
 * If the operands are alphabetic then error is true and 0 is returned.
 */
double Expression::Evaluate(bool& error) const{
    stack<double>evalStack;

    //make sure these are numbers
    for (int i = 0; i < static_cast<int>(_postfix.length()); i++) {
        if (isalpha(_postfix.at(i))) {
            error = true;
            return 'e';
        }
    }

    //clear the stack for operating
    while (!evalStack.empty()) {
        evalStack.pop();
    }
    double total = 0.0;

    for (int j = 0; j < static_cast<int>(_postfix.length()); j++) {
        //_postfix.at(i) = std::stod(_postfix.at(i));
        //tempTotal needs to start at 0.0 for each operation
        double tempTotal = 0.0;
        //iterate through operands and push those into a stack
        if (isdigit(_postfix.at(j))) {
            evalStack.push(static_cast<double>(_postfix.at(j)));
        }
            //stop at an operator
        else if ((_postfix.at(j) == '+' ) || (_postfix.at(j) == '-') ||
                 (_postfix.at(j) == '*') || (_postfix.at(j) == '/')) {
            if (evalStack.size() > 1) {
                //store and pop the operands
                double operator2 = evalStack.top();
                evalStack.pop();
                double operator1 = evalStack.top();
                evalStack.pop();
                //tempTotal = operand1 (operator) operand2
                if (_postfix.at(j) == '+') {
                    tempTotal = operator1 + operator2;
                } else if (_postfix.at(j) == '-') {
                    tempTotal = operator1 - operator2;
                } else if (_postfix.at(j) == '/') {
                    tempTotal = operator1 / operator2;
                } else if (_postfix.at(j) == '*') {
                    tempTotal = operator1 * operator2;
                }
                total += tempTotal;
                //store tempTotal in the stack
                evalStack.push(tempTotal);
            }
        }
    }
    return total;
}

/**
 * This method determines the precedence between two operators.
 * , it will return false otherwise.
 * @param operator1 if the first operator is of higher or equal precedence than the
 * second operator, true is returned
 * @param operator2 if the second operator is of higher precedence than the
 * first operator, false is returned
 */
bool Expression::Precedence(char operator1, char operator2) const {
    //if operator2 is * or /, the method should return false if operator1 is either + or -.
    //in every other situation the method should return true.
    if ((operator2 == '*') || (operator2 == '/')) {
        if ((operator1 == '+') || (operator1 == '-')) {
            return false;
        }
    }
    return true;
}

/**
 * This method takes in a string and returns the next "thing"
 * (operator, operand or parenthesis) from the string sent as parameter.
 * @param infixString the string that will be read through and the next character returned
 */
string Expression::Next(string& infixString, int& pos) const {
    string sym = "";
    while (pos < static_cast<int>(infixString.length())) {
        if (infixString[pos] == '+' || infixString[pos] == '-' || infixString[pos] == '*' ||
            infixString[pos] == '/' || infixString[pos] == '(' || infixString[pos] == ')') {
            if (!sym.empty()) {
                break;              //don't move on
            }
            sym = infixString[pos++];
            break;
        }
        else if (infixString[pos] != ' ') {
            sym = infixString[pos++];
        }
        else {
            pos++;
        }
    }
    return sym;
}





/**
 * From: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
 */
string trim(const string& str, const string& whitespace){
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}



