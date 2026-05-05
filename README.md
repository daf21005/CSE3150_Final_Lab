# CSE3150 Final Lab - Node Cycles and week_ptrs
In this lab assignment we explore C++ weak_pts and using them within a linked list.  

The idea is to have a SERVER that creates the shared linked list and a CLIENT that acceeses the circular linked list - unless the SERVER has deleted it.

## Run and Compile main program:
```
g++ mainLinkedList.cpp LinkedList.cpp Node.cpp -o mainProg
./mainProg
```

## Run and Compile unit test:
```
g++ testLinkedList.cpp LinkedList.cpp Node.cpp -o testProg
./testProg
```