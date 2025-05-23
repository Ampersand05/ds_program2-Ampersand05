#ifndef BINARYNODE_
#define BINARYNODE_
#include <iostream>

template <class T>
class BinaryNode {
    public:
        T  data;
        //Pointers to children of the node
        BinaryNode<T> * left;
        BinaryNode<T> * right;

        BinaryNode(){ 
            left= nullptr; 
            right=nullptr; 
            data=T(0);
        }
        BinaryNode(T item){
          data = item;
          left = nullptr;
          right = nullptr;
    }
};

#endif
