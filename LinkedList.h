#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "Node.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory> // for smart ptrs


class LinkedList {

    std::shared_ptr<Node> root;
    std::weak_ptr<Node> weak_root;

    int numberOfNodes;
    std::vector<std::string> names;

    public:
        LinkedList(const std::vector<std::string>& names);
        ~LinkedList();

        // the required methods
        void SERVER_buildCircularLinkedList();
        void SERVER_deleteCircularLinkedList();
        void SERVER_printLinkedList();
        void CLIENT_printLinkedList();        

};


#endif