#include <string>
#include <vector>
#include "calculator.h"
#include "expressionstream.h"
#include "lifo.h"
#include <iostream>
#include <stack>


namespace lab4 
{
    void calculator::parse_to_infix(std::string &input_expression) 
    {
        // input_expression = "1 + 2 + 3"
        std::string numberOrExpression = "";
        for (int i=0; i<input_expression.length(); i++) 
        {
            char letter = input_expression[i];
            if (letter >= '0' && letter <= '9') 
            {
                numberOrExpression += letter;
            }
            else if(letter == ' ') {
                infix_expression.enqueue(numberOrExpression);
                numberOrExpression = "";
            }
            else {
                numberOrExpression = letter;
            }
        }
        infix_expression.enqueue(numberOrExpression);
        // infix_expression = (f) [1, +, 2, +, 3] (b)
    }
    void calculator::convert_to_postfix(lab3::fifo infix_expression) 
    {
        lab3::lifo Temp_Stack;
        std::string temporary;
        while(!infix_expression.is_empty()) 
        {
            temporary = infix_expression.front();
            infix_expression.dequeue();

            if (is_number(temporary))
            {
                postfix_expression.enqueue(temporary);
            }

            if(is_operator(temporary)) 
            {
                while (!Temp_Stack.is_empty() && operator_priority(Temp_Stack.top()) >= operator_priority(temporary) && Temp_Stack.top() != "(")
                {
                    postfix_expression.enqueue(Temp_Stack.top());
                    Temp_Stack.pop();
                }
                Temp_Stack.push(temporary);
            }
            if (temporary == "(") 
            {
                Temp_Stack.push(temporary);
            }
            if (temporary == ")") 
            {
                while (Temp_Stack.top() != "(")
                {
                    postfix_expression.enqueue(Temp_Stack.top());
                    Temp_Stack.pop();
                }
                Temp_Stack.pop();
            }
        }
        while(!Temp_Stack.is_empty()) {
            postfix_expression.enqueue(Temp_Stack.top());
            Temp_Stack.pop();
        }

    }

    calculator::calculator() 
    {
        std::string empty_input;
        parse_to_infix(empty_input);
        convert_to_postfix(infix_expression);
    }

    calculator::calculator(std::string &input_expression) 
    {
        parse_to_infix(input_expression);
        convert_to_postfix(infix_expression);
    }

    std::istream &operator>>(std::istream &stream, calculator &RHS) 
    {
        std::string expression;
        getline(stream, expression);
        RHS.parse_to_infix(expression);
        RHS.convert_to_postfix(RHS.infix_expression);
        return stream;
    }
    //infix_expression: 1+2+3
    //postfix_expression: (f) + (b)
    //operand_stack: (t) 3 3 (b)

        int lab4::calculator::calculate() {
        int answer=0;
        std::string temp1, temp2;
        lab3::lifo *Temp_Stack = new lab3::lifo;
        while (!postfix_expression.is_empty()) {
            if (is_number(postfix_expression.front())) 
            {
                Temp_Stack->push(postfix_expression.front());
                postfix_expression.dequeue();
            } else {
                temp2 = Temp_Stack->top();
                Temp_Stack->pop();
                temp1 = Temp_Stack->top();
                Temp_Stack->pop();
                if (postfix_expression.front() == "+")
                    answer = get_number(temp1) + get_number(temp2);
                else if (postfix_expression.front() == "-")
                    answer = get_number(temp1) - get_number(temp2);
                else if (postfix_expression.front() == "*")
                    answer = get_number(temp1) * get_number(temp2);
                else
                    answer = get_number(temp1) / get_number(temp2);
                postfix_expression.dequeue();
                Temp_Stack->push(std::to_string(answer));
            }
        }
        return answer = get_number(Temp_Stack->top());
    }

     std::ostream &operator<<(std::ostream &stream, calculator &RHS) 
     {
        int infixSize = RHS.infix_expression.size();
        int postfixSize = RHS.postfix_expression.size();
        stream << "Infix: ";

        for (int i=0; i<infixSize; i++) 
        {
            if (i == infixSize-1) 
            {
                stream << RHS.infix_expression.front() << std::endl;
            }
            else
                stream << RHS.infix_expression.front() << ",";
            RHS.infix_expression.dequeue();
        }

        stream << "Postfix: ";

        for (int i=0; i<postfixSize; i++) 
        {
            if (i == postfixSize-1) 
            {
                stream << RHS.postfix_expression.front();
            }
            else
                stream << RHS.postfix_expression.front() << ",";
            RHS.postfix_expression.dequeue();
        }

        return stream;
    }


    // AUXILIARY FUNCTIONS
    bool calculator::is_number(std::string input_string)
    {
        std::string::iterator location = input_string.begin();
        if(*location >= '0' && *location <= '9') return true;
        if(*location != '-')return false;
        return(*++location >='0' && *location <= '9');
    }


    bool calculator::is_operator(std::string input_string){
        if(input_string == "+" ||input_string == "-" || input_string == "*" || input_string == "/" || input_string == "^")
        {
            return true;
        }
        else
        {
         return false;
        }
    }

    int calculator::get_number(std::string input_string)
    {
        return std::stoi( input_string );
    }

    std::string get_operator(std::string input_string);

    int calculator::operator_priority(std::string operator_in)
    {
        if(operator_in == "^")
            return 3;
        else if(operator_in == "/" || operator_in=="*")
            return 2;
        else if(operator_in == "+" || operator_in == "-")
            return 1;
        else
            return -1;

    }
    int calculator::calc_binary_operation(int lhs, int rhs, std::string op) {
        std::string::iterator op_iter = op.begin();
        switch (*op_iter){
            case '^': return lhs ^ rhs;
            case '*': return lhs * rhs;
            case '/': return lhs / rhs;
            case '+': return lhs + rhs;
            case '-': return lhs - rhs;
            default: throw "unknown operator";
        }
    }
    void calculator::clear_expressions() {
        while(!infix_expression.is_empty()) infix_expression.dequeue();
        while(!postfix_expression.is_empty()) postfix_expression.dequeue();
    }
}