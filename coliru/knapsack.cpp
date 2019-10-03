#include <algorithm>
#include <iostream>
#include <vector>


using namespace std;

template <class InputIt, typename T>
InputIt greedy_knapsack(InputIt first, InputIt last, const T &b) {
  using Item = InputIt::value_type;
  T init(0);
  std::sort(first, last,
            [](Item &i1, Item &i2) { return i1._a * i2._p < i2._a * i1._p; });
  InputIt it =
      std::find_if(first, last, [](Item &i) { return (init += i._a) > b; });
  return it;
}

struct item {
  int _a; // weight
  int _p; //
};

int main(int argc, char const *argv[]) {
  std::vector<item> v{{4, 2}, {10, 3}, {20, 4}, {7, 2}};
  auto it1 = begin(v);
  auto it2 = greedy_knapack(begin(v), end(v), 15);
  for (; it1 != it2; ++it1) {
    cout << '(' << it1->_a << ", " << it1->_p << ')';
  }
  return 0;
}