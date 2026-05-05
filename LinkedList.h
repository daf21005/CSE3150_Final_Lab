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

        // helper functions for unit testing - AI implemented here for creating unittests
        // is [zero] reachable via weak ptr
        bool isRootAlive() const { return weak_root.lock() != nullptr; }
 
        // is [zero]'s next node ([one]) still reachable via weak ptr
        // after SERVER_delete this returns false since [one] is destroyed
        bool isRootNextAlive() const {
            auto r = weak_root.lock();
            if (!r) return false;
            return r->weak_next.lock() != nullptr;
        }
    
        // how many shared_ptrs currently own [zero]?
        int getRootUseCount() const { return root ? root.use_count() : 0; }

};


#endif