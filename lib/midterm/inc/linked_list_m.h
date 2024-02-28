#ifndef CMPE126S18_LABS_LIB_LAB05_INC_LINKED_LIST_H
#define CMPE126S18_LABS_LIB_LAB05_INC_LINKED_LIST_H

#include "stack_node.h"
#include <iostream>


    class linked_list_m {
        stack_node *head, *tail;

        stack_node* find_node(unsigned int location)const;
        bool is_valid_location(unsigned location)const;
    public:
        linked_list_m();

        //explicit linked_list_m(std::string &data);

        linked_list_m(const linked_list_m &original);

        virtual ~linked_list_m();

        linked_list_m &operator=(const linked_list_m &RHS);

        bool isEmpty() const;
        unsigned listSize() const;

        value_date get_value_at(unsigned location)const;
        //void insert(const value_date input, unsigned location = 0 );
        void insert(const value_date input, unsigned int location=0);
        //void append(struct stack_node *input);
        void append(value_date input);
        void remove(unsigned location = 0);

        //void sort();
    };


#endif