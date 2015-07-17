#ifndef _VanillaNode_h
#define _VanillaNode_h 1

#ifdef __GNUG__
#pragma interface
#endif

/*******************************************************************
 Copyright (c) 1997
 Hewlett-Packard Company

 Permission to use, copy, modify, distribute and sell this software and
 its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and that
 both that copyright notice and this permission notice appear in
 supporting documentation.  Hewlett-Packard Company makes no
 representations about the suitability of this software for any
 purpose.  It is provided "as is" without express or implied warranty.

 Programmer : Geroncio Galicia
 Date of Creation : 8/5/97

********************************************************************/

#include "AssociatedObj.h"
#include "AssociationList.h"
#include "ListAssociation.h"
#include "MemberAssociation.h"
#include "type.h"
#include <limits.h>
#include <iostream.h>

/** Generic node for a breadfirst-search algorithm.
This class adds a color state that can switch between white, gray, or
black. */
class VanillaNode : public AssociatedObj {

public:

  // FIXME: get rid of this method--for debugging purposes only
  void info() { 
    cout << "&VanillaNode = " << this << endl;
    cout << "&neighbors = " << &neighbors << endl;
    AssociatedObj::info();
  }

  /// Constructor.
  VanillaNode() : d(INT_MAX), pi(NULL), neighbors(*this), color(0) {}
  
  /**@name Breadth-first search parameters.  
  *These are specific to the breadth-first search algorithm described
  *in {\em Introduction to Algorithms} by Thomas Cormen, Charles
  *Leiserson, and Ronald Rivest. */
  //@{
  /// Distance from source node.
  int d;
  /// Pointer to this node's predecessor in the breadth-first tree.
  VanillaNode* pi;
  //@}

  /// List of nodes adjacent to this one.
  AssociationList neighbors;

  /// Establish a bidirectional link.
  void adjacentTo(VanillaNode &node);

  /**@name Node coloring methods. */
  //@{
  ///
  void makeWhite();
  ///
  void makeGray();
  ///
  void makeBlack();
  //@}
  
  /**@name Color query methods. */
  //@{
  ///
  int isWhite();
  ///
  int isGray();
  //@}
  
private:
  
  int color;

  /// Iterator.
  friend class VanillaNodeIter;

};

/** Iterator for the VanillaNode class.
Returns a pointer to a VanillaNode. */
class VanillaNodeIter : private AssociatedObjIter {
public:

  /// Constructor.
  VanillaNodeIter(AssociationList& al) : AssociatedObjIter(al) {}

  /// Return pointer to the next VanillaNode in list.
  inline VanillaNode* next() { 
    return (VanillaNode*)AssociatedObjIter::next();
  }
  /// Synonym for next();
  VanillaNode* operator++(POSTFIX_OP) { return next(); }
  /// Reset pointer to head of list.
  AssociatedObjIter::reset;
};

#endif
