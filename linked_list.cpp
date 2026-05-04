#include <iostream>
#include <vector>

class myLinkedList {
    vector<string> names = { "zero", "one", "two", "three", "four", "five"};

    numberOfNodes = names.size();
    shared_ptr<Node> root = make_shared<Node>(names[0]);
    shared_ptr<Node> node = root;

    for (int i=1; i < numberOfNodes; i++) {
        node->next = make_shared<Node>(names[i]);
        node = node->next;
    }
    
    node->next = root;
}



