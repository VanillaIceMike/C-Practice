#include <linked_list_m.h>
#include <stdexcept>


    linked_list_m::linked_list_m() {
        head = nullptr;
        tail = nullptr;
    }


    linked_list_m::~linked_list_m() {
        while(!isEmpty()){
            remove(0);
        }
    }

linked_list_m &linked_list_m::operator=(const linked_list_m &RHS) {
    if(this == &RHS)return *this;

    if(RHS.isEmpty()){head=tail= nullptr; return *this;}

    stack_node * node_jumper = RHS.head;

    while(node_jumper){
        append(node_jumper->data);
        node_jumper = node_jumper->next;
    }

    return *this;

}

bool linked_list_m::isEmpty() const {
        if((head && !tail) || (!head && tail))throw std::logic_error ("Error head and tail are not both null"); // this should never happen internal error
        return !head;
}

unsigned linked_list_m::listSize() const {
        stack_node * node_jumper=head;
        unsigned size=0;

        while(node_jumper){
            node_jumper=node_jumper->next;
            ++size;
        }
        return size;
    }

    void linked_list_m::insert(const value_date input, unsigned int location) {
        if(!is_valid_location(location) && (isEmpty() && location != 0))throw std::invalid_argument( "received location outside of bounds" );
        //todo: check for valid location before inserting
        if(location == 0 && isEmpty()) head = tail = new stack_node(input);
        else
        {
            if (location == 0){
                auto * temp = new stack_node(input);
                temp->next=head;
                head=temp;
            }
            else if (location == listSize()){
                append(input);
            }
            else{
                stack_node * node_holder = find_node(location-1);
                auto * node_creater = new stack_node(input);
                node_creater->next = node_holder->next;
                node_holder->next = node_creater;
            }
        }
    }

    void linked_list_m::append(value_date input) {
        if(isEmpty()) {head=tail=new stack_node(input); return;}

        tail->next=new stack_node(input);
        tail = tail->next;
    }

    void linked_list_m::remove(unsigned location) {
        if (!is_valid_location(location))throw std::invalid_argument( "received location outside of bounds" );
        if(head == tail){
            delete head;
            head = tail = nullptr;
        }
        else if(location == 0){
            stack_node * node_to_delete = head;
            head = head->next;
            delete node_to_delete;
        }else{
            stack_node *node_before_delete = find_node(location - 1);
            stack_node *node_to_delete = node_before_delete->next;
            node_before_delete->next = node_to_delete->next;
            if (node_to_delete == tail) tail = node_before_delete;
            delete node_to_delete;
        }
    }





   /* void linked_list_m::sort() {
        struct{
            unsigned location=0;
            std::string value;
        } largest;

        linked_list_m sorted_list;
        unsigned location=0;
        stack_node* node_jumper;

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
    }*/

    stack_node *linked_list_m::find_node(unsigned int location) const{
        if(!is_valid_location(location))throw std::invalid_argument( "received location outside of bounds" );
        stack_node* node_jumper = head;
        for(unsigned i=0; i<location; ++i) node_jumper = node_jumper->next;

        return node_jumper;
    }

    bool linked_list_m::is_valid_location(unsigned location) const{
        return location < listSize();
    }

    value_date linked_list_m::get_value_at(unsigned location)const{
        const value_date data = find_node(location)->data;
        return data;
    }
