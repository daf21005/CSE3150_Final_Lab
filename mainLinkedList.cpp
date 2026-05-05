#include <iostream>
#include "LinkedList.h"

int main() {
    std::vector<std::string> names = {"zero", "one", "two", "three", "four", "five"};
 
    {
        LinkedList list(names);
 
        // Step 1 - SERVER builds the circular linked list
        list.SERVER_buildCircularLinkedList();
 
        // Step 2 - SERVER prints via shared_ptrs
        list.SERVER_printLinkedList();
 
        // Step 3 - CLIENT prints via weak_ptrs (list is still alive)
        list.CLIENT_printLinkedList();
 
        // Step 4 - SERVER destroys the shared_ptrs (nodes 1-5 destructors fire here)
        list.SERVER_deleteCircularLinkedList();
 
        // Step 5 - CLIENT tries to print — weak_ptrs are stale, "Yipes!" for each
        std::cout << "Client after linked list deleted:" << std::endl;
        std::cout << "---------------------------------" << std::endl;
        list.CLIENT_printLinkedList();
 
    } // LinkedList goes out of scope here → LinkedList destructor runs
      // → root = nullptr → [zero] destructor fires last


    return 0;
}