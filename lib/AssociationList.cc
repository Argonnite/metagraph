static const char file_id[] = "AssociationList.cc";
/******************************************************************
 Copyright (c) 1997
 Hewlett-Packard Company

 Permission to use, copy, modify, distribute and sell this software and
 its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and that
 both that copyright notice and this permission notice appear in
 supporting documentation.  Hewlett-Packard Company makes no
 representations about the suitability of this software for any
 purpose.  It is provided "as is" without express or implied warranty.

 Programmer: Geroncio Galicia
 Date of creation: 7/11/97

*******************************************************************/


#include "AssociationList.h"
#include <iostream.h>

#ifdef __GNUG__
#pragma implementation
#endif


AssociationList::AssociationList(AssociatedObj& owner) : dimen(0),
    nearObj(owner), headNode(0), lastNode(0) {}

AssociationList::~AssociationList() { dissociate(); }

void AssociationList::associate(AssociatedObj& farObj) {
  // Create associate in far list and link it.
  farObj.associates.associate(*this);
}

void AssociationList::associate(AssociationList& farList) {
  ListAssociation& newAssoc = makeNew(); // Put new associate in list
					 // here.
  // FIXME: get rid of these lines and iostream above.
  cout << "new guy is " << &newAssoc << " made by this " << this << endl;
  cout << &newAssoc << "is linking to list" << &farList << endl;
  newAssoc.associate(farList);       // Create far and link both.
}

void AssociationList::associate(Association& farAssociate) {
  ListAssociation& newAssoc = makeNew(); // Put new associate in list
					 // here.
  // FIXME: get rid of these lines and iostream above.
  cout << "new guy is " << &newAssoc << " made by this " << this << endl;
  cout << &newAssoc << " is linking to association " << &farAssociate << endl;
  newAssoc.associate(farAssociate);  // Link both associates.
}

void AssociationList::dissociate() {

  if(empty()) return; // List is already empty.

  ListAssociation *deadHead = headNode; // The head Association.

  // As long as there's a next element.
  while(deadHead->next) {
    headNode = deadHead->next; // Move head-of-list pointer by one.
    deadHead->dissociate();    // Delete old head and all its partner.
    deadHead = headNode;
  }
  
  // Delete the last Association.
  deadHead->dissociate();
  
  // Mark the list empty.
  headNode = 0;
  lastNode = 0;
  dimen = 0;
}

ListAssociation& AssociationList::makeNew() {
    // Set list and AssociatedObj as owners.
    ListAssociation& member = *(new ListAssociation(nearObj,*this));
    return member;
}

void AssociationList::put(ListAssociation& member) {
  if(dimen > 0) {         // List isn't empty.
    member.next = headNode;
    headNode->previous = &member;
    headNode = &member;
  } else {                // List is empty.
    lastNode = headNode = &member;
  }
  dimen++;
  // FIXME: get rid of these lines and iostream.h above.
  cout << "in this(" << this << ") list...\n";
  cout << "headNode = " << headNode << endl;
  cout << "lastNode = " << lastNode << endl;
  cout << "dimen = " << dimen << endl;
}

// AssociatedObjIter methods

AssociatedObjIter::AssociatedObjIter(const AssociationList& l) : list(&l) 
{ 
  // FIXME: remove cout line below and iostream above
  cout << " iterating list " << list << endl;
reset(); }

void AssociatedObjIter::reset() { 
  startAtHead = TRUE; 
  ref = 0; 
}
