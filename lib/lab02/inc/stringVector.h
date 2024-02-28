
#ifndef CMPE126S18_LABS_STRINGVECTOR_H
#define CMPE126S18_LABS_STRINGVECTOR_H

#include <string>

namespace lab2 {
    class stringVector {
    private:
        std::string *data;
        unsigned length;
        unsigned allocated_length;

    public:
        stringVector();
        stringVector(unsigned size); // add this to your code for Lab 3 
        virtual ~stringVector();
        unsigned size()const;
        unsigned capacity()const;
        void reserve(unsigned new_size);
        bool empty()const;
        void append(std::string new_data);
        void increaeLength();
        void swap(unsigned pos1, unsigned pos2);
        stringVector &operator=(stringVector const &rhs);
        std::string &operator[](unsigned position);
        void sort();
        void insert(unsigned int pos, std::string new_data);
    };
}

#endif //CMPE126S18_LABS_STRINGVECTOR_H
