#ifndef CMPE126EXAM1_TUESDAY_LINKED_LIST_H
#define CMPE126EXAM1_TUESDAY_LINKED_LIST_H

#include "linked_list_m.h"

class stack{
    linked_list_m storage_structure;

public:
    stack();
    ~stack();

    void pop();
    void push(struct value_date input);
    const struct value_date top() const;
    bool empty();
    //stack& operator=(const stack& RHS);
};

#endif