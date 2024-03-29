#ifndef COMMON_CONCEPTS_HPP
#define COMMON_CONCEPTS_HPP 1

#include <utility>

namespace fun {

template <typename I> concept bool Input_iter = requires(I iter) { ++iter; };

template <typename T> using Element_type = decltype(back(std::declval<T>()));

template <typename T> using Iterator_type = decltype(begin(std::declval<T>()));

template <typename T> concept bool Sequence() {
  return requires(T t, Element_type<T> x) {
    { t.size() } -> int;
    { t.empty() } -> bool;
    { t.back() } -> Element_type<T>;
    { t.push_back(x) }
  };
}

template <typename T> concept bool Range = requires(T range) {
  typename Iterator_type<T>;
  { std::begin(range) } -> Iterator_type<T>;
  { std::end(range) } -> Iterator_type<T>;
};

template <typename P, typename... Args> concept bool Predicate() {
  return requires(P pred, Args... args) {
    { pred(args...) } -> bool;
  };
}

template <typename T>
concept bool Equality_comparable = requires(T a, T b){{a == b}->bool};

Equality_comparable { T }
bool operator!=(const T &a, const T &b) { return !(a == b); }

} // namespace

#endif