#include "../inc/tree.h"

namespace lab7 {
    void clear(node *to_clear);
    int recursive_level(node* top, int location);
    void recursive_insert(node *&root, int value);
    node* find_node(node* top, int key);
    node* find_parent(node* top, node* target);
    bool has_children(node* target);
    node* calc_swap(node* top);
    void recursive_path_to(node* top, int key);
    unsigned recursive_size(node* top);
    unsigned recursive_depth(node* top);
    bool recursive_in_tree(node* top, int key);
    int recursive_frequency(node* top, int key);
    void recursive_string(node* top, std::string &answer);
    void recursive_print(node *root, std::vector<int> &vec);
    node* node_copy(node* top);


    // Construct an empty tree
    tree::tree() 
    {
        root = nullptr;
        tree_size = 0;
    }

    // Copy constructor
    tree::tree(const tree &copy) 
    {
    }

    // Deconstruct tree
    tree::~tree() 
    {
        clear(root);
    }

    // Insert
    void tree::insert(int value) 
    {
        recursive_insert(root, value);
    }


    // Remove key return true if the key is deleted, and false if it isn't in the tree
    bool tree::remove(int key) {
        // remove key from tree iteratively using root and update frequency
        if (root == nullptr) {
            return false;
        }
        // if root is key, remove root
        if (root->data == key) {
            if (root->frequency > 1) {
                root->frequency--;
                return true;
            } else {
                node *temp = root;
                root = root->right;
                delete temp;
                tree_size--;
                return true;
            }
        }
        node *current = root;
        node *parent = nullptr;
        while (current != nullptr) {
            if (current->data == key) {
                if (current->frequency > 1) {
                    current->frequency--;
                    return true;
                } else if (current->frequency == 1) {
                    if (current->left == nullptr && current->right == nullptr) {
                        if (parent->left == current) {
                            parent->left = nullptr;
                        } else {
                            parent->right = nullptr;
                        }
                        delete current;
                        tree_size--;
                        return true;
                    } else if (current->left == nullptr) {
                        if (parent->left == current) {
                            parent->left = current->right;
                        } else {
                            parent->right = current->right;
                        }
                        delete current;
                        tree_size--;
                        return true;
                    } else if (current->right == nullptr) {
                        if (parent->left == current) {
                            parent->left = current->left;
                        } else {
                            parent->right = current->left;
                        }
                        delete current;
                        tree_size--;
                        return true;
                    } else {
                        node *temp = current->right;
                        while (temp->left != nullptr) {
                            temp = temp->left;
                        }
                        temp->left = current->left;
                        if (parent->left == current) {
                            parent->left = current->right;
                        } else {
                            parent->right = current->right;
                        }
                        delete current;
                        tree_size--;
                        return true;
                    }
                }
            } else if (current->data > key) {
                parent = current;
                current = current->left;
            } else {
                parent = current;
                current = current->right;
            }
        }
    }

    // What level is key on?
    int tree::level(int key) 
    {
       // node* top;
        if(!(in_tree(key)))
        {
            return -1;
        }
        else
        {
            return recursive_level(root, key);
        }
    }

    // Print the path to the key, starting with root
    void tree::path_to(int key) 
    {
        if(in_tree(key))
        {
            recursive_path_to(root, key);
        }
    }

    // Number of items in the tree
    unsigned tree::size() 
    {
        return recursive_size(root);
    }

    // Calculate the depth of the tree, longest string of connections
    unsigned tree::depth() 
    {
        if(!(size() <= 1))
        {
            return recursive_depth(root) - 1;
        }
        else return 0;
    }

    // Determine whether the given key is in the tree
    bool tree::in_tree(int key) 
    {
       return recursive_in_tree(root, key);
    }

    // Return the number of times that value is in the tree
    int tree::get_frequency(int key) 
    {
        return recursive_frequency(root, key);
    }

    // Return a string of all of the elements in the tree in order
    std::string tree::to_string() 
    {
        auto answer = std::string();
        recursive_string(root, answer);
        return answer;
    }

    //Use the to string function for the following two functions
    // Print the tree least to greatest, Include duplicates
    void tree::print() 
    {
         // print the tree in order with duplicates using to_string_helper
        std::vector<int> vec;
        recursive_print(root, vec);
        for (int i = 0; i < vec.size(); i++) 
        {
            std::cout << vec[i] << " ";
        }
        std::cout << "\n";
    }

    // Print the tree least to greatest, Include duplicates
    std::ostream &operator<<(std::ostream &stream, tree &RHS) 
    {
        stream << RHS.to_string();
        return stream;
    }

    // Operator= Overload. Allowing for copying of trees
    tree &tree::operator=(const tree &rhs) 
    {
        this->root = node_copy(rhs.root);
        this->tree_size = rhs.tree_size;
    }

    //Auxiliary function implementations//
    int recursive_level(node* top, int location) 
    {
        if (top->data != location) 
        {
            if (location < top->data) 
            {                                   //if location is less than top node data go left
                return (recursive_level(top->left, location) + 1);
            }
            else if (location > top->data) 
            {                                  //if location is greater than top node data goes right
                return (recursive_level(top->right, location) + 1);
            }
        }
        else return 0;
    }

    void tree::recursive_insert(node *&root, int value)
    {
        // insert value into tree recursively using root and update frequency
        if (root == nullptr) 
        {
            root = new node(value);
            tree_size++;
        } 
        else if (value < root->data) 
        {
            recursive_insert(root->left, value);
        } 
        else if (value > root->data) 
        {
            recursive_insert(root->right, value);
        } 
        else 
        {
            root->frequency++;
        }

    }

    node* find_node(node* top, int key)
    {
        if(top->data == key)
        {
            return top;
        }
        else if(key < top->data)
        {
            return(find_node(top->left, key));
        }
        else if(key > top->data)
        {
            return(find_node(top->right, key));
        }
    }
    node* find_parent(node* top, node* target)
    {
        if(top != target)
        {
            if(top->left == target || top->right == target)
            {
                return top;
            }
            else if (target->data < top->data)
            {
                return find_parent(top->left, target);
            }
            else if (target->data > top->data)
            {
                return find_parent(top->right,  target);
            }

        }
        else return top;
    }

    bool has_children(node* target)
    {
        if (!(target->left != nullptr || target->right != nullptr))
        {
            return false;
        }
        else return true;
    }

    node* calc_swap(node* top)
    {
        if(!(top->left))
        {
            top = top->right;
            return top;
        }
        else
            top = top->left;
            while(top->right)
            {
                top = top->right;
                return top;
            }
    }
    void recursive_path_to(node* top, int key)
    {
        std::cout << top->data;
        if(!(top->data == key))
        {
            std::cout << " -> ";
            if(key < top->data)
            {
                recursive_path_to(top->left, key);
            }
            else recursive_path_to(top->right, key);
        }
        else
        {
            std::cout << std::endl;
            return;
        }
    }

    unsigned recursive_size(node* top)
    {
        if(top != nullptr)
        {
            return top->frequency + recursive_size(top->left) + recursive_size(top->right);
        }
        else
            return 0;
    }

    unsigned recursive_depth(node* top) 
    {
        if (top != nullptr) 
        {
            unsigned left = 0;
            unsigned right = 0;
            left = 1 + recursive_depth(top->left);
            right = 1 + recursive_depth(top->right);
            if (right < left) 
            {
                return left;
            } 
            else return right;
        }
        else return 0;
    }
    bool recursive_in_tree(node* top, int key) 
    {
        if (top != nullptr) 
        {
            if (top->data == key) 
            {
                return true;
            } 
            else if (key < top->data) 
            {
                return recursive_in_tree(top->left, key);
            } 
            else if (key > top->data) 
            {
                return recursive_in_tree(top->right, key);
            }
        }
        else return false;
    }

    int recursive_frequency(node* top, int key)
    {
        if (top != nullptr) 
        {
            if (top->data == key) 
            {
                return top->frequency;
            } 
            else if (key < top->data) 
            {
                return recursive_frequency(top->left, key);
            } 
            else if (key > top->data) 
            {
                return recursive_frequency(top->right, key);
            }
        }
        else return 0;
    }

    void recursive_string(node* top, std::string &answer)
    {
        if(top != nullptr)
        {
            recursive_string(top->left, answer);
            for(int i = 0; i < top->frequency; i++)
            {
                answer += std::to_string(top->data);
                answer += " ";
            }
        }
        else return;
    }

    void recursive_print(node *root, std::vector<int> &vec)
    {
       if (root == nullptr) 
        {
            return;
        }
        recursive_print(root->left, vec);
        for (int i = 0; i < root->frequency; i++) 
        {
            vec.push_back(root->data);
        }
        recursive_print(root->right, vec);
    }

    node* node_copy(node* top)
    {
        if(top)
        {
            node* temp = new node(top);
            if(top->left) temp->left = node_copy(top->left);
            if(top->right) temp->right = node_copy(top->right);
            return temp;
        }
        else return top;
    }
    /**************************
     * Extra credit functions *
     **************************/

    // Return a vector with all of the nodes that are greater than the input key in the tree
    std::vector<int> tree::values_above(int key) {

    }

    // Merge rhs into this. Demo to a TA for credit
    tree tree::operator+(const tree &rhs) const {

    }

    // Balance the tree using any published algorithm. Demo to a TA for credit
    void tree::balance() {

    }

    /*********************************************************************
     * Recursion Example                                                 *
     * Print the linked list from greatest to least using recursion      *
     *********************************************************************/

    // Auxiliary functions
    void node_print_gtl(node *top) 
    {
        if (top == nullptr) return;
        node_print_gtl(top->right);
        for (int i = 0; i < top->frequency; i++) std::cout << top->data << " ";
        node_print_gtl(top->left);
    }

    void clear(node *to_clear) 
    {
        if (to_clear == nullptr) return;
        if (to_clear->left != nullptr) clear(to_clear->left);
        if (to_clear->right != nullptr) clear(to_clear->right);
        delete to_clear;
    }

    // Class function
    void tree::print_gtl() 
    {
        node_print_gtl(root);
        std::cout << std::endl;
    }
}