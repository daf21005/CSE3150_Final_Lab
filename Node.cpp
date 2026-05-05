#include "Node.h"
#include <iostream>

Node::Node(std::string name) : name{name} {}
Node::~Node() { 
    std::cout << "Node [" << name << "] destructor" << std::endl; 
}