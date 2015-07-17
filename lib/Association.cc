static const char file_id[] = "Association.cc";
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

#ifdef __GNUG__
#pragma implementation
#endif

#include "Association.h"
#include "Error.h"
#include <iostream.h>

Association::Association(AssociatedObj& localObj) : 
  far(0), nearObj(localObj), isPaired(FALSE), isDissociating(FALSE){}

Association::~Association() { if(!isDissociating) dissociate(); }

AssociatedObj& Association::nearOwner() { return nearObj; }

AssociatedObj* Association::farOwnerPtr() { 
    return far ? &far->nearObj : (AssociatedObj*)NULL ; 
}

Association& Association::associate(AssociationList& farList) {
    if(isPaired && far) { // "Already married."
        Error::error("Association object is already associated.\n");
    } 
    else // "Single and searching." 
	farList.associate(*this);  
    return *far; // Return NULL if unsuccessful.
}

Association& Association::associate(Association& farAssociation) {
    if(isPaired && far) { // "Already married."
        Error::error("Association object is already associated.\n");
    } 
    if(!(isPaired || far)) { // "Single and searching."
    	isPaired = TRUE;
    	farAssociation.associate(*this); // Make far link to *this.
    	far = &farAssociation;           // Set *this to point to far.
	// FIXME: remove this line and iostream above. for DEBUGGING ONLY
	cout << this << " points to " << far << endl;
	return farAssociation;
    }
    return *far; // If cannot reseat association return the current one.
}

void Association::dissociate() {
    if(!isDissociating) {
	isDissociating = TRUE;
	// Dissociate far.  
	if(far) {
	    far->far = NULL; // Prevent *far from re-dissociating *this.
	    far->dissociate();
	}
	// Commit suicide.
	delete this;
    }
}
