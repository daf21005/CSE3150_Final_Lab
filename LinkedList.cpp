#include "LinkedList.h"

// constructor and destructor
LinkedList::LinkedList(const std::vector<std::string>& names) : names{names}, numberOfNodes{(int)names.size()} {}
LinkedList::~LinkedList() {}


// task 1 - server create linked list
void LinkedList::SERVER_buildCircularLinkedList() {
    root = std::make_shared<Node>(names[0]);

    weak_root = root;

    // walking foward
    std::shared_ptr<Node> current = root;
    for (int i = 1; i < numberOfNodes; i++) {
        current->next = std::make_shared<Node>(names[i]);
        current->weak_next = current->next;
        current = current->next;
    }

    // close the circle
    current->next = root;
    current->weak_next = root;
}

// task 2 - server print linked list
void LinkedList::SERVER_printLinkedList() {
    std::cout << "Server: " << std::endl;

    // traversing the LL 
    std::shared_ptr<Node> current = root;
    for (int i = 0; i < numberOfNodes; i++) {
        std::cout << "[" << current->name << "]"
                  << " : use_count: " << current.use_count()
                  << " address: "     << current.get()
                  << " next (from shared_ptr): " << current->next.get()
                  << std::endl;
        current = current->next;
    }

    std::cout << std::endl;
}

// task 4 - server deletes linked list
void LinkedList::SERVER_deleteCircularLinkedList() {
    std::cout << "Server is deleting the shared_ptrs:" << std::endl;
 
    // traverse the list and null out every node's shared_ptr->next
    // this breaks the circular chain so reference counts can drop to 0
    std::shared_ptr<Node> current = root;
    for (int i = 0; i < numberOfNodes; i++) {
        std::shared_ptr<Node> nextNode = current->next;
        current->next = nullptr; // drop the strong ref to the next node
        current = nextNode;
    }
 
    // release the linked list's own handle to root — this triggers the last destructor
    // root = nullptr;
    std::cout << std::endl;

}

// task 3 - client prints linked list
void LinkedList::CLIENT_printLinkedList() {
    std::cout << "Client:" << std::endl;
 
    // check if the linked list was deleted or not - using .lock()
    std::shared_ptr<Node> current = weak_root.lock();
    if (!current) {
        std::cout << "[Nothing]" << std::endl;
        std::cout << std::endl;
        return;
    }
 
    // just like server, traverse the linked list
    for (int i = 0; i < numberOfNodes; i++) {
        // try to get the next node via weak_ptr
        std::shared_ptr<Node> nextNode = current->weak_next.lock();
 
        std::cout << "[" << current->name << "]"
                  << " : use_count: " << current.use_count()
                  << " address: "     << current.get()
                  << " next (from weak_ptr): "
                  << (nextNode ? nextNode.get() : 0)
                  << std::endl;
 
        // if the shared ptr is deleted this message is given
        if (!nextNode) {
            std::cout << "Yipes! shared_ptr not available" << std::endl;
        }
 
        current = nextNode; // will be nullptr if the next node was deleted
        if (!current) break;
    }

    std::cout << std::endl;
}

// task 5 - showcase client trying to print linked list after deletion
// done in main