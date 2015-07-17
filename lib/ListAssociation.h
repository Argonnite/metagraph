#include "AssociationList.h"
#ifndef _ListAssociation_h
#define _ListAssociation_h 1
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
 Date of Creation : 7/25/97

********************************************************************/

#include "type.h"
#include "Association.h"

class AssociatedObj;

/** Associations that exist only in lists.
ListAssociations are created from the {\em free store} and exist only
in an AssociationList.  They cannot exist outside of an
AssociationList.  Furthermore, objects of this class exist only for
the purpose of implementing an AssociationList.  Hence, an explicit
object of this class can be instantiated through an AssociationList's
interface only, and even then its existence is not apparent through
the public interface.  ListAssociation objects have arbitrary
lifetimes, unlike MemberAssociations which persist after they are
dissociated.  (MemberAssociations have the same lifetimes as their
scope.)  Subclasses should add attributes and attribute manipulation.
When a ListAssociation is instantiated it is, by design, already
assigned a link, and a link for any Association cannot be redefined
without first dissociating the link.  A ListAssociation is designed to
be destroyed when it dissociates */
class ListAssociation : public Association {
    
private:

  /// The next ListAssociation in the list.
  ListAssociation *next;
  
  /// The previous ListAssociation in the list.
  ListAssociation *previous;
  
  /// Constructor adds an owner list field to base constructor.
  ListAssociation(AssociatedObj& localObj, AssociationList& localList);
  
  /// The local AssociationList owning {\bf *this}, if there is one.
  AssociationList &nearList;
  
  /// Delete self from list and far Association.  Overrides base method.
  /* virtual */ void dissociate();
  
  /** My owner list must have access to my successor/predecessor.  
      Grants the list permission to update a ListAssociation's next and
      previous pointers during a put() and dissociate(). */
  friend class AssociationList;
  
  ///
  friend class AssociatedObjIter;

};

#endif
