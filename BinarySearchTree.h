#ifndef BINARYTREE_
#define BINARYTREE_
#include "BinaryNode.h"

#include <iostream>
#include <fstream>
using namespace std;

template <class T>
class BinarySearchTree {
  private:
    BinaryNode<T> * root;
    int size;
 
    BinaryNode<T> *find (T item, BinaryNode<T> *t) ;
    bool insert(T item, BinaryNode<T> *&t) ;
    void remove (T item, BinaryNode<T> *&t);
    void clear(BinaryNode<T> *& t) ;

    // Functions that will return a given tree in Preorder, Postorder, and Inorder transversal methods
    string printPreorder(BinaryNode<T> *t);
    string printPostorder(BinaryNode<T> *t);
    string printInorder(BinaryNode<T> *t);

    int correctCompares;
    int incorrectCompares;
    //Temp variable for how many compares the current word has
    int compares;
 
  public:
    int getCorrectCompares();
    int getIncorrectCompares();

    BinarySearchTree(){ 
        root =nullptr; size=0;  
    }
    ~BinarySearchTree(){ 
        clear(root); 
    }

    BinaryNode<T> * find(T item){
      return find (item, root);
    }

    bool insert (T item);

    // Functions for storing mispelled words linearly as if the tree were a linked list
    //so they can be written to a text file in the order they appeared
    bool linkedInsert(T item);
    void writeLinkedToText();
    string printReversedLinkedList(BinaryNode<T> *t);

    BinaryNode<T> *findMax (BinaryNode<T> *t) ;
    BinaryNode<T> *findMin (BinaryNode<T> *t) ;
    void writeToTextPreorder();
    void writeToTextPostorder();
    void writeToTextInorder();

    int getSize(){ 
        return size;
    }
    int isEmpty(){ 
        return size ==0;
    }
};


template <class T>
BinaryNode<T> * BinarySearchTree<T>:: find (T item,  BinaryNode<T> *t) {
    if(t == nullptr){
        //The word was not found in the tree so the compares it took get added to incorrectCompares
        incorrectCompares += compares;
        compares = 0;
        return nullptr;
    } else if(item.compare(t->data) < 0){
        compares++;
        return find(item, t-> left);
    } else if(item.compare(t->data) > 0){
        compares += 2;
        return find(item, t->right);
    } else {
        //Item and t->data must be the same, so the word was found in the tree
        //so the compares for the word get added to correctCompares
        compares += 2;
        correctCompares += compares;
        compares = 0;
        return t;
    }
}

template <class T>
bool BinarySearchTree<T>:: insert (T item) {
    bool inserted = insert(item, root);
    if (inserted){
        size++;  
    } 
  return inserted;
}

template <class T>
bool BinarySearchTree<T>:: insert (T item, BinaryNode<T> *&t) {
    //Insert at the root if the root is null
    if(t == nullptr){
        t = new BinaryNode<T>(item);
        return true;
    } else if(item.compare(t->data) < 0){
        return insert(item, t->left);
    } else if(item.compare(t ->data) > 0){
        return insert(item, t->right);
    } else {
        //No insert made because the item is already in the tree
        return false;
    }
}

//Function that only inserts on the right side of the tree
//to mimic a linked list so the incorrect words can
//be kept in order
template <class T>
bool BinarySearchTree<T>:: linkedInsert(T item){
    BinaryNode<T> * tmp = new BinaryNode<T>(item);
    tmp->right = root;
    root = tmp;
    size++;
    return true;
}

//Writes the "linked list" of mispelled words to a text file
template <class T>
void BinarySearchTree<T>:: writeLinkedToText(){
    ofstream MispelledWords("mispelledWords.txt");
    MispelledWords << printReversedLinkedList(root);
    MispelledWords.close();
}

template <class T>
string BinarySearchTree<T>:: printReversedLinkedList(BinaryNode<T> *t){
    if(t->right == nullptr){
        return t->data + "\n";
    } else {
        return printReversedLinkedList(t->right) + t->data + "\n";
    }
}


template <class T>
void BinarySearchTree<T>:: clear(BinaryNode<T> *& t) {
    if (t == nullptr){
        return;
    } else {
    clear(t->left);
    clear(t->right);
    delete(t);
    t = nullptr;
    size--;
    }
}

template <class T>
BinaryNode<T> * BinarySearchTree<T>::findMin (BinaryNode<T> *t) {
    if ( t == nullptr ){
        return nullptr;
    } else if ( t -> left == nullptr ){
        return t;
    }
    return findMin (t -> left);
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::findMax (BinaryNode<T> *t) {
    if ( t == nullptr ){
        return nullptr;
    } else if ( t -> right == nullptr ){
        return t;
    }
    return findMax (t ->right);
}


template <class T>
void BinarySearchTree<T>::remove (T item, BinaryNode<T> *&t) {
  if ( t == nullptr){
    return; // Item to remove is not found, so return without doing anything
  }   
    if(item < t->data){
        remove(item, t->left);
    } else if(item > t->data){
        remove(item, t->right);
    } else {
        BinaryNode<T> * oldNode;
        if(t->left == nullptr){
            oldNode = t;
            t = t->right;
            delete oldNode;
            return;
        } else if(t->right == nullptr){
            oldNode = t;
            t = t->left;
            delete oldNode;
            return;
        }
        // Both children pointers of the node point to children
        oldNode = findMin(t -> right);
        t->data = oldNode -> data;
        remove(t -> data, t->right);
    }
}

//Function that can be used to write a tree using Preorder transversal
//to a file with the name "preOrder.txt"
template <class T>
void BinarySearchTree<T>:: writeToTextPreorder(){
    ofstream MispelledWords("preOrder.txt");
    MispelledWords << printPreorder(root);
    MispelledWords.close();
}

template <class T>
string BinarySearchTree<T>::printPreorder (BinaryNode<T> *t) {
    //Returns the "Preorder" strings of a tree
    if ( t == nullptr ){
        return "";
    } else if ( t -> left == nullptr ){
        if(t->right == nullptr){
            return (*t).data + "\n";
        } else {
            return (*t).data + "\n" + printPreorder(t->right);
        }
    }
    return (*t).data + "\n" + printPreorder (t -> left) + printPreorder (t -> right);
}

//Function that can write a tree using Postorder transversal
//to the file "postOrder.txt"
template <class T>
void BinarySearchTree<T>:: writeToTextPostorder(){
    ofstream PostOrder("postOrder.txt");
    PostOrder << printPostorder(root);
    PostOrder.close();
}

template <class T>
string BinarySearchTree<T>:: printPostorder(BinaryNode<T> *t){
    //Returns the "Postorder" strings of a tree
    if(t == nullptr){
        return"";
    } else if(t -> left == nullptr){
        if(t->right != nullptr){
            return (*t).data + "\n" + printPostorder(t->right);
        } else {
            return (*t).data + "\n";
        }
    } else {
        return printPostorder(t->left) + printPostorder(t->right) + (*t).data + "\n";
    }
}

//Function that can write a tree using Inorder transversal to the file
//"inOrder.txt"
template <class T>
void BinarySearchTree<T>:: writeToTextInorder(){
    ofstream InOrder("inOrder.txt");
    InOrder << printInorder(root);
    InOrder.close();
    
}

template <class T>
string BinarySearchTree<T>:: printInorder(BinaryNode<T> *t){
    //Returns the "Inorder" strings of a tree
    if(t == nullptr){
        return "";
    } else if(t->left == nullptr){
        return (*t).data + "\n" + printInorder(t->right);
    } else {
        return printInorder(t->left) + (*t).data + "\n" + printInorder(t->right);
    }
}

template <class T>
int BinarySearchTree<T>:: getCorrectCompares(){
    return correctCompares;
}

template <class T>
int BinarySearchTree<T>:: getIncorrectCompares(){
    return incorrectCompares;
}

#endif
