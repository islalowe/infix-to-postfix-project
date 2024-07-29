# Infix to Postfix Project
## Overview
The expression class converts a given expression from infix to postfix notation. 

## Features
- Constructors: Initialize the class infix and postfix data members.
- Conversion: Converts the infix expression stored in the data member _infix and place the converted postfix expression in the data member _postfix.
- Formatting: Returns the postfix expression as s string or in JSON notation.
- Evaluation: 

## Class Utility Methods
- bool Expression::Precedence(char operator1, char operator2) const: This method determines the precedence between two operators. If the first operator is of higher or equal precedence than the second operator, true is returned. False is returned otherwise.
- string Expression::Next(string& infixString, int& pos) const: This method takes in a string and returns the next operator, operand or parenthesis.

## Unit Tests

