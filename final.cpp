#include <iostream>
#include <string>
#include <vector>

#include <stack> // Used for implementing stack data structures
#include <cmath> // Includes mathematical functions like pow() and fmod()
#include <map> // Used to map operators to their precedence values

using std::string;
using std::vector;
using std::stack;
using std::map;
using std::cout;
using std::endl;

/*
THIS PART DOES ERRORS!!!!!
*/

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
        if (!(is_num(expr[i]) || is_operator(expr[i]) || expr[i] == '(' || expr[i] == ')')) {
            return 1;
        }
    }
    return 0;
}

//Checks if there are any repeated operators
int repeated_operator(string expr) {
    //Looks for repeated operator
    for (int i=0; i < expr.length()-1; i++) {
        if ((is_operator(expr[i]) && is_operator(expr[i+1])) && ((expr[i] != '+') || (expr[i] != '-'))) {
            return 1;
        }
    }
    return 0;
}

//Checks if there are any operators in the wrong sequence 
int invalid_op_sequence(string expr) {
    for (int i=0; i < expr.length()-1; i++) {
        if ((is_operator(expr[i]) && expr[i+1] == ')') || (is_not_sign(expr[i]) && expr[i-1] == '(')) {
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
    for (int i = 0; i < expr.length()-1; i++) {
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
    for (int i = 0; i < expr.length(); i++) {
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
                        if (evaluate(sub_expr) == 0) {
                            return 1;
                        }
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

    if (invalid_op_sequence(expr)) {
        string inv_seq = "Syntax Error: Invalid operator sequence"; 
        error.push_back(inv_seq); 
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

int print_errors(vector<string> error) {
    vector<string>::iterator line = error.begin();

    cout << "Possible errors in the expression:\n";
    if (error.size() > 0) {
        for (line; line < error.end(); line++) {
            cout << *line << "\n";
            return 1; 
        }
    } else {
        cout << "No errors found\n";
        return 0; 
    }
    return 0; 
}

/*
THIS PART DOES ORDER OF OPERATIONS!!!!!
*/

// Function to evaluate a basic operation between two operands
double applyOp(double a, double b, char op){
    switch(op){
        case '+': return a + b; // Handles addition
        case '-': return a - b; // Handles subtraction
        case '*': return a * b; // Handles multiplication
        case '/': return a / b; // Handles division
        case '^': return pow(a, b); // Handles exponentiation
        case '%': return fmod(a, b); // Handles modulo operation
    }
    return 0; // Default return in case of an unknown operator
}

// Function to evaluate a given arithmetic expression
double evaluate(const std::string &expression){
    stack<double> values; // Stack to store values (numbers)
    stack<char> ops; // Stack to store operators
    // Map to store precedence of operators
    map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}, {'%', 2}};

    // Iterating over each character of the expression
    for(int i = 0; i < expression.length(); i++){
        // Skipping spaces in the expression
        if(expression[i] == ' '){
            continue; // Continues to the next character in the expression
        }
        else if(expression[i] == '('){
            ops.push(expression[i]); // If character is '(' push it to ops stack
        }
        // If character is a digit, parse the number and push to values stack
        else if(isdigit(expression[i])){
            double value = 0;
            // Parsing numbers/decimals
            while(i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')){
                value = (value * 10) + (expression[i] - '0');
                if(expression[i] == '.') i++; // Increases by one if there is a decimal
                i++; // Increase by one
            }
            values.push(value);
            i--; // Decreases by one 
        }
        // Handling operators and closing parenthesis
        else if(expression[i] == ')' || expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^' || expression[i] == '%'){
            // Handling closing parenthesis or operator precedence
            if(expression[i] == ')' || (!ops.empty() && precedence[ops.top()] >= precedence[expression[i]])){
                // Process the operators in the ops stack
                while(!ops.empty() && ops.top() != '('){
                    double val2 = values.top(); values.pop(); // Will assign the value to val2
                    double val1 = values.top(); values.pop(); // Will assign the value to val1 
                    char op = ops.top(); ops.pop(); // Will assign the operator to op 
                    values.push(applyOp(val1, val2, op)); // Will evalute the two values and operator and push that value to the value stack
                }
                // Pop the opening parenthesis
                if(expression[i] != ')') ops.push(expression[i]);
                else ops.pop();
            }
            // Handling unary operators
            else if(expression[i] == '-' || expression[i] == '+'){ // If the expression is postive or negative it performs this 
                if(i == 0 || expression[i-1] == '('){ // Checks if the operator is unary
                    values.push(0); // Assume zero before unary operator
                }
                ops.push(expression[i]); // Push the operator to the ops stack
            }
            else{
                ops.push(expression[i]); // Push other operators onto the ops stack
            }
        }
    }

    // Processing remaining operators in the ops stack
    while(!ops.empty()){ // Will continue until there is no operators in the op stack
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op)); // Push the number to the value stack
    }

    // The top of the values stack contains the result
    return values.top();
}

int main(){
    string expression; // Recognizes expression as a string
    cout << "Enter the expression: "; // Prompts the user for an expression
    std::getline(std::cin, expression); // Reading the entire line as an expression

    vector<string> error = check_errors(expression); 
    int check = print_errors(error); 

    if (check == 0) {
        double result = evaluate(expression); // Evaluating the expression
        cout << "Result: " << result << endl; // Displaying the result
    }

    return 0; // End of main function
}
