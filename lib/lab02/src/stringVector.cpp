#include "../inc/stringVector.h"
#include<iostream>
#include<stdexcept>

namespace lab2 
{
    stringVector::stringVector()  //constructor for private variables in class stringVector
    {
       data = new std::string[1];
       length = 0;
       allocated_length = 0;
    }
    stringVector::stringVector(unsigned size)  //constructor for private variables in class stringVector
    {
       data = new std::string[size];
       length = 0;
       allocated_length = size;
    }

    stringVector::~stringVector() //destructor for dynamic array variable data
    {
        delete [] data;  
    }

    unsigned stringVector::size() const //initilize the length as unsigned as it is a postive number always
    {
        return (unsigned)length;
    }

    unsigned stringVector::capacity() const //initilize the allocated length as unsigned as it is a postive number always
    {
        return (unsigned)allocated_length;
    }

    void stringVector::reserve(unsigned new_size) 
    {
        
        if(length > new_size) //if the length is greater than the new size
        {
            length = new_size; //set the length equal to the new size
        }

        std::string *temp = new std::string[new_size]; //set pointer string temp as dynamic and alocate its size as the new size

        for(int i = 0; i < length; i++) //for loop that iterates till i reaches the length 1 by 1
        {
            temp[i] = data[i]; //place data[i] into temp[i]
        }
        delete [] data; //delete data 

        data = new std::string[new_size]; //allocates data to new size after temp is used and sets allocated length equal to new size
        allocated_length = new_size;

        for(int i = 0; i < length; i++)
        {
             data[i] = temp[i]; //place every element from tmep back into data 
        }
        delete [] temp;
    }

    bool stringVector::empty() const
    {
        //std::cout<<"here"<<std::endl;
        if (size() == 0) return true;
        else return false;
        //std::cout<<"here"<<std::endl;
    }

    void stringVector::append(std::string new_data) //if user wants to make dynamic array larger with more elements of strings
    {

        std::string *newData = new std::string [length + 1];
        for (int i = 0; i < length; i++)
        {
            *(newData + i) = *(data + i);
        }

        *(newData + length)  = new_data;
        data = newData;
        length++;

        if (allocated_length == 0)
            allocated_length = 1;
        else if (length >= allocated_length)
        {
            allocated_length = 2 * allocated_length; // doubles the size
        }
    }

    void stringVector::swap(unsigned pos1, unsigned pos2)
    {
        //MY CODE
 

        //SAI CODE
        if (pos1 > size() || pos2 > size()) // if any of the positions out of range, throow error below
        throw std::out_of_range("Index out of Range");
        else
        {
            // Logic to swap data in pos1 and pos2
            std::string temp = data[pos1];
            data[pos1] = data[pos2];
            data[pos2] = temp;
        }
    }

    stringVector &stringVector::operator=(stringVector const &rhs) 
    {
        //FOR LAB2(my code)
        if(&data == &rhs.data) //used to determine if two containers are equal to one another
        {
            return *this; //return the object rhs.data or data since they are equal
        }
        delete [] data; //clear pointer array data to fill with new data
        length = rhs.length; //set the private length equal to the right hand side length
        allocated_length = rhs.allocated_length; //set the allocated length to the right hand side length
        data = new std::string[length]; //dynamic array data containing strings that have rhs.length elements

        for(int i = 0 ; i < length; i++) //itertate the length and replace every right hand side element in the array into data array
        {
            data[i] = rhs.data[i];
        }
        return *this; //return data[i]

        //FOR LAB3(sai code)
        // unsigned rhsSize = rhs.size();
        // std::string *rhsData = rhs.data;
        // reserve(rhsSize);
        // for(int i = 0; i < rhsSize; i++)
        // {
        //     data[i] = rhsData[i];
        // }
        // length = rhsSize;
        // allocated_length= rhsSize;
        // return *this;
    }
    
    std::string &stringVector::operator[](unsigned position) 
    {
        //FOR LAB 2 (my code)

        if(empty()) //if the length is equal to zero
        {
            throw std::logic_error("Your array is empty cannot access."); //give logic error that array is empty
        }
        if(position > allocated_length || position < 0) //if the position of the positive pointer is greater than the allocated length
                                                        //or the position is less than zero (since it is unassigned)
        {
            throw std::out_of_range("The desired position is out of range."); //give out of range error that the element is out of range
        }
        return data[position];

        //FOR LAB 3(sai code)
        // if (position >= size())
        //     throw std::out_of_range("Index out of Range");
        // else
        //     return data[position];
        
    }

    void stringVector::sort() 
    {
        std::string str; //create instance variable str to hold strings from data
        for(int i = (length - 1); i > 0; i--) //for loop that iterates till i is greater than zero and decrements from i = length - 1
        {
            for(int j = 0; j < i; j++) //for loop that iterates until j is less than i and j increments one at a time
            {
                if(data[j].compare(data[j+1]) > 0) //if the jth element in dynamic string array and the one after is smaller than the jth element,
                {
                    str = data[j]; //then set the instance variable str to that element j that is greater than the one after
                    data[j] = data[j+1]; //set the jth element equal to the one after 
                    data[j+1] = str; //then place it in str
                }
            }
        }
    }
}