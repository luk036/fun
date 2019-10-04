#include <set>

template <class Container> bool is_overlap(const Container &U) {
  using I = typename Container::value_type;
  auto cmp = [](const I &i1, const I &i2) -> bool {
    return i1.upper() < i2.lower();
  };
  std::set<I, decltype(cmp)> S(cmp);
  for (auto &&i : U) {
    if (S.find(i) != S.cend())
      return true;
    S.insert(i);
  }
  return false;
}

#include <iostream>
#include <vector>

struct interval {
  int _lower, _upper;

  constexpr int lower() const { return _lower; }
  constexpr int upper() const { return _upper; }
};

int main() {
  std::vector<interval> T = {{3, 5}, {1, 2}, {6, 8}, {4, 17}};
  std::cout << is_overlap(T) << std::endl;
}
