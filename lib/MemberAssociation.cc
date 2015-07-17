static const char file_id[] = "MemberAssociation.cc";
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

#include "MemberAssociation.h"

MemberAssociation::MemberAssociation(AssociatedObj& localObj) : 
    Association(localObj) {}

