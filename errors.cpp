//Name: Ian Collins
//KUID: 3051520
//Date: 11/24/23
//Course: EECS 348
//Purpose: Handle the errors that can occur within the caluclator

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cout;

//Check if a given char is a num
bool is_num(char num) {
    if ((num >= '0') && (num <= '9')) {
        return true;
    } else {
        return false;
    }
}

//Check if a given char is an operator
bool is_operator(char sym) {
    if ((sym == '%') || (sym == '*') || (sym == '+') || (sym == '-') || (sym == '^') || (sym == '/')) {
        return true;
    } else {
        return false;
    }
}

//Checks if the char is an operator that does not function a sign
bool is_not_sign(char sym) {
    if ((sym == '%') || (sym == '*') || (sym == '^') || (sym == '/')) {
        return true;
    } else {
        return false;
    }
}

//Checks if there are any invalid chars in the string
int invalid_char(string expr) {
    for (int i = 0; i < expr.length(); i++) {
        //Checks range using ascii values
        if (!(is_num(expr[i]) || is_operator(expr[i]))) {
            return 1;
        }
    }
    return 0;
}

//Checks if there are any repeated operators
int repeated_operator(string expr) {
    //Looks for repeated operator
    for (int i=0; i < expr.length()-1; i++) {
        if ((is_operator(expr[i]) && is_operator(expr[i+1]))) {
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
    if (is_not_sign(expr[0]) || is_operator(expr[n])) {
        return 1;
    } else {
        return 0;
    }
}

//Checks if ther are any missing operators 
int missing_operator(string expr) {
    for (int i; i < expr.length()-1; i++) {
        if ((is_num(expr[i]) && (expr[i+1] == '(')) || ((expr[i] == ')')&&is_num(expr[i+1]))) {
            return 1;
        }
    }
    return 0;
}


//Finds any parantheses errors like mismatch or 
int mismatch_parantheses(string expr) {
    int front = 0;
    int back = 0;
 
    //iterate str
    for (int i; i < expr.length(); i++) {
        if (expr[i] == '(') {
            front++;
        } else if (expr[i] == ')') {
            back++;
        }
        //Detects open front parantheses
        if (front < back) {
            return 1;
        }
    }

    //Detects open back parantheses
    if (front != back) {
        return 1;
    } else {
        return 0;
    }
}

//Determines if the expression is dividing by zero
int divide_by_zero(string expr) {
    int front = 0;
    int back = 0;
    int n;

    for (int i=0; i < expr.length()-1; i++) {
        if ((expr[i] == '/' || expr[i] == '%') && (expr[i+1] == '(')) {
            front++;
            //Finds denominator
            for (n = i; n < expr.length(); n++) {
                if (expr[n] == ')') {
                    back++;
                    //Checks if demoniator expression is finished
                    if (front >= back) {
                        string sub_expr = expr.substr(i, n-i);
                        //Order of operations with sub_expr passed in
                        //if (!(orderOfOperation(sub_expr))) {
                        //    return 1;
                        //}
                    }
                }
            }
            //Perform Order of Operations on denominator term
            
        } else if ((expr[i] == '/' || expr[i] == '%') && expr[i+1] == '0') {
             return 1;
        }
    }

    return 0;
}

vector<string> check_errors(string expr) {
    vector<string> error;

    if (invalid_char(expr)) {
        string inv_char = "Syntax Error: Invalid operator character error";
        error.push_back(inv_char);
    }

    if (repeated_operator(expr)) {
        string repeat_op = "Syntax Error: Repeated operator error";
        error.push_back(repeat_op);
    }

    if (hanging_operators(expr)) {
        string hang_op = "Syntax Error: Hanging operator error";
        error.push_back(hang_op);
    }

    if (missing_operator(expr)) {
        string miss_op = "Syntax Error: Missing operator error";
        error.push_back(miss_op);
    }

    if (mismatch_parantheses(expr)) {
        string mis_para = "Syntax Error: Mismatch parantheses error";
        error.push_back(mis_para);
    }

    if (divide_by_zero(expr)) {
        string zero = "Arithemtic Error: Divide by zero error";
    }

    return error;
}

void print_errors(vector<string> error) {
    vector<string>::iterator line = error.begin();

    cout << "Possible errors in the expression:\n";
    if (error.size() > 0) {
        for (line; line < error.end(); line++) {
            cout << *line << "\n";
        }
    } else {
        cout << "No errors found\n";
    }
}

int main() {
    string expr = "((5+3)*8)";
    vector<string> error = check_errors(expr);

    print_errors(error);
    
    return 0;
}