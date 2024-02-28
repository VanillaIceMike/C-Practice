#ifndef CMPE126S18_LABS_QUEUE_H
#define CMPE126S18_LABS_QUEUE_H
#include "stringVector.h"

namespace lab3 {
    class fifo {
        lab2::stringVector fifo_storage;
        int front_index;
        int back_index;

    public:
        fifo();                                          //Default constructor. Reserve 100 spaces in lifo_storage
        explicit fifo(std::string input_string);        //Create new fifo from string input
        fifo(const fifo &original);                     //Copy constructor
        virtual ~fifo();                                //Destructor
        fifo &operator=(const fifo &right);            //Assignment operator

        bool is_empty();  // Return true if the fifo is empty and false if it is not
        int size();  // Return the size of the fifo
        std::string front(); 
        std::string rear();           // Return the front string of the fifo.
        void enqueue(std::string input);   // Add input string to the back of the fifo
        void dequeue();                    // Remove the front string from the fifo
    };
}

#endif
