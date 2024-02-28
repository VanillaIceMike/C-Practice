#include "fifo.h"
#include<iostream>
#include<stdexcept>

namespace lab3{
    fifo::fifo() 
    {
        fifo_storage = lab2::stringVector(100);
        back_index = 0;
        front_index = 0;
    }

    fifo::fifo(std::string input_string) 
    {
        fifo_storage = lab2::stringVector(100);
        fifo_storage.append(input_string);
        front_index = 0;
        back_index = 1;
    }

    fifo::fifo(const fifo &original) 
    {
        fifo_storage = original.fifo_storage;
        back_index = original.back_index;
        front_index = original.front_index;
    }

    fifo::~fifo() 
    {
        
    }

    fifo &fifo::operator=(const fifo &right) 
    {
        if (&fifo_storage == &right.fifo_storage)
        {
            return *this;
        }
        else
        {
            front_index = right.front_index;
            back_index = right.back_index;
            fifo_storage= right.fifo_storage;
            return *this;
        }
    }

    bool fifo::is_empty()
    {
        if (size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int fifo::size()
    {
        //return (is_empty() ? 0 : size); this is equal to if else statement
        int size = (back_index - front_index);
        return size;
        //return 0;
    }

    std::string fifo::front()
    {
        return fifo_storage[front_index];
    }

    std::string fifo::rear()
    {
        return fifo_storage[back_index-1];
    }

    void fifo::enqueue(std::string input) 
    {
        fifo_storage.append(input);
        back_index++;
    }

    void fifo::dequeue() 
    {
        front_index++;
    }
}