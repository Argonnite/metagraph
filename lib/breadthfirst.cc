#include "VanillaNode.h"
#include <iostream.h>
#include <stl.h>

template class list<VanillaNode*>;

main() {

  VanillaNode R, S, T, U, V, W, X, Y;
  list<VanillaNode*> Q; // Q is a list of pointers to VanillaNodes
  VanillaNode *u, *v; // Temporary variables for breadthfirst-search.

  // Initialize adjacency lists.
  S.adjacentTo(W);
  S.adjacentTo(R);
  R.adjacentTo(S); // this is redundant but doesn't affect algorithm
  R.adjacentTo(V);
  W.adjacentTo(X);
  W.adjacentTo(T);
  T.adjacentTo(U);
  T.adjacentTo(X);
  Y.adjacentTo(U);
  Y.adjacentTo(X);
  
  // Steps 5-8.
  S.makeGray();
  S.d = 0;
  S.pi = NULL;
  Q.push_back(&S);

  // Steps 9 and 10
  while(Q.size()) {
  u = Q.front();

  // Iterate through u's neighbors.
  VanillaNodeIter nextVN(u->neighbors);

  // Steps 11-16
  while ( (v=nextVN++) != NULL ) { 
    if(v->isWhite()) {
      v->makeGray();
      v->d = u->d + 1;
      v->pi = u;
      Q.push_back(v); // ENQUEUE
    }
  }
  
  // Steps 17 and 18
  Q.pop_front(); // DEQUEUE
  u->makeBlack();
  }


  // checking the values of d
  cout << "R.d = " << R.d << endl;
  cout << "S.d = " << S.d << endl;
  cout << "T.d = " << T.d << endl;
  cout << "U.d = " << U.d << endl;
  cout << "V.d = " << V.d << endl;
  cout << "W.d = " << W.d << endl;
  cout << "X.d = " << X.d << endl;
  cout << "Y.d = " << Y.d << endl;

}
