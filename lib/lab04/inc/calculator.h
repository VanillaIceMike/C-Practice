#ifndef CMPE126S18_LABS_CALCULATOR_H
#define CMPE126S18_LABS_CALCULATOR_H

#include "lifo.h"
#include "fifo.h"
#include "expressionstream.h"

namespace lab4{
    class calculator{
        lab3::fifo infix_expression;
        lab3::fifo postfix_expression;

        void parse_to_infix(std::string &input_expression); //PRIVATE function used for converting input string into infix notation
        void convert_to_postfix(lab3::fifo infix_expression); //PRIVATE function used for converting infix FIFO to postfix
    public:
        calculator();   //Default constructor
        calculator(std::string &input_expression); // Constructor that converts input_expression to infix and postfix upon creation
        friend std::istream& operator>>(std::istream& stream, calculator& RHS); //Store the infix and postfix expression in calculator

        int calculate(); //Return the calculation of the postfix expression
        friend std::ostream& operator<<(std::ostream& stream, calculator& RHS); //Stream out overload. Should return in the format "Infix: #,#,#,#\nPostfix: #,#,#,#"
        int operator_priority(std::string operator_in);
        bool is_operator(std::string input_string);
        bool is_number(std::string input_string);
        int calc_binary_operation(int lhs, int rhs, std::string op);
        int get_number(std::string input_string);
        void clear_expressions();
    };
}

#endif //CMPE126S18_LABS_CALCULATOR_H
