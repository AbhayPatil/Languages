/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

auto printv = [](int &n) { cout << n << ", "; };

auto square = [](int &n) { n *= n; };

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  for_each(v.begin(), v.end(), printv);
  cout << endl;

  transform(v.begin(), v.end(), v.begin(), [](int n) { return n * n; });
  for_each(v.begin(), v.end(), printv);
  cout << endl;

  return 0;
}
