#include "AssociationList.h"
#ifndef _MemberAssociation_h
#define _MemberAssociation_h 1
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

/** Associations that can be instantiated by declaration.
This base class is useful for creating {\em kind-of}-Association
objects that exist outside of an AssociationList.  Such objects will
typically be public members of AssociatedObj subclasses and will have
the same lifetime as its owner AssociatedObj. */
class MemberAssociation : public Association {
public:
    /// Public constructor allows instantiation by declaration.
    MemberAssociation(AssociatedObj& localObj);
};

#endif
