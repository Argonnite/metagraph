#include "AssociationList.h"
#ifndef _Association_h
#define _Association_h 1
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

#include <iostream.h>
#include "type.h"

class AssociatedObj;
class AssociationList;

/** A base class for objects that link to each other only once.
An Association object links to at most one other object of its type.
It is typically part of a AssociationList or is a member of a class
derived from AssociatedObj.  An Association object can be linked to
another only once.  Attempting to reseat an existing link without
first dissociating will return a message indicating failure.  This
class behaves differently from an AssociatedObj in that it support
only one-to-one links and destruction or dissociating of an instance
will affect its partner instance. */
class Association {

public:

    /**@name Owner identification methods */
    //@{
    /// Return my owner.
    AssociatedObj& nearOwner();

    /** Return the owner of my partner Association.
    Returns NULL if there is no partner Association. */
    AssociatedObj* farOwnerPtr();
    //@}

    /**@name Link-to-member methods 
    *Linking instantiates a bi-directional association.  Linking to a
    *far object is always accompanied by an implicit link back from
    *the linked-to object. */
    //@{

    /** Link to a {\bf public} AssociationList member of an AssociatedObj.
    Creates and returns the Association in the farList.  Such a member
    will be of subtype ListAssociation.  Useful if a characteristic,
    qualification, or attribute is attached to a particular list. */
    Association& associate(AssociationList& farList);

    /** Link to a {\bf public} Association member of an AssociatedObj.
    Such a member will be of subtype MemberAssociation.  Useful if a
    characteristic, qualification, or attribute is attached to a
    particular existing link. */
    Association& associate(Association& farAssociation);
    //@}


protected:

    /// The Association to which I am linked (there can be only one).
    Association *far;

    // The local AssociatedObj owning {\bf *this}.
    AssociatedObj &nearObj;

    /** Constructor creates and inserts myself into a list.
    Associations must be owned by an object and a list.  Instantiating
    {\bf *this} automatically updates the state of the owner list.
    Note that this constructor is not public to prevent instantiation
    by declaration.  If instantiation by declaration is possible, then
    it is also possible that the Destructor will be called twice: the
    far Association is destroyed, thus destroying {\bf *this}, then
    the end of the scope in which {\bf *this} resides is reached.
    Instantiation by declaration should be possible only in derived
    classes that avoid this scenario. */
    Association(AssociatedObj& localObj);

    /** Destructor deletes myself and partner.
    Invokes dissociate(). */
    virtual ~Association();
    
    /** Delete my Associate and me.
    My partner Associate is destroyed (if it is part of an
    AssociationList) or reset (if it is an AssociatedObj subclass
    public member).  (The latter cannot happen with the base class
    AssociatedObj but rather in classes derived from AssociatedObj
    this method must be overridden to NULL its Association member's
    pointer instead of deleting that member.)  In short, if a derived
    class is instantiated by declaration (see comments for the
    Constructor above) then this method must be overridden. */
    virtual void dissociate();

private:

    /// Used to avoid infinite recursion during associating.
    int isPaired;

    /// Used to avoid calling destructor twice during "delete this".
    int isDissociating;

};

#endif
