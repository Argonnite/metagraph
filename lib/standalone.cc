#include <iostream.h>
#include <stl.h>

template class multimap<string,int>;

main() {
    multimap<string,int> phone_book;

    phone_book.insert(pair<string,int>,("Stroustrup",5551912);


    typedef multimap<string,int>::const_iterator I;
    pair<I,I>b = phone_book.equal_range("Stroustrup");
    for(I i = b.first; i != b.last; i++) cout << *i.second << '\n';


    //    VanillaNode aObj;
    //    VanillaNode bObj;

    // member_association-to-list
    //    aObj.neighbors.associate(bObj.neighbors);
    //    bObj.neighbors.associate(aObj.neighbors); // ERROR: Redundant.
    //    aObj.neighbors.associate(aObj.neighbors); // ERROR: Self-linking.

    // member_association-to-member_association
    //    b.associate(c); //FAQ 11.6 violation: dying before scope's end
    //    d.associate(d); // THIS SHOULD RETURN AN ERROR.
    //    a.associate(aList);
    //    a.associate(bList); // ERROR: Cannot relink a.

    //*

    // list-to-obj

    // list-to-list

    // list-to-association

    //*

    // obj-to-obj

    // obj-to-list

    // obj-to-association

    //*

    // List dissociation

    // Association dissociation
    

}

