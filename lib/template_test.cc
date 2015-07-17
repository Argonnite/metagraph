#include <iostream.h>
#include <stl.h>

template class vector<int>;

main() {

    vector<int> list1;

    for(int i = 0; i < 10; ++i) {
        list1.push_back(rand());
    }
    sort(list1.begin(),list1.end());
    for(i = 0; i < 10; ++i)
	cout << list1[i] << "\n";
    return 0;

}

