# Infix to Postfix Project
## Overview
The Expression class provides functionality to convert an infix expression to postfix notation and evaluate the postfix expression. It includes methods for formatting the postfix expression as a string or in JSON notation.

## Features
- Constructors: Initialize the class infix and postfix data members.
- Conversion: Converts the infix expression stored in the data member _infix and place the converted postfix expression in the data member _postfix.
- Formatting: Returns the postfix expression as s string or in JSON notation.
- Evaluation: Evaluates the postfix expression and returns the result.


## Class Utility Methods
- Precedence(char operator1, char operator2) const: Determines the precedence between two operators. Returns true if the first operator has higher or equal precedence than the second operator, otherwise returns false.
- Next(string& infixString, int& pos) const: Extracts and returns the next token (operator, operand, or parenthesis) from the given infix string starting at the specified position.
- Trim(const string& str, const string& whitespace): Trims leading and trailing whitespace from the given string.

## Unit Tests
- DoubleEquals(double a, double b, double epsilon = 1e-6): A helper function to test if two doubles are approximately equal.
- ProcessCommandLineParameters(int argc, char argv[])**: Processes command-line parameters and returns a CommandLineParameters structure.
- Help(const char argv)**: Displays usage information for the command-line interface.
