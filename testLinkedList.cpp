#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "./include/doctest.h" 
#include "LinkedList.h"

const std::vector<std::string> NAMES = {"zero", "one", "two", "three", "four", "five"};


TEST_CASE("Before build: root is not yet alive") {
    LinkedList list(NAMES);
    CHECK(list.isRootAlive() == false);
    CHECK(list.isRootNextAlive() == false);
    CHECK(list.getRootUseCount() == 0);
}

TEST_CASE("After build: root is alive via weak_ptr") {
    LinkedList list(NAMES);
    list.SERVER_buildCircularLinkedList();
 
    // weak_root should successfully lock — [zero] is alive
    CHECK(list.isRootAlive() == true);
}

TEST_CASE("After build: root's next node is alive via weak_ptr") {
    LinkedList list(NAMES);
    list.SERVER_buildCircularLinkedList();
 
    // [zero]->weak_next should lock to [one] — it exists
    CHECK(list.isRootNextAlive() == true);
}
 
TEST_CASE("After build: root use_count is 2 (root member + circular next from last node)") {
    LinkedList list(NAMES);
    list.SERVER_buildCircularLinkedList();
 
    // [zero] is owned by: root member + [five]->next (circular)
    // The weak_root.lock() inside isRootAlive() is temporary and already released
    CHECK(list.getRootUseCount() == 2);
}

TEST_CASE("After delete: root [zero] is still alive (held by LinkedList member)") {
    LinkedList list(NAMES);
    list.SERVER_buildCircularLinkedList();
    list.SERVER_deleteCircularLinkedList();
 
    // root still holds [zero] — it should survive the delete step
    CHECK(list.isRootAlive() == true);
}