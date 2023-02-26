
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Use reference(&) to modify values in place.
// If passed by value, then 'mutable' should be used
// to modify the values in place.

// Auto args
auto square_vec = [](auto &n) { n *= n; };

auto print_vec = [](auto &n) { cout << n << ", "; };

auto square_map_val = [](auto &kv) { kv.second *= kv.second; };

auto print_map = [](auto &kv) {
  cout << "Key: " << kv.first << ", Value: " << kv.second << endl;
};

int main() {

  // Vector
  cout << endl << "Vector" << endl << endl;
  vector<int> vi = {1, 2, 3, 4, 5};
  for_each(vi.begin(), vi.end(), print_vec);
  cout << endl;

  for_each(vi.begin(), vi.end(), square_vec);
  for_each(vi.begin(), vi.end(), print_vec);
  cout << endl;

  int delta = 5;
  auto change_val = [delta](auto &n) { n += delta; };
  for_each(vi.begin(), vi.end(), change_val);
  for_each(vi.begin(), vi.end(), print_vec);
  cout << endl;

  vector<char> vc = {'a', 'b', 'c', 'd', 'e'};
  for_each(vc.begin(), vc.end(), print_vec);
  cout << endl;

  // Map
  cout << endl << "Map" << endl << endl;
  map<char, int> m;
  m['a'] = 10;
  m['b'] = 20;
  m['c'] = 30;
  for_each(m.begin(), m.end(), print_map);
  cout << endl;

  for_each(m.begin(), m.end(), square_map_val);
  for_each(m.begin(), m.end(), print_map);
  cout << endl;

  return 0;
}
