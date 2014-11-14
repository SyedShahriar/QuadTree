#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

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
#include <algorithm>
using namespace std;


template <typename T>
class Quadtree;

template <typename T>
class Quadtree_node {

//member variables
private:
    T       x_value;
    T       y_value;
    
    Quadtree_node *north_west;
    Quadtree_node *north_east;
    Quadtree_node *south_west;
    Quadtree_node *south_east;
    
public:
    Quadtree_node( T const & = T(), T const & = T() );
    
    T retrieve_x() const;
    T retrieve_y() const;
    
    Quadtree_node *nw() const;
    Quadtree_node *ne() const;
    Quadtree_node *sw() const;
    Quadtree_node *se() const;
    
    T min_x() const;
    T min_y() const;
    
    T max_x() const;
    T max_y() const;
    
    T sum_x() const;
    T sum_y() const;
    
    bool member( T const &, T const & ) const;
    
    bool insert( T const &, T const & );
    void clear();
    
	friend class Quadtree<T>;
};

//Intializes x and y values, to the input values, and sets all subtrees(nw,ne,sw,se) to zero.
template <typename T>
Quadtree_node<T>::Quadtree_node( T const &x, T const &y ):
x_value( x ),
y_value( y ),
north_west( 0 ),
north_east( 0 ),
south_west( 0 ),
south_east( 0 ) {
	// empty constructor
}

//Returns the x and y values of the current node respectively.
template <typename T>
T Quadtree_node<T>::retrieve_x() const {
	return x_value;
}

template <typename T>
T Quadtree_node<T>::retrieve_y() const {
	return y_value;
}
//Child pointer functions.Returns pointers to northwest,northeast,southwest,and south east.
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::nw() const {
	return north_west;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::ne() const {
	return north_east;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::sw() const {
	return south_west;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::se() const {
	return south_east;
}

//Recursively finds the minimum x value and returns it.
template <typename T>
T Quadtree_node<T>::min_x() const {
	//Once we have reached empty nodes in both NW and SW, then we know we have found the minimum x value, so we return the current x value.
   if(nw()==0 && sw()==0)
   {
       return retrieve_x();
   }
    
    //If we reach the end of NW, then we must keep searching in the SW
    if(nw()==0)
    {
        return sw()->min_x();
    }
    
    //If we reach the end of SW, then we must keep searching in the NW
    if(sw()==0)
    {
        return nw()->min_x();
    }
    
    //Compares the minimum x values between the SW and NW, and returns the lower x value between the two
    return min(sw()->min_x(), nw()->min_x());
    
}

//Recursively finds the minimum y value and returns it.
template <typename T>
T Quadtree_node<T>::min_y() const {
	
    //Once we have reached empty nodes in both SW and SE, then we know we have found the minimum y value, so we return the current y value.
    if(sw()==0 && se()==0)
    {
        return retrieve_y();
    }
    
    //If we reach the end of SW, then we must keep searching in the SE
    if(sw()==0)
    {
        return se()->min_y();
    }
    
    //If we reach the end of SE, then we must keep searching in the SW
    if(se()==0)
    {
        return sw()->min_y();
    }
    
    //Compares the minimum y values between the SE and SW, and returns the lower y value between the two
    return min(sw()->min_y(), se()->min_y());
}

//Recursively finds the maximum x value and returns it.
template <typename T>
T Quadtree_node<T>::max_x() const {
	
	//Once we have reached empty nodes in both NE and SE, then we know we have found the maximum x value, so we return the current x value.
    if(ne()==0 && se()==0)
    {
        return retrieve_x();
    }
    
    //If we reach the end of NE, then we must keep searching in the SE
    if(ne()==0)
    {
        return se()->max_x();
    }
    
    //If we reach the end of SE, then we must keep searching in the NE
    if(se()==0)
    {
        return ne()->max_x();
    }
    
    //Compares the maximum x values between the NE and SE, and returns the higher x value between the two
    return max(ne()->max_x(), se()->max_x());
}

//Recursively finds the maximum y value and returns it.
template <typename T>
T Quadtree_node<T>::max_y() const {
	
    //Once we have reached empty nodes in both NE and NW, then we know we have found the maximum y value, so we return the current y value.
    if(ne()==0 && nw()==0)
    {
        return retrieve_y();
    }
    
    //If we reach the end of NE, then we must keep searching in the NW
    if(ne()==0)
    {
        return nw()->max_y();
    }
    
    //If we reach the end of NW, then we must keep searching in the NE
    if(nw()==0)
    {
        return ne()->max_y();
    }
    
    //Compares the maximum x values between the NW and NE, and returns the higher x value between the two
    return max(nw()->max_y(), ne()->max_y());
}

//Recursively adds all the x values, and returns the sum of the all x values from all the nodes in the Quadtree
template <typename T>
T Quadtree_node<T>::sum_x() const {
	if ( this == 0 )
    {
		return 0;
	}
    else {
		return sw()->sum_x() + se()->sum_x() + ne()->sum_x()+
        nw()->sum_x()+ retrieve_x();
	}
}

//Recursively adds all the y values, and returns the sum of the all y values from all the nodes in the Quadtree

template <typename T>
T Quadtree_node<T>::sum_y() const {
	if ( this == 0 ) {
		// hint...
		return 0;
	} else {
		return sw()->sum_y() + se()->sum_y() + ne()->sum_y()+
        nw()->sum_y()+ retrieve_y();
	}
}

//Returns true if the pair (x,y) is stored in the current node, or in the Quadtree starting at the current node. Returns false otherwise.
template <typename T>
bool Quadtree_node<T>::member( T const &x, T const &y ) const {
	if ( this == 0 ) {
		return false;
	}
    
    //Once the input values, match the current node values, we have have found the values.
    if(x==retrieve_x() && y==retrieve_y())
    {
        return true;
    }
    
    //If the input x,y values are greater than or equal to the current nodes x,y values then we recursively search in the NE subtree
    if (x>=retrieve_x() && y>=retrieve_y())
    {
        return ne()->member(x,y);
    }
    
    //If only the input x value is greater than or equal to the current nodes x value, then we recursively search in the SE subtree
    if (x>=retrieve_x() && y<retrieve_y())
    {
        return se()->member(x,y);
    }
    
     //If only the input y value is greater than or equal to the current nodes y value, then we recursively search in the NW subtree
    if (x<retrieve_x() && y>=retrieve_y())
    {
        return nw()->member(x,y);
    }
    
    //If both the input x,y values are less than the current nodes x,y values, then we recursively search in the SW subtree
    if (x<retrieve_x() && y<retrieve_y())
    {
        return sw()->member(x,y);
    }
    
	return false;
}

//Inserts the (x,y) pair appropriately into the Quadtree
template <typename T>
bool Quadtree_node<T>::insert( T const &x, T const &y ) {
	
    //If the current nodes values are equivalent to the insert (x,y) values then we return false, to avoid duplicates
    if(retrieve_x()==x && retrieve_y()==y)
    {
        return false;
    }
    
    //If the input x,y values are greater than or equal to the current nodes (x,y) values then we recursively search till the NE subtree is empty
    if (x>=retrieve_x() && y>=retrieve_y()) {
        
        //When we get to the end, we create a new node and insert.
        if (ne()==0) {
            north_east=new Quadtree_node<T>(x,y);
            return true;
        }
        
        //Otherwise we keep looking
        else
            return ne()->insert(x,y);
            
    }
    
    //If the input y value is greater than or equal to the current nodes y value then we recursively search till the NW subtree is empty
    if (x<retrieve_x() && y>=retrieve_y()) {
        
        //When we get to the end, we create a new node and insert.
        if (nw()==0) {
            north_west=new Quadtree_node<T>(x,y);
            return true;
        }
        
        //Otherwise we keep looking
        else
            return nw()->insert(x,y);
        
    }
    
    //If the input x value is greater than or equal to the current nodes x value then we recursively search till the SE subtree is empty
    if (x>=retrieve_x() && y<retrieve_y()) {
        
        //When we get to the end, we create a new node and insert.
        if (se()==0) {
            south_east=new Quadtree_node<T>(x,y);
            return true;
        }
        
        //Otherwise we keep looking
        else
            return se()->insert(x,y);
        
    }
    
   //If the input x,y values are less than the current nodes (x,y) values then we recursively search till the SW subtree is empty
    if (x<retrieve_x() && y<retrieve_y()) {
        
        //When we get to the end, we create a new node and insert.
        if (sw()==0) {
            south_west=new Quadtree_node<T>(x,y);
            return true;
        }
        
         //Otherwise we keep looking
        else
            return sw()->insert(x,y);
        
    }
    
   
    return false;
}
    
    
//Calls clear on any non-zero subtree and deletes that node
template <typename T>
void Quadtree_node<T>::clear() {
    
    //If SE is not non zero, then call clear and delete SE node
    if(se()!=0)
    {
        se()->clear();
        south_east=0;
    }
    
    //If SW is not non zero, then call clear and delete SW node
    if(sw()!=0)
    {
        sw()->clear();
        south_west=0;
        
    }
    
    //If NE is not non zero, then call clear and delete NE node
    if(ne()!=0)
    {
        ne()->clear();
       north_east=0;
    }
    
    //If NW is not non zero, then call clear and delete NW node
    if(nw()!=0)
    {
        nw()->clear();
        north_west=0;
    }
    
    delete this;
    
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
