#ifndef _AssociatedObj_h
#define _AssociatedObj_h 1
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

#include "AssociationList.h"
#include <iostream.h>

/** Objects that link to each other. 
A {\em link} is an instance of an {\em association} as defined in {\em
Object-Oriented Modeling and Design} by James Rumbaugh, Michael Blaha
{\em et al.}  On links: ``A {\em link} is a physical or conceptual
connection between object instances.  For example, Joe Smith {\em
Works-for} Simplex company.''  On associations: ``An {\em association}
describes a group of links with common structure and common semantics.
For example, a person {\em Works-for} a company.''  Links can have
attributes and an association can even be a class.  Associations are
always bi-directional but for our purposes not each direction should
be equally visible: limited visibility in one direction is desirable
to hide information in a shadow graph from its user hierarchy, such as
an SDF graph.  Therefore, we weaken the notion of links by allowing a
reverse link to {\em not} have an inverse association {\em name}.  So
the above example does not have to mean that Simplex {\em employs} Joe
Smith.  Here, Simplex may choose to keep its employee information
private.  Links are still implemented as bi-directional, for garbage
collection purposes, and we expect numerous many-to-many associations.
Therefore, we implement the process of linking as an atomic operation
where two uni-directional links are created at a time.  The
responsibility of this link-back process belongs to the Association
object that initiates linking; that is, if we instantiate an
Association here it must ensure that the other Association links back
to here.  Instead of storing links in a two-way dictionary, as
suggested by Rumbaugh {\em et al.}, links are stored locally to
minimize hashing during graph traversals.  Classes derived from
AssociatedObj are expected to support multiple lists and non-list
Association members (called MemberAssociations) for more efficient
graph traversal and implementing qualified associations. */
class AssociatedObj {

public:

  // FIXME:  get rid of this method and iostream above.
  void info() {
    cout << "&AssociatedObj = " << this << endl;
    associates.info();
  }

  /// Constructor.
  AssociatedObj() : associates(*this) {}

  /** Copy constructor.
  Create a new AssociatedObj instance and make it link to all of my
  {\tt associates}. */
  AssociatedObj(const AssociatedObj& ao) : associates(*this) {}

  /// Copy assignment operator.
  AssociatedObj& operator=(const AssociatedObj& ao) {
    associates = ao.associates;
  }

  /// Destructor.
  ~AssociatedObj() {}

  /**@name Association methods.  
   *Link to a far data structure/object instance.  In this base class
   *links don't have attributes.  To add attributes to links, derive
   *from this class.  */
  //@{
  /** Link to a {\bf public} AssociationList member of an AssociatedObj.
  Create a ListAssociation in the list here, create a ListAssociation
  in the far list, then link the two.  Note that this AssociatedObj
  base class does not declare a public AssociationList member; such a
  member would exist only in AssociatedObj subclasses.  For example,
  if {\tt A} and {\tt B} are instances of AssociatedObj and {\tt B}
  has a public member {\tt firings} of type AssociationList, then {\tt
  A.associate(B.firings)} would link {\tt A} to {\tt B}'s {\tt
  firings}. */
  void associate(AssociationList& farList);

  /** Link to a {\bf public} Association member of an AssociatedObj.
  In particular, such Association member will be a MemberAssociation.
  (Note that this method cannot be explicitly used to link to a
  ListAssociation.  When a ListAssociation is instantiated it is, by
  design, already assigned a link, and a link for any Association
  cannot be redefined without first dissociating the link.  A
  ListAssociation is designed to be destroyed when it dissociates,
  unlike a MemberAssociation which persists.)  Note that this
  AssociatedObj base class does not declare a public MemberAssociation
  member; such a member would exist only in derived classes and would
  {\em not} be part of any list. */
  void associate(Association& farAssociate);

  /** Link a list to here.
  A far list linking here needs the local {\bf private}
  AssociationList's name. */
  friend void AssociationList::associate(AssociatedObj& farObj);
  //@}


private:

  ///
  AssociationList associates;

};

#endif
