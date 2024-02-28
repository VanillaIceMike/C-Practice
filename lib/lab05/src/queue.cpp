#include "queue.h"
namespace lab5
{
    queue::queue() 
    {

    }

    queue::queue(std::string &data) 
    {
        enqueue(data);
    }

    queue::queue(const queue &original) 
    {
        storage_structure = original.storage_structure;
    }

    queue::~queue() 
    {

    }

    queue &queue::operator=(const queue &RHS) 
    {
        //return <#initializer#>;
        if(this == &RHS)
            return *this;
        else
            for (int i = 0; i < RHS.queueSize() ; i++)
                this->enqueue(RHS.storage_structure.get_value_at(i)) ;
        return *this;

    }

    bool queue::isEmpty() const 
    {
        if(queueSize() == 0)
            return true;
        else
            return false;
    }

    unsigned queue::queueSize() const 
    {
        return storage_structure.listSize();
    }

    std::string queue::top() const 
    {
        //return std::__cxx11::string();
        return storage_structure.get_value_at(0);
    }

    void queue::enqueue(const std::string &data) 
    {
        storage_structure.append(data);

    }

    void queue::dequeue() 
    {
        storage_structure.remove(0);
    }

    std::ostream& operator<<(std::ostream &stream, queue &RHS) 
    {
        for (int i = 0; i < RHS.queueSize() ; i++)
        {
            stream << RHS.storage_structure.get_value_at(i);
        }
        return stream;
    }

    std::istream& operator>>(std::istream &stream, queue &RHS) 
    {
        std::string temp;
        stream >> temp;
        RHS.enqueue(temp);
        return stream;
    }
}