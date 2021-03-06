#if !defined (BINARYSEARCHTREE_H)
#define BINARYSEARCHTREE_H

#include "BinaryTreeIterator.h"
#include "TreeNode.h"
#include "Text.h"
#include "Line.h"
#include "Drawable.h"
using CSC2110::String;
#include <iostream>
using namespace std;

template < class T >
class BinarySearchTree : public Drawable
{

   private:
      TreeNode<T>* root;
      int sze;
      void destroyItem(TreeNode<T>* tNode);
      void destroy();

      TreeNode<T>* insertItem(TreeNode<T>* tNode, T* item);
      TreeNode<T>* removeItem(TreeNode<T>* tNode, String* sk);
      TreeNode<T>* removeNode(TreeNode<T>* tNode);
      TreeNode<T>* removeLeftMost(TreeNode<T>* tNode);
      T* findLeftMost(TreeNode<T>* tNode);

      TreeNode<T>* getRootNode();
      void setRootNode(TreeNode<T>* tNode);
      int getHeight(TreeNode<T>* tNode);
      bool isBalanced(TreeNode<T>* tNode);

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);

      virtual void drawRec(TreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr);

   public:
      BinarySearchTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
      ~BinarySearchTree();

      bool isEmpty();
      void makeEmpty();

      T* retrieve(String* search_keys);
      void insert(T* item);
      void remove(String* search_keys);

      BinaryTreeIterator<T>* iterator();
      T* getRootItem();
      int getHeight();
      bool isBalanced();

      T** toArray();
      static T** treeSort(T** items, int num_items, int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));

      virtual void draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height);
      virtual void mouseClicked(int x, int y);
};

template < class T >
void BinarySearchTree<T>::remove(String* sk)
{
   //DO THIS

   root = removeItem(root, sk);


}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeItem(TreeNode<T>* tNode, String* sk)
{
   //DO THIS

   T* key_comp = tNode->getItem();
   int comp = (*compare_keys) (sk, key_comp);

   if(comp == 0)
    {
      TreeNode<T>* remove_node = removeNode(tNode);
       
      return remove_node;
      }

   else if(comp < 0)
   {
     tNode = tNode->getLeft();
     removeItem(tNode, sk);

     }

   else
   {
     tNode = tNode->getRight();
     removeItem(tNode,sk);

     }


}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeNode(TreeNode<T>* tNode)
{
   if (tNode->getLeft() == NULL && tNode->getRight() == NULL)
   {
      delete tNode;
      return NULL;
   }
   else if (tNode->getLeft() == NULL)
   {
      TreeNode<T>* temp = tNode->getRight();
      delete tNode;
      return temp;
   }
   else if (tNode->getRight() == NULL)
   {
      TreeNode<T>* temp = tNode->getLeft();
      delete tNode;
      return temp;
   }
   else 
   {
      //DO THIS

     T* item = findLeftMost(tNode->getRight());

     tNode->setItem(item);

     TreeNode<T>* remove_node = removeLeftMost(tNode->getRight());
     tNode->setRight(remove_node);

     return tNode;
   }
}

template < class T >
T* BinarySearchTree<T>::findLeftMost(TreeNode<T>* tNode)
{
   //DO THIS (use a while loop)

   while(tNode->getLeft() != NULL)
   {
     tNode = tNode->getLeft();
     }

  return tNode->getItem();

}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeLeftMost(TreeNode<T>* tNode)
{
   //DO THIS (recursion)

   if(tNode->getLeft() == NULL)
    {
      TreeNode<T>* right_node = tNode->getRight();
           
      delete tNode;
      return right_node;
      }

   else
   {
     TreeNode<T>* subtree = removeLeftMost(tNode->getLeft());
     tNode->setLeft(subtree);

     return tNode;
    }

}

template < class T >
T** BinarySearchTree<T>::toArray()
{
   //DO THIS

   T** sorted_cds = new T* [sze];

//do an inorder traversal, putting the items in the array

   BinaryTreeIterator<T>* iter = iterator();
   iter->setInorder();

   int i = 0;

   while(iter->hasNext())
   {
      T* item = iter->next();

      sorted_cds[i] = item;

      i++;
     }

/*
   for(int i = 0; i < sze; i++)
    {
      TreeNode<T>* temp = removeLeftMost(root);     //this method only works for removing, not for sorting an array

      if(temp == root)
       {
         setRootNode(temp->getRight());

         }
      
      sorted_cds[i] = temp->getItem();


      }
   */

   return sorted_cds;

}

template < class T >
T** BinarySearchTree<T>::treeSort(T** items, int num_items, int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   //DO THIS

   BinarySearchTree<T>* bst = new BinarySearchTree<T>(comp_items, comp_keys);

   for(int i = 0; i < num_items; i++)
   {
    bst->insert(items[i]);
     }

    cout << "before toArray #2" << endl;
	
    T** sorted = bst->toArray();
  cout << "after toArray #2" << endl;

    return sorted;
}

template < class T >
BinarySearchTree<T>::BinarySearchTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   root = NULL;
   sze = 0;

   compare_items = comp_items;
   compare_keys = comp_keys;
}

template < class T >
BinarySearchTree<T>::~BinarySearchTree()
{
   destroy();
}

template < class T >
void BinarySearchTree<T>::destroy()
{
   destroyItem(root);
}

template < class T >
void BinarySearchTree<T>::destroyItem(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
bool BinarySearchTree<T>::isEmpty()
{
   return sze == 0;
}

template < class T >
void BinarySearchTree<T>::makeEmpty()
{
   destroy();
   root == NULL;
   sze = 0;
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::getRootNode()
{
   return root;
}

template < class T >
void BinarySearchTree<T>::setRootNode(TreeNode<T>* tNode)
{  
   root = tNode;
}

template < class T >
T* BinarySearchTree<T>::getRootItem()
{
   T* rootItem = root->getItem();
   return rootItem;
}

template < class T >
void BinarySearchTree<T>::insert(T* item)
{
   root = insertItem(root, item);
}

template < class T >
T* BinarySearchTree<T>::retrieve(String* sk)
{
   TreeNode<T>* tNode = getRootNode();

   while (tNode != NULL)
   {
      T* node_items = tNode->getItem();
      int comp = (*compare_keys) (sk, node_items);

      if (comp == 0)
      {
         //no duplicate search keys allowed, so do nothing
         return node_items;
      }
      else if (comp < 0)
      {
         tNode = tNode->getLeft();
      }
      else
      {
         tNode = tNode->getRight();
      }
   }

   return NULL; //item is not in the tree
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::insertItem(TreeNode<T>* tNode, T* item)
{
   TreeNode<T>* subtree;
   if (tNode == NULL)
   { 
      sze++;
      return new TreeNode<T>(item);
   }

   T* node_items = tNode->getItem();
   int comp = (*compare_items) (item, node_items);

   if (comp == 0)
   {
      //no duplicate search keys allowed, so do nothing
      return tNode;
   }
   else if (comp < 0)
   {
      subtree = insertItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);
   }
   else
   {
      subtree = insertItem(tNode->getRight(), item);
      tNode->setRight(subtree);
   }
   
   return tNode;
}

template < class T >
BinaryTreeIterator<T>* BinarySearchTree<T>::iterator()
{
   return new BinaryTreeIterator<T>(root);
}

template < class T >
void BinarySearchTree<T>::draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height)
{
   Line line(new Color(0, 0, 0), 5.0);
   drawRec(getRootNode(), cr, &line, width, width/2, 20);
}

template < class T >
void BinarySearchTree<T>::drawRec(TreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(cr, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), cr, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), cr, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(cr, x_curr, y_curr);
   }
}

template < class T >
void BinarySearchTree<T>::mouseClicked(int x, int y) {}

#endif
