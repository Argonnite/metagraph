#include "AssociatedObj.h"
#ifndef _AssociationList_h
#define _AssociationList_h 1
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
 Date of Creation : 7/11/97

********************************************************************/

#include "ListAssociation.h"
#include "MemberAssociation.h"
#include "type.h"
#include <stl.h>
#include <iostream.h>
// FIXME: get rid of iostream

class Association;

/// Lists of Association objects.
class AssociationList {

public:

  // FIXME: remove this method and iostream above.
  void info() {
    cout << &nearObj << " owns this " << this << " private list\n";
  }
   
  /** Constructor requires an owner.
  The owner must be of type AssociatedObj. */
  AssociationList(AssociatedObj& owner);

  /// Copy constructor
  AssociationList(const AssociationList& al) {
    


  }

  /** Copy assignment operator.  
  Copies links to a far AssociationList.  Does not copy links where
  the far Association is a MemberAssociation. */
  AssociationList& operator=(const AssociationList& al) {
    if( this != &al) { // Beware of self-assignment: al = al
      dissociate();

      // FIXME: what happens here if intervening arc AssociatedObj?
      // FIXME: write iterators
      ListAssociationIter next(&al); // Iterate over list to copy from.
      ListAssociation *original;
      while( (original=next++) != NULL ) {
	associate(&original->far->nearList); // Associate to a far list.
      }
    }
    return *this;
  }

  /// Destructor also deletes all Associations in this list.
  ~AssociationList();

  /**@name Associate methods 
   * These methods create a new Association in this list. 
   */
  //@{
  /** Link to an AssociatedObj. 
  Instantiate a new Association object in the far AssociatedObj's list 
  and link that to the new one here. */
  void associate(AssociatedObj& farObj);

  /** Link to an AssociationList.
  Instantiate a new Association object in the specified (far) list and
  link that to the the new one here. */
  void associate(AssociationList& farList);

  /** Link to an Association, particularly a MemberAssociation.
  Note that this method cannot be explicitly used to link to a
  ListAssociation.  When a ListAssociation is instantiated it is, by
  design, already assigned a link, and a link for any Association
  cannot be redefined without first dissociating the link.  A
  ListAssociation is designed to be destroyed when it dissociates,
  unlike a MemberAssociation which persists.  Privately (that is,
  hidden from the public interface), this method is used in
  implementation to link to a ListAssociation. */
  void associate(Association& farAssociate);
  //@}

  /// Delete all Associations in this list but don't delete self.
  void dissociate();

  /// Return number of Association entries in this list.
  inline int size() const { return dimen; }

protected:

private:

  /// Logical size of the list.
  int dimen; 

  /// My local owner.
  AssociatedObj& nearObj;

  /** Pointer to the top of the list.
  Must be pointer since put() reseats. */
  ListAssociation* headNode;

  /// Pointer to the end of the list.
  ListAssociation* lastNode;

  /** Create a new yet-to-be-associated link in this list.  
  Link attributes can be implemented only in Association subclasses by
  overriding this method. */
  ListAssociation& makeNew();

  /// Add at top of the list.
  void put(ListAssociation& member);

  /// List empty?
  inline int empty() const { return (headNode == 0); } 

  /** A ListAssociation must be able to insert and delete self from here.  
  A ListAssociation claiming {\bf *this} as an owner must update the
  dimen and headNode members of {\bf *this} when the ListAssociation
  comes and goes. */
  friend class ListAssociation;

  /// Iterator class.
  friend class AssociatedObjIter;

};


/** Iterator for an AssociationList.
Returns a pointer to an AssociatedObj. */
class AssociatedObjIter {
public:

  /// Constructor.
  AssociatedObjIter(const AssociationList& l);

  /// Reset pointer to head of list.
  void reset();

  // FIXME: get rid of cout's
  /// Return pointer to the next AssociatedObj in list.
  inline AssociatedObj* next() {
    if(startAtHead) { // If starting at beginning of list.
      startAtHead = FALSE;
      if (list->headNode) { // List not empty.
	ref = list->headNode;
	return ref->farOwnerPtr();
      } else { // List is empty, pass NULL.
	ref = 0;
	return (AssociatedObj*)NULL;
      }
    } else { // If not at beginning of list.
      if (ref != list->lastNode) { // If not at end of list.
	if (ref) { // If pointer to element is not NULL, return next.
	  ref = ref->next;
	  return ref->farOwnerPtr();
	} else { // If pointer is NULL, then end of list was already
		 // passed.
	  ref = 0;
	  return (AssociatedObj*)NULL;
	}
      } else { // If at end of list.
	ref = 0;
	return (AssociatedObj*)NULL;
      }
    }
  }

  /// Synonym for next().
  AssociatedObj* operator++ (POSTFIX_OP) { return next(); }

private:
  const AssociationList* list;
  ListAssociation *ref;	
  int startAtHead;
};

#endif
