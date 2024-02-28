#include "fancy_calculator.h"
#include "stack.h"
#include "queue.h"

namespace lab5
{
    bool is_number(std::string input_string);
    bool is_operator(std::string input_string);
    int get_number(std::string input_string);
    std::string get_operator(std::string input_string);
    int operator_priority(std::string operator_in);

    void calculator::parse_to_infix(std::string &input_expression) 
    {
        int count_paren_open = 0;
        lab1::expressionstream  *stream=new lab1::expressionstream(input_expression);
        if (stream->next_token_is_op())
            throw std::exception();
        else 
        {
            do 
            {
                if (stream->next_token_is_int() || stream->next_token_is_op())
                    infix_expression.enqueue(stream->get_next_token());
                else if(stream->next_token_is_paren_open()){
                    infix_expression.enqueue(stream->get_next_token());
                    count_paren_open++;
                }
                else if(stream->next_token_is_paren_close())
                {
                    if (count_paren_open == 0)
                    {
                        throw std::exception();
                    }
                    else
                    {
                        infix_expression.enqueue(stream->get_next_token());
                        count_paren_open--;
                    }
                }
                else break;
            } 
            while (true);
        }
    }

    void calculator::convert_to_postfix(lab5::queue infix_expression) 
    {
        lab5::stack Temp_Stack;
        std::string temporary;
        while(!infix_expression.isEmpty()) 
        {
            temporary = infix_expression.top();
            infix_expression.dequeue();
            if (is_number(temporary))
            {
                postfix_expression.enqueue(temporary);
            }
            if(is_operator(temporary)) 
            {
                while (!Temp_Stack.isEmpty() && operator_priority(Temp_Stack.top()) >= operator_priority(temporary) && Temp_Stack.top() != "(")
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
        while(!Temp_Stack.isEmpty()) 
        {
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
        std::istreambuf_iterator<char> OpTemp;
        std::string ex(std::istreambuf_iterator<char>(stream), OpTemp);
        while (!RHS.infix_expression.isEmpty())
        {
            RHS.infix_expression.dequeue();
        }
        while (!RHS.postfix_expression.isEmpty())
        {
            RHS.postfix_expression.dequeue();
        }
        RHS.parse_to_infix(ex);
        RHS.convert_to_postfix(RHS.infix_expression);
        return stream;
    }

    int calculator::calculate() 
    {
        int answer=0;
        std::string temp1, temp2;
        lab5::stack *Temp_Stack = new stack;
        while (!postfix_expression.isEmpty()) 
        {
            if (is_number(postfix_expression.top()))
             {
                Temp_Stack->push(postfix_expression.top());
                postfix_expression.dequeue();
            } 
            else 
            {
                temp2 = Temp_Stack->top();
                Temp_Stack->pop();
                temp1 = Temp_Stack->top();
                Temp_Stack->pop();
                if (postfix_expression.top() == "+")
                    answer = get_number(temp1) + get_number(temp2);
                else if (postfix_expression.top() == "-")
                    answer = get_number(temp1) - get_number(temp2);
                else if (postfix_expression.top() == "*")
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
        stream << std::string ("Infix: ");
        stream << RHS.infix_expression.top();
        RHS.infix_expression.dequeue();
        while (!RHS.infix_expression.queueSize() == 0)
        {
            stream << std::string (",");
            stream << RHS.infix_expression.top();
            RHS.infix_expression.dequeue();
        }
        stream << std::string ("\nPostfix: ");
        stream << RHS.postfix_expression.top();
        RHS.postfix_expression.dequeue();
        while (!RHS.postfix_expression.queueSize() == 0)
        {
            stream << std::string (",");
            stream << RHS.postfix_expression.top();
            RHS.postfix_expression.dequeue();
        }
        return stream;
    }


    // AUXILIARY FUNCTIONS
    bool is_number(std::string input_string)
    {
        if (input_string == "+" || input_string == "-" || input_string == "*" || input_string == "/" || input_string == "(" || input_string == ")")
            return false;
        else
            return true;
    }

    bool is_operator(std::string input_string)
    {
        if (input_string == "+" || input_string == "-" || input_string == "*" || input_string == "/")
            return true;
        else
            return false;
    }

    int get_number(std::string input_string)
    {
        if(is_number(input_string))
            return stoi(input_string);
    }

    std::string get_operator(std::string input_string);

    int operator_priority(std::string operator_in)
    {
        if (operator_in == "(" || operator_in == ")")
            return 3;
        else if (operator_in == "/" || operator_in == "*")
            return 2;
        else if (operator_in == "+" || operator_in == "-")
            return 1;
        else
            return 0;
    }

}