#include "../inc/inventory.h"

int inventory::reserve_upc() 
{
    srand(42);
    auto random_upc_location = int(rand()%upc_generator.size());
    auto a = upc_generator.begin();
    for(auto a = upc_generator.begin(); --random_upc_location != 0; a++);
    while(!a->second && a != upc_generator.end()) a++;
    a->second = false;
    return a->first;
}

void inventory::release_upc(int input_upc) 
{
    auto val =  upc_generator.find(input_upc);
    if(val->first == input_upc && val->second == false){
        val->second = true;
        return;
    }
    else throw "UPC not valid";
}

bool inventory::valid_upc(int input_upc) 
{
    if(input_upc == 0) return false;
    auto val = inventory::upc_generator.find(input_upc);
    return val->first == input_upc;
}

void inventory::initialize_upc() {
    srand(17); // Initial seed
    for(int i = 1; i< 1000; i++) {
        int unique_upc = 1000000 + rand() % 9000000;
        inventory::upc_generator.insert(std::pair<int, bool>(unique_upc, true));
    }
}

inventory::inventory() {
    head = nullptr;
    tail = nullptr;
    initialize_upc();
}

inventory::~inventory() 
{

}

void inventory::add_sku(std::string new_name, int initial_price, int initial_inventory, int initial_date) 
{
    int upc = reserve_upc();
    if(isEmpty()) 
    {
        head=tail = new inventory_node(upc,new_name,initial_inventory,initial_price,initial_date);
        return;
    }

    tail->next=new inventory_node(upc,new_name,initial_inventory,initial_price,initial_date);
    tail = tail->next;

}

void inventory::remove_sku(int input_upc) 
{
    if(valid_upc(input_upc))
    {
        if(head == NULL && tail == NULL)
        {
            delete head;
            head = NULL;
            tail = NULL;
        } 
        else
        {
            inventory_node* head1 = head;
            inventory_node* prev = NULL;
            if(head1 != NULL && head1->upc == input_upc)
            {
                head = head1->next;
                delete head1;
                return;
            }
        }
    }
    throw "Incorrect UPC";
}

std::vector<int> inventory::get_upc(std::string input_name) 
{
   std::vector<int> find;
   inventory_node *temp = head;
   while (temp != NULL)
   {
       if((input_name) == (temp->name))
       {
           find.push_back(temp->upc);
       }
        temp = temp->next;
   }
    return find;
}

int inventory::get_price(int input_upc) 
{
   inventory_node *temp = head;
   while (temp != NULL)
   {
       if((input_upc) == (temp->upc))
       {
           return temp->price.top().value;
       }
        temp = temp->next;
   }
    throw "Wrong UPC";
}

int inventory::get_inventory(int input_upc) 
{
    inventory_node *temp = head;
   while (temp != NULL)
   {
       if((input_upc) == (temp->upc))
       {
           return temp->inventory_count;
       }
        temp = temp->next;
   }
    throw "Wrong UPC";
}

std::string inventory::get_name(int input_upc) 
{
   inventory_node *temp = head;
   while (temp != NULL)
   {
       if((input_upc) == (temp->upc))
       {
           return temp->name;
       }
        temp = temp->next;
   }
    throw "Wrong name";
}

void inventory::adjust_price(int input_upc, int new_price, int new_date)
{
   bool statement = false;
   inventory_node *temp = head;
   while (temp != NULL)
   {
       if((input_upc) == (temp->upc))
       {
           statement = true;
           value_date time = value_date();
           time.value = new_price;
           time.date = new_date;
           temp->price.push(time);
       }
        temp = temp->next;
   }
   if (!statement)
   {
        throw "Wrong name";
   }
}

void inventory::adjust_inventory(int input_upc, int new_inventory) 
{
    bool statement = false;
   inventory_node *temp = head;
   while (temp != NULL)
   {
       if((input_upc) == (temp->upc))
       {
           temp->inventory_count = new_inventory;
           statement = true;
       }
        temp = temp->next;
   }
   if (!statement)
   {
        throw "Wrong name";
   }
}

inventory_node *inventory::get_head() 
{
    return head;
}

bool inventory::isEmpty() const 
{
    if((head && !tail) || (!head && tail))throw std::logic_error ("Error head and tail are not both null"); // this should never happen internal error
    return !head;
}