
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
