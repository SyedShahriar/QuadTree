#ifndef QUADTREE_H
#define QUADTREE_H

/*****************************************
 * UW User ID:  sgshahri
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall) 2014
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "ece250.h"
#include "Quadtree_node.h"
#include "Exception.h"
#include <iostream>

template <typename T>
class Quadtree {
private:
    Quadtree_node<T> *tree_root;  //pointer to root node of tree
    int count;                    //used to keep track of the number of elements currently in the quadtree
    
public:
    Quadtree();
    ~Quadtree();
    
    // Accessors
    
    int size() const;
    bool empty() const;
    
    T min_x() const;
    T min_y() const;
    
    T max_x() const;
    T max_y() const;
    
    T sum_x() const;
    T sum_y() const;
    
    Quadtree_node<T> *root() const;
    bool member( T const &, T const & ) const;
    
    // Mutators
    
    void insert( T const &, T const & );
    void clear();
    
	
};

template <typename T>
Quadtree<T>::Quadtree():
tree_root( 0 ),
count( 0 ) {
	// empty constructor
}

//Deletes all the nodes in the Quadtree
template <typename T>
Quadtree<T>::~Quadtree() {
    clear();
   
}

//Returns the current number of elements(x,y pairs) in the quadtree
template <typename T>
int Quadtree<T>::size() const {
	//return 0;
    return count;
}

//Checks if the tree is empty
template <typename T>
bool Quadtree<T>::empty() const {
	//return true;
    if(size()==0)
        return true;
    else
        return false;
}

//Returns the smallest x value currently stored in the tree. Throws an underflow exception if tree is empty.
template <typename T>
T Quadtree<T>::min_x() const {
	if(size()==0)
        throw underflow();
    else
    return tree_root->min_x();
}

//Returns the smallest y value currently stored in the tree. Throws an underflow exception if tree is empty.
template <typename T>
T Quadtree<T>::min_y() const {
    if(size()==0)
        throw underflow();
    else
	return tree_root->min_y();
}

//Returns the largest x value currently stored in the tree. Throws an underflow exception if tree is empty.
template <typename T>
T Quadtree<T>::max_x() const {
	if(size()==0)
        throw underflow();
    else
    return tree_root->max_x();
}

//Returns the largest y value currently stored in the tree. Throws an underflow exception if tree is empty.
template <typename T>
T Quadtree<T>::max_y() const {
    if(size()==0)
        throw underflow();
    else
	return tree_root->max_y();
}

//Returns the sum of the x values within the quadtree
template <typename T>
T Quadtree<T>::sum_x() const {
	
    if (size()==0) {
        return 0;
    }
    return tree_root->sum_x();
}

//Returns the sum of the y values within the quadtree
template <typename T>
T Quadtree<T>::sum_y() const {
    
    if(size()==0)
    {
        return 0;
    }
	
    return tree_root->sum_y();
}

//Returns the address of the root node. If the tree is empty,this method will return zero.
template <typename T>
Quadtree_node<T> *Quadtree<T>::root() const {
	if (size()==0) {
        return 0;
    }
    else
    return tree_root;
}

//Checks for specified pair of (x,y) values, if found returns true, else false.
template <typename T>
bool Quadtree<T>::member( T const &x, T const &y ) const {
	if(size()==0)
    {
        return false;
    }
    
    if(tree_root->member(x,y)==true)
    {
        return true;
    }
    
    else
        return false;
    
}

//Inserts the specified x,y pair into the tree. If the root node is empty, a new quadtree node is created.
//If root node is not empty, it handles the insertion, by placing it in a appropriate node.
template <typename T>
void Quadtree<T>::insert( T const &x, T const &y ) {
    if(size()==0)
    {
        tree_root=new Quadtree_node<T>(x,y);
        count ++;
    }
    if(tree_root->insert(x,y)==true)
    {
        count++;
    }
    
}

//Clears all the elements in the tree, including the root if necessary
template <typename T>
void Quadtree<T>::clear() {
    tree_root->clear();
    tree_root=0;
    count=0;
    
    
}



// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif