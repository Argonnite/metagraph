static const char file_id[] = "VanillaNode.cc";
#ifdef __GNUG__
#pragma implementation
#endif

#include "VanillaNode.h"

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

void VanillaNode::adjacentTo(VanillaNode &node) {
    neighbors.associate(node.neighbors);
}

void VanillaNode::makeWhite() {
    color = 0;
}

void VanillaNode::makeGray() {
    color = 1;
}

void VanillaNode::makeBlack() {
  color = 2;
}

int VanillaNode::isWhite() {
  return color == 0;
}

int VanillaNode::isGray() {
  return color == 1;
}

