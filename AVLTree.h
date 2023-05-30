#ifndef AVLTREE_H
#define AVLTREE_H
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const string hands[] = {"a High Card!", "One Pair!", "Two Pairs!", "Three of a Kind!", "a Straight!", "a Flush", "a Full House!", "Four of a Kind!", "a Straight Flush", "a Royal Flush"}; 

template <typename T>
class Node {
private:
   int height;
public:
   T data; //Round
   string winner;
   int handVal;
   int winnings;
   Node *left;
   Node *right;

   Node(T t) {
      data = t;
      height = 1;
      left = NULL;
      right = NULL;
   }

   int getHeight(Node<T> *n) {
      if (n == NULL) {
         return 0;
      }
      return n->height;
   }

   void setHeight(int h) {
      height = h;
   }

   int getBalance(Node *n) {
      if (n == NULL)
         return 0;
      return getHeight(n->left) - getHeight(n->right);
   }
};

template <typename T>
class AVLTree {
private:
   Node<T> *root = NULL;

   Node<T> *insert(Node<T> *n, T t) {
      //Basic tree insert
      if (n == NULL) {
         return new Node(t);
      } else if (t < n->data) {
         n->left = insert(n->left, t);
      } else if (t > n->data) {
         n->right = insert(n->right, t);
      } else {
         //Return and skip balancing if this key already exists
         return n;
      }

      //Update heights and check the balance after insert recursion is done
      n->setHeight(1 + max(n->getHeight(n->right), n->getHeight(n->left)));

      int balance = n->getBalance(n);

      //Left Left
      if (balance > 1 && t < n->left->data) {
         return rRotate(n);
      }

      //Right Right
      if (balance < -1 && t > n->right->data) {
         return lRotate(n);
      }

      //Left Right
      if (balance > 1 && t > n->left->data) {
         n->left = lRotate(n->left);
         return rRotate(n);
      }

      //Right Left
      if (balance < -1 && t < n->right->data) {
         n->right = rRotate(n->right);
         return lRotate(n);
      }

      //No balance needed
      return n;
   }

   Node<T> *deleteNode(Node<T> *n, T t) {
      //Find value
      //Base Case
      if (n == NULL) {
         return n;
      }
      //Less than current node
      if (t < n->data) {
         n->left = deleteNode(n->left, t);
      }//greater than current node
      else if (t > n->data) {
         n->right = deleteNode(n->right, t);
      }
      //Once value is found, modify children nodes, then delete the node
      else {
         //Node has no children
         if (n->left == NULL && n->right == NULL)return NULL;
         //Node with right child
         else if(n->left == NULL){
            Node<T> * temp = n->right;
            free(n);
            return temp;
         } //Node with right child
         else if(n->right == NULL){
            Node<T> *temp = n->left;
            free(n);
            return temp;
         }
         //Node with 2 children nodes
         Node<T> * temp = minChildVal(n->right);
         //Set node to new lowest
         n->data = temp->data;
         //Restart recursive delete at next highest node
         n->right = deleteNode(n->right,temp->data);
      }
      //If no children nodes, you are done
      if (n == NULL){return n;}
      
      //Update height and balance for new node
      n->setHeight(1 + max(n->getHeight(n->right), n->getHeight(n->left)));
      int balance = n->getBalance(n);
      
      //Check balance factor and balance if needed
      
      //Left Left
      if (balance > 1 && n->getBalance(n->left) >= 0){return rRotate(n);}
      //Right Right
      if (balance < -1 && n->getBalance(n->right) <= 0){return lRotate(n);}
      //Left Right
      if (balance > 1 && n->getBalance(n->left) < 0){
         n->left = lRotate(n->left);
         return rRotate(n);
      }
      //Right Left
      if (balance < -1 && n->getBalance(n->right) > 0){
         n->right = rRotate(n->right);
         return lRotate(n);
      }
      return n;
   }

   Node<T> *minChildVal(Node<T> *n){
      Node<T> *min = n;
      
      while(min && min->left != NULL){min = min->left;}
      
      return min;
   }

   //a, b, and c as in :
   //       a
   //      /
   //    b
   //  /
   //c

   Node<T> *rRotate(Node<T> *a) {
      Node<T> *b = a->left;
      a->left = b->right;
      b->right = a;

      //readjust heights
      a->setHeight(1 + max(a->getHeight(a->right), a->getHeight(a->left)));
      b->setHeight(1 + max(b->getHeight(b->right), b->getHeight(b->left)));

      return b;
   }

   //a, b, and c as in :
   // a
   //  \
   //    b
   //     \
   //      c

   Node<T> *lRotate(Node<T> *a) {
      Node<T> *b = a->right;
      a->right = b->left;
      b->left = a;

      //readjust heights
      a->setHeight(1 + max(a->getHeight(a->right), a->getHeight(a->left)));
      b->setHeight(1 + max(b->getHeight(b->right), b->getHeight(b->left)));

      return b;
   }

   //Left Print Right
   void inOrder(Node<T> *n) {
      if (n == NULL) return;
      inOrder(n->left);
      cout << "Round: " <<n->data << " - " << n->winner << " won with " << hands[n->handVal-1] << " They won $" << n->winnings << "!" << endl;
      inOrder(n->right);
   }
   
   Node<T> *find(Node<T> *n, T t){
      if (n == NULL) {
         return n;
      }
      //Less than current node
      if (t < n->data) {
         n->left = find(n->left, t);
      }//greater than current node
      else if (t > n->data) {
         n->right = find(n->right, t);
      }
      //Once value is found, modify children nodes, then delete the node
      else {
         return n;
      }
   }

public:

   void insert(T t) {
      root = insert(root, t);
   }

   void deleteNode(T t) {
      root = deleteNode(root, t);
   }

   void inOrder() {
      inOrder(root);
      cout << endl;
   }
   
   void addHandVal(int val, int round){
      Node<T> *temp = find(root,round);
      temp->handVal = val;
   }
   
   void addNameMoney(string name, int win, int round){
      Node<T> *temp = find(root,round);
      temp->winner = name;
      temp->winnings = win;
   }
};
#endif /* AVLTREE_H */

