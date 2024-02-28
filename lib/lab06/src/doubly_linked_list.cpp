#include "../inc/doubly_linked_list.h"

namespace lab6{
    doubly_linked_list::doubly_linked_list() 
    {
        head = nullptr;
        tail = nullptr;

    }


    doubly_linked_list::doubly_linked_list(int input) 
    {
        head = nullptr;
        tail = nullptr;
        append(input);

    }

    doubly_linked_list::doubly_linked_list(std::vector<int> vector_input) 
    {
        head = nullptr;
        tail  =nullptr;
        for (int i = 0 ; i < vector_input.size() ; i++)
            append(vector_input[i]);
    }

    doubly_linked_list::doubly_linked_list(const doubly_linked_list &original) 
    {
        node* current_node = original.head;
        this->head= nullptr;
        this->tail = nullptr;
        while(current_node != nullptr){
            this->append(current_node -> get_data());
            current_node = current_node -> next;
        }
    }

    doubly_linked_list::~doubly_linked_list() 
    {
        node* current_node=head;
        node* previous;
        while(current_node && current_node->next){
            previous=current_node;
            current_node= current_node->next;
            delete previous;
        }
        delete current_node;
        head=nullptr;
        tail=nullptr;

    }

    int doubly_linked_list::get_data(unsigned position) 
    {
        node* current_node = head;
        if (head == nullptr)
            throw std::out_of_range("Linked List is empty");
        else if (position >= size())
            throw std::out_of_range("Position out of bound");
        else{
            for (int i = 0 ; i < position ; i++)
                current_node = current_node -> next;
            return current_node->get_data();
        }
    }

    std::vector<int> doubly_linked_list::get_set(unsigned position_from, unsigned position_to) 
    {
        std::vector<int> set;
        node* current_node = head;
        if (position_from > position_to || position_from >= size() || position_to >= size())
            throw std::out_of_range("Position out of bound");
        else{
            for (int j = 0; j < position_from ; j++)
                current_node = current_node -> next;
            for (int i = position_from ; i <= position_to ; i++){
                set.push_back(current_node -> get_data());
                current_node = current_node -> next ;
            }
        }
        return set;
    }

    unsigned doubly_linked_list::size()
    {
        node* count_node = head;
        unsigned int count = 0;
        if (head == nullptr)
            count = 0;
        else if (head != nullptr && head == tail)
            count = 1;
        else{
            while (count_node != nullptr){
                count++;
                count_node = count_node -> next;
            }
        }
        return count;
    }

    bool doubly_linked_list::is_empty() 
    {
        return (head == nullptr)? true: false;

    }

    void doubly_linked_list::append(int input) 
    {
        node* input_node = new node(input);
        input_node -> next = nullptr;
        if (head == nullptr){
            head = input_node;
            tail = input_node;
        }
        else{
            tail -> next = input_node;
            tail = input_node;
        }

    }

    void doubly_linked_list::insert(int input, unsigned int location) 
    {
        node* previous_node;
        node* current_node = head;
        node* input_node = new node(input);
        if ((location == 0 && head == nullptr)){
            head = nullptr;
            tail = nullptr;
            append(input);
        }
        else if(location == 0 && head != nullptr){
            input_node -> next = current_node;
            head = input_node;
        }
        else if(location > size())
            throw std::out_of_range("Position out of bound");
        else if(location == size())
            append(input);
        else{
            for(int i = 0 ; i < location ; i++){
                previous_node = current_node;
                current_node = current_node -> next;
            }
            previous_node -> next = input_node;
            input_node -> next = current_node;
        }
    }

    void doubly_linked_list::remove(unsigned location) 
    {
        int position = 0;
        node* current_node = nullptr;
        node* previous_node = nullptr;

        if(location >= size())
            throw std::out_of_range("Out of position.");
        else if(head == nullptr && location == 0 )
            throw std::out_of_range("Linked list is empty.");
        else if(head != nullptr && location == 0)
            head = head-> next ;
        else if(location == size() -1){
            current_node = head;
            for(int i = 0; i< size() -1 ; i++){
                previous_node = current_node;
                current_node = current_node -> next;
            }
            tail = previous_node;
            tail -> next = nullptr;
        }
        else{
            current_node = head;
            do{
                if (position == location)
                {
                    current_node = current_node -> next;
                    (previous_node -> next) -> next = nullptr;
                    previous_node -> next = current_node;
                }
                else
                {
                    previous_node = current_node;
                    current_node = current_node -> next;
                }
                position ++;
            }
            while(position <= location);
        }
    }

    doubly_linked_list doubly_linked_list::split(unsigned position) 
    {
        doubly_linked_list split(get_set(position, size() - 1));
        for (int i = size() - 1; i >= position && i >= 0; i--) {
            remove(i);
        }
        return split;
    }

    doubly_linked_list doubly_linked_list::split_set(unsigned position_1, unsigned position_2) 
    {
        doubly_linked_list split_set(get_set(position_1,position_2));
        for (int i = position_2; i>= position_1; i--){
            remove(i);
        }
        return split_set;

    }

    void doubly_linked_list::swap(unsigned position_1, unsigned position_2) 
    {
        node* Pos1_node = head;
        node* Pos2_node = head;
        if (position_1 >= size() || position_2 >= size())
            throw std::out_of_range("Position out of bound");
        else{
            for (int i = 0 ; i < position_1 ; i++)
                Pos1_node = Pos1_node -> next;


            for (int j = 0 ; j < position_2 ; j++)
                Pos2_node = Pos2_node -> next;

            int i =(Pos1_node->get_data());
            int j =(Pos2_node->get_data());
            remove(position_2);
            remove(position_1);
            insert(j,position_1);
            insert(i,position_2);

        }

    }

    void doubly_linked_list::swap_set(unsigned location_1_start, unsigned location_1_end, unsigned location_2_start,
                                      unsigned location_2_end) 
                                      {
        if ((location_1_end - location_1_start) != (location_2_end - location_2_start) ||
            location_1_end < location_1_start || location_2_end < location_2_start ||
            ((location_1_end <= location_2_end) && (location_2_start <= location_1_end)) ||
            ((location_1_start <= location_2_end) && (location_2_start <= location_1_start)))
            throw std::out_of_range("Cannot swap.");
        else {
            int lo1=location_1_start;
            int lo2=location_2_start;
            for(int i = 0; i <= (location_2_end - location_2_start); i++ ){
                swap(lo1,lo2);
                lo1++;
                lo2++;
            }
        }
    }

    void doubly_linked_list::sort() 
    {
        // Implement Insertion Sort
        std::vector <int> to_sort = get_set(0,this->size()-1);
        int i, key, j;
        for (i = 1; i < to_sort.size() ; i++)
        {
            key = to_sort[i];
            j = i - 1;
            while (j >= 0 && to_sort[j] > key)
            {
                to_sort[j + 1] = to_sort[j];
                j = j - 1;
            }
            to_sort[j + 1] = key;
        }
        for (int i = 0 ; i < to_sort.size() ; i++){
            this->append(to_sort[i]);
            this->remove(0);
        }
    }

    doubly_linked_list doubly_linked_list::operator+(const doubly_linked_list &rhs) const 
    {
        lab6::doubly_linked_list *to_return = new lab6::doubly_linked_list ;
        node* this_current_node = this->head;

        while (this_current_node != nullptr){
            to_return->append(this_current_node->get_data());
            this_current_node = this_current_node -> next;
        }
        node* rhs_current_node = rhs.head;

        while (rhs_current_node != nullptr){
            to_return->append(rhs_current_node->get_data());
            rhs_current_node = rhs_current_node -> next;
        }
        return *to_return;
    }

    doubly_linked_list& doubly_linked_list::operator=(const doubly_linked_list &rhs) 
    {
        if (this == &rhs)
            return *this;
        else{
            node* current_node = rhs.head;
            while (current_node != nullptr){
                append(current_node -> get_data());
                current_node = current_node -> next;
            }
            return *this;
        }
    }

    doubly_linked_list& doubly_linked_list::operator+=(const doubly_linked_list &rhs) {
        node* current_node = rhs.head;
        while (current_node != nullptr){
            append(current_node -> get_data());
            current_node = current_node -> next;
        }
        return *this;
    }

    bool doubly_linked_list::operator==(const doubly_linked_list &rhs) {
        node* current_node = rhs.head;
        int count=0;
        while (current_node != nullptr){
            count++;
            current_node = current_node -> next;
        }
        if (this->size() != count)
            return false;
        else{
            node* this_current_node = this->head;
            node* rhs_current_node = rhs.head;
            for (int i=0; i<this->size() ; i++){
                if(this_current_node ->get_data() == rhs_current_node ->get_data()) {
                    this_current_node = this_current_node->next;
                    rhs_current_node = rhs_current_node -> next;
                }
                else
                    return false;
            }
            return true;
        }
    }

    std::ostream &operator<<(std::ostream &stream, doubly_linked_list &RHS) {
        node* current_node = RHS.head;
        stream <<"NULL <- ";
        stream << current_node -> get_data();
        current_node = current_node -> next;
        while (current_node != nullptr){
            stream << " <-> ";
            stream << current_node -> get_data();
            current_node = current_node -> next;
        }
        stream << " -> NULL";
        return stream;
    }

    std::istream &operator>>(std::istream &stream, doubly_linked_list &RHS) {
        std::string temp;
        stream >> temp;
        RHS.append(stoi(temp));
        return stream;
    }
}

