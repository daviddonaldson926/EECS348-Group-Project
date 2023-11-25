//Name: Ian Collins
//KUID: 3051520
//Date: 11/24/23
//Course: EECS 348
//Purpose: Handle the errors that can occur within the caluclator

#include <string.h>
using std::string;

int invalid_char(string expression):
    for (int i = 0, i < expression.length(), i++):
        if !('0' <= expression[i] <= '9' || expression[i] == ('+'||'-'||'*'||'/'||'('||')'||'^'||'%')):
            return 1;
            
    return 0;