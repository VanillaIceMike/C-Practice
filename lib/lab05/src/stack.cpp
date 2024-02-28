#include "stack.h"
namespace lab5{
    stack::stack() 
    {

    }

    stack::stack(std::string &data) 
    {
        push(data);
    }

    stack::stack(const stack &original) 
    {
        storage_structure = original.storage_structure;
    }

    stack::~stack() 
    {

    }

    stack &stack::operator=(const stack &RHS) 
    {
        //return <#initializer#>;
        if (this == &RHS)
            return *this;
        else
            for (int i = 0; i < RHS.stackSize() ; i++)
            {
                this->push(RHS.storage_structure.get_value_at(i));
            }
        return *this;
    }

    bool stack::isEmpty() const 
    {
        if(stackSize() == 0)
            return true;
        else
            return false;
    }

    unsigned stack::stackSize() const 
    {
        return storage_structure.listSize();
    }

    std::string stack::top() const 
    {
        //return std::__cxx11::string();
        return storage_structure.get_value_at(stackSize() - 1);
    }

    void stack::push(const std::string &data) 
    {
        storage_structure.append(data);
    }

    void stack::pop() 
    {
        storage_structure.remove(storage_structure.listSize() -1 );
    }

    std::ostream& operator<<(std::ostream &stream, stack &RHS) 
    {
        for (int i = 0; i < RHS.stackSize() ; i++)
        {
            stream << RHS.storage_structure.get_value_at(i);
        }
        return stream;
    }

    std::istream& operator>>(std::istream &stream, stack &RHS) 
    {
        std::string temp;
        stream >> temp;
        RHS.push(temp);
        return stream;
    }
}