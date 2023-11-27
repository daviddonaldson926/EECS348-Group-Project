//Name: Ian Collins
//KUID: 3051520
//Date: 11/24/23
//Course: EECS 348
//Purpose: Handle the errors that can occur within the caluclator

#include <string>

//Check if a given char is a num
bool is_num(char num) {
    if ((num >= '0')&&(num <= '9')) {
        return true;
    } else {
        return false;
    }
}

//Check if a given char is an operator
bool is_operator(char sym) {
    if ((sym == '%')||(sym == '*')||(sym == '+')||(sym == '-')||(sym == '^')||(sym == '/')) {
        return true;
    } else {
        return false;
    }
}

//Checks if the char is an operator that does not function a sign
bool is_not_sign(char sym) {
    if ((sym == '%')||(sym == '*')||(sym == '^')||(sym == '/')) {
        return true;
    } else {
        return false;
    }
}

//Checks if there are any invalid chars in the string
int invalid_char(string expr) {
    for (int i = 0; i < expr.length(); i++) {
        //Checks range using ascii values
        if (!(is_num(expr[i])||is_operator(expr[i]))) {
            return 1;
        }
    }
    return 0;
}

//Checks if there are any repeated operators
int repeated_operator(string expr) {
    //Looks for repeated operator
    for (int i=0; i < expr.length()-1; i++) {
        if ((is_operator(expr[i]) && is_operator(expr[i+1]))&&((expr[i] != '+')||(expr[i] != '-'))) {
            return 1;
        }
    }
    return 0;
}

//Checks if there are operators with missing operands
int hanging_operators(string expr) {
    //Find last index of given string
    int n = expr.length()-1;

    //Looks if first or last char in the string is an operator
    if (is_not_sign(expr[0])||is_operator(expr[n])) {
        return 1;
    } else {
        return 0;
    }
}

//Checks if ther are any missing operators 
int missing_operator(string expr) {
    for (int i; i < expr.length()-1; i++) {
        if ((is_num(expr[i])&&(expr[i+1] == '(')) || ((expr[i] == ')')&&is_num(expr[i+1]))) {
            return 1;
        }
    }
    return 0;
}