#include <iostream>
#include <vector>
#include "increment_and_sum.h"
using std::vector;
using std::cout;

int main()
{
    vector<int> v{11, 23, 34, 45};
    int total = IncrementAndComputeVectorSum(v);
    cout << "The total is: " << total << "\n";
}
