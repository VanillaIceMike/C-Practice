#include "../inc/inventory_node.h"
#include "stack_node.h"
inventory_node::inventory_node(int input_upc, std::string input_name, int input_count, int input_price, int date) 
{
    // HINT: for the attribute price, the data type is stack of structs.
    // so to push the initial price to stack, construct a struct first and push to stack
    // Remaining all attributes are straight forward.

    /*
     * Fill in all the attributes for the constructor to work;
     * eg: name = input_name;
     */
    upc = input_upc;
    name = input_name;
    inventory_count = input_count;
    value_date to_add = value_date();
    to_add.value = input_price;
    to_add.date = date;
    price.push(to_add);
    next = nullptr;

    next = nullptr;;
}

inventory_node::~inventory_node()=default;

