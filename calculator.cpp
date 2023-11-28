#include <iostream> // For input and output operations
#include <stack> // Used for implementing stack data structures
#include <cmath> // Includes mathematical functions like pow() and fmod()
#include <map> // Used to map operators to their precedence values

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
    std::stack<double> values; // Stack to store values (numbers)
    std::stack<char> ops; // Stack to store operators
    // Map to store precedence of operators
    std::map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}, {'%', 2}};

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
    std::string expression; // Recognizes expression as a string
    std::cout << "Enter the expression: "; // Prompts the user for an expression
    std::getline(std::cin, expression); // Reading the entire line as an expression
    double result = evaluate(expression); // Evaluating the expression
    std::cout << "Result: " << result << std::endl; // Displaying the result

    return 0; // End of main function
}

