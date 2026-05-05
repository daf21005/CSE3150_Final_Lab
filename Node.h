#ifndef _NODE_H
#define _NODE_H

#include <string>
#include <memory>
#include <iostream>
 
struct Node {
    std::string name;

    // server access 
    std::shared_ptr<Node> next;
    // client access
    std::weak_ptr<Node> weak_next;
 
    Node(std::string name);
    ~Node();
};

#endif