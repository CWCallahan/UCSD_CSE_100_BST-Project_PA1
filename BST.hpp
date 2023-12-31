#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
      This is inlined because it is trivial.
   */
  BST() : root(nullptr), isize(0), iheight(0) {}


  /** Default destructor.
      Delete every node in this BST.
  */
  ~BST();

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return a pair where the first element is an iterator 
   *  pointing to either the newly inserted element or the element 
   *  that was already in the BST, and the second element is true if the 
   *  element was newly inserted or false if it was already in the BST.
   * 
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)  
   */
  std::pair<iterator, bool> insert(const Data& item);


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */
  iterator find(const Data& item) const;

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const;
  
  /** Return the height of the BST.
      height of a tree starts with root at height 0
   */ 
  unsigned int height() const;


  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const;

  /** Return an iterator pointing to the first (smallest) item in the BST.
   */ 
  iterator begin() const;

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const;


private:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;
  
  /** Number of Data items stored in this BST. */
  unsigned int isize;

  //  Height of the tree with root being height 0
  unsigned int iheight;
  
  /** Find the first element of the BST
   * Helper function for the begin method above.
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root);

  /** do a postorder traversal, deleting nodes
   */
  static void deleteAll(BSTNode<Data>* n);
 };


// ********** Function definitions ****************


/** Default destructor.
    Delete every node in this BST.
*/
template <typename Data>
BST<Data>::~BST() {
  deleteAll(root);
}


/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return a pair where the first element is an iterator pointing to either the newly inserted
 *  element or the element that was already in the BST, and the second element is true if the 
 *  element was newly inserted or false if it was already in the BST.
 * 
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  
 */
template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data& item) {
  // TODO
  // HINT: Copy code from your BSTInt class and change the return value
  
  //an int to measure the height of this particular insert
  //incriments with each step down and on addition of a node 
  int tempHeight = 0;
  
  if (!root) {
    root = new BSTNode<Data>(item);
    ++isize;
    return std:: pair <BSTIterator <Data>, bool> (BSTIterator<Data>(root), true);
    //return true;// replace this one returning the it
  }

  BSTNode<Data>* curr = root;
  
  while (curr->left && curr->right) {
    if (item < curr->data) {
      curr = curr->left;
      tempHeight++; 
    }
    else if (curr->data < item) {
      curr = curr->right;
      tempHeight++;
    }
    else {
      return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(0), false);
	//return false;
    }
  }// end of while

  BSTNode<Data>* newNode = new BSTNode<Data>(item);
  //If there are children check for proper insertion conditions
  while (curr->left || curr->right) {
    
    if ( curr->left ) {
      //When the node is smaller than left current node moves downwards
      //and when it isn't set it to the right 
      if (item < curr->data) { //step
	curr = curr->left;
	tempHeight++;
      } else if (curr->right) {
        curr = curr->right;
	tempHeight++;
      } else {  //insert
	curr->right = newNode;
        newNode->parent = curr;
        ++isize;
	tempHeight++;
	if (tempHeight > iheight)
	  iheight = tempHeight; 
	//newNode->parent->print(); //uncomment to print the tree as it builds
        return std:: pair <BSTIterator <Data>, bool> (BSTIterator<Data>(newNode), true);
      }
      
    } else if (curr->right) {
      //When the node is larger than right current node moves downwards
      //and when it isn't set it to the left 
      if (item > curr->data) { //step
	curr = curr->right;
	tempHeight++;
      } else if (curr->left) {
        curr = curr->left;
	tempHeight++;	
      } else {	//insert
        curr->left = newNode;
        newNode->parent = curr;
        ++isize;
	tempHeight++;
	if (tempHeight > iheight)
	  iheight = tempHeight;
	//newNode->parent->print(); //uncomment to print the tree as it builds
        return std:: pair <BSTIterator <Data>, bool> (BSTIterator<Data>(newNode), true);
      }
    }
  }//end of while

  // Ready to insert
  if (item < curr->data) {
    curr->left = newNode;
    newNode->parent = curr;
  }
  else {
    curr->right = newNode;
    newNode->parent = curr;
  }

  ++isize;
  tempHeight++;
  if (tempHeight > iheight)
    iheight = tempHeight;
  //newNode->parent->print(); //uncomment to print the tree as it builds
  return std:: pair <BSTIterator <Data>, bool> (BSTIterator<Data>(newNode), true);//return true;

  
  // REPLACE THE LINE BELOW
  return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(0), false);

}


/** Find a Data item in the BST.
 *  Return an iterator pointing to the item, or pointing past
 *  the last node in the BST if not found.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
template <typename Data>
  BSTIterator<Data> BST<Data>::find(const Data& item) const
{
  // TODO
  // HINT: Copy code from your BSTInt class and change the return value

  BSTNode<Data>* curr = root;
  while (curr) {
    if (curr->data < item) {
      curr = curr->right;
    }
    else if (item < curr->data) {
      curr = curr->left;
    }
    else {
      return BSTIterator<Data>(curr);
    }
  }
  //return false;
  return BSTIterator<Data>(nullptr);

}

  
/** Return the number of items currently in the BST.
 */ 
template <typename Data>
unsigned int BST<Data>::size() const
{
  return isize;
}

/** Return the height of the BST.
 */
template <typename Data> 
unsigned int BST<Data>::height() const
{
  // TODO
  // HINT: Copy code from your BSTInt class
  return iheight;

}


/** Return true if the BST is empty, else false.
 */ 
template <typename Data>
bool BST<Data>::empty() const
{
  if (isize)
    return false;
  else
    return true;
}

/** Return an iterator pointing to the first (smallest) item in the BST.
 */ 
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
  return BSTIterator<Data>(first(root));
}

/** Return an iterator pointing past the last item in the BST.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
  //  BSTNode<Data>* cn = root; 
  //while (cn->right)
  //  cn = cn->right;
  //return BSTIterator<Data>(cn);
  return BSTIterator<Data>(nullptr);
}

/** Find the first element of the BST
 * Helper function for the begin method above.
 */ 
template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root)
{
  // TODO
  BSTNode<Data>* cn = root; 
  while (cn->left)
    cn = cn->left;
  return cn;
}

/** do a postorder traversal, deleting nodes
 */
template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n)
{
    if (!n)
      return;
    deleteAll(n->left);
    deleteAll(n->right);
    delete n;  // TODO
  // HINT: Copy code from your BSTInt class.
}



#endif //BST_HPP
