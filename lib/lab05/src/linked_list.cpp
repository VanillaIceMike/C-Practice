#include <linked_list.h>
#include <stdexcept>

namespace lab5 {

    linked_list::linked_list() {
        head = nullptr;
        tail = nullptr;
    }

    linked_list::linked_list(std::string &data) {
        head = tail = new node(data);
    }

    linked_list::linked_list(const linked_list &original) {
        head=tail= nullptr;
        if(original.isEmpty()){return;}

        node * node_jumper = original.head;

        while(node_jumper){
            append(node_jumper->data);
            node_jumper = node_jumper->next;
        }
    }

    linked_list::~linked_list() {
        while(!isEmpty()){
            remove(0);
        }
    }

    linked_list &lab5::linked_list::operator=(const linked_list &RHS) {
        if(this == &RHS)return *this;

        if(RHS.isEmpty()){head=tail= nullptr; return *this;}

        node * node_jumper = RHS.head;

        while(node_jumper){
            append(node_jumper->data);
            node_jumper = node_jumper->next;
        }

        return *this;
    }


    bool linked_list::isEmpty() const {
        if((head && !tail) || (!head && tail))throw std::logic_error ("Error head and tail are not both null"); // this should never happen internal error
        return !head;
    }

    unsigned linked_list::listSize() const {
        node * node_jumper=head;
        unsigned size=0;

        while(node_jumper){
            node_jumper=node_jumper->next;
            ++size;
        }
        return size;
    }

    void linked_list::insert(const std::string input, unsigned int location) {
        if(!is_valid_location(location) && (isEmpty() && location != 0))throw std::invalid_argument( "received location outside of bounds" );
        //todo: check for valid location before inserting
        if(location == 0 && isEmpty()) head = tail = new node(input);
        else
        {
            if (location == 0){
                auto * temp = new node(input);
                temp->next=head;
                head=temp;
            }
            else if (location == listSize()){
                append(input);
            }
            else{
                node * node_holder = find_node(location-1);
                auto * node_creater = new node(input);
                node_creater->next = node_holder->next;
                node_holder->next = node_creater;
            }
        }
    }

    void linked_list::append(const std::string input) {
        if(isEmpty()) {head=tail=new node(input); return;}

        tail->next=new node(input);
        tail = tail->next;
    }

    void linked_list::remove(unsigned location) {
        if (!is_valid_location(location))throw std::invalid_argument( "received location outside of bounds" );
        if(head == tail){
            delete head;
            head = tail = nullptr;
        }
        else if(location == 0){
            node * node_to_delete = head;
            head = head->next;
            delete node_to_delete;
        }else{
            node *node_before_delete = find_node(location - 1);
            node *node_to_delete = node_before_delete->next;
            node_before_delete->next = node_to_delete->next;
            if (node_to_delete == tail) tail = node_before_delete;
            delete node_to_delete;
        }
    }

    std::ostream& operator<<(std::ostream &stream, linked_list &RHS) {
        node* node_jumper = RHS.head;
        while (node_jumper){
            stream << node_jumper->data << " -> ";
            node_jumper=node_jumper->next;
        }
        stream << "NULL";
        return stream;
    }

    std::istream& operator>>(std::istream &stream, linked_list &RHS) {
        std::istreambuf_iterator<char> eos;
        std::string input(std::istreambuf_iterator<char>(stream), eos);
        RHS = linked_list(input);
        return stream;
    }

    void linked_list::sort() {
        struct{
            unsigned location=0;
            std::string value;
        } largest;

        linked_list sorted_list;
        unsigned location=0;
        node* node_jumper;

        while(!isEmpty()){
            node_jumper = head;
            location = 0;
            largest.value = node_jumper->data;
            largest.location = 0;
            while(node_jumper){
                if(node_jumper->data < largest.value){
                    largest.value = node_jumper->data;
                    largest.location = location;
                }
                node_jumper = node_jumper->next;
                ++location;
            }
            sorted_list.append(largest.value);
            remove(largest.location);
        }
        *this = sorted_list;
    }

    node *linked_list::find_node(unsigned int location) const{
        if(!is_valid_location(location))throw std::invalid_argument( "received location outside of bounds" );
        node* node_jumper = head;
        for(unsigned i=0; i<location; ++i) node_jumper = node_jumper->next;

        return node_jumper;
    }

    bool linked_list::is_valid_location(unsigned location) const{
        return location < listSize();
    }

    std::string linked_list::get_value_at(unsigned location)const{
        const std::string data = find_node(location)->data;
        return data;
    }
}
