#include "../inc/stack.h"

stack::stack() 
{
    //left empty
}

stack::~stack() 
{
    //left empty
}

void stack::pop() 
{
    return storage_structure.remove(storage_structure.listSize()-1);
}

void stack::push(struct value_date input) 
{
  return storage_structure.append(input);
}

bool stack::empty()
{
    return storage_structure.isEmpty();
}

const struct value_date stack::top() const
{
    return storage_structure.get_value_at(this->storage_structure.listSize()-1);
}