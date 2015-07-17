static const char file_id[] = "ListAssociation.cc";
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
 Date of creation: 7/25/97

*******************************************************************/

#ifdef __GNUG__
#pragma implementation
#endif

#include "ListAssociation.h"

ListAssociation::ListAssociation(AssociatedObj& localObj,
				 AssociationList& localList) : 
  next(0), previous(0), nearList(localList), Association(localObj) 
{
	nearList.put(*this); // Insert *this into nearList.
}

void ListAssociation::dissociate() {

  // Update my neighbors' pointers in my owning list.
  if(next)
    next->previous = previous;
  if(previous)
    previous->next = next;
  
  // Update list size.
  nearList.dimen--;
  
  // If I am head-of-list, then update headNode.
  if(previous==NULL)
    nearList.headNode = next;
  
  // If I am end-of-list, then update lastNode.
  if(next==NULL)
    nearList.lastNode = previous;

    Association::dissociate();

}
