#include <vector>
#include <ext/pool_allocator.h>
#include <algorithm>
#include <iostream>

#include "memory+"

using namespace std;

class descend 
{
public:
    int operator()(int i, int j)
    {
        return i > j;
    }
};
int main()
{
    typedef vector<int, mycxx::pool_alloc<int> > vector_type;
    vector_type v;

    for (int i = 0; i < 100000; i++) {
        v.push_back(i);
    }

    sort(v.begin(), v.end(), descend());

    for (unsigned int i; i < v.size(); i += 10000) {
        cout << v[i] << endl;
    }
    
    return 0;
}
