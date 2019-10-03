#include <utility>

template <typename T>
struct Vec2 { T _a, _b; };

template<typename T>
auto operator*(const Vec2<T>& v, const Vec2<T>& w) {
    return v._a * w._b - w._a * v._b;
}

template <typename T>
struct Point { T _x, _y; };

template <class ostream, typename T>
ostream& operator<<(ostream& os, const Point<T>& p) { 
    os << '(' << p._x << ", " << p._y << ')'; return os; 
}

template<typename T>
bool operator<(const Point<T>& p, const Point<T>& q) {
    return std::make_pair(p._x, p._y) < std::make_pair(q._x, q._y);
}

template<typename T>
auto operator-(const Point<T>& p, const Point<T>& q) {
    return Vec2<T>{p._x - q._x, p._y - q._y};
}

template<typename T>
auto p_area(const Point<T>& p, const Point<T>& q, const Point<T>& r) {
    return (p - r) * (q - r);
}

template <typename T>
struct Segment { 
    Point<T> _t, _h;
    
    Segment(const Point<T>& a, const Point<T>& b) : _t(a), _h(b) {
        if (_h < _t) std::swap(_t,_h);
    }
};

template <class ostream, typename T>
ostream& operator<<(ostream& os, Segment<T> s) { 
    os << '[' << s._h << ", " << s._t << ']'; return os; 
}


#include <algorithm> // std::min, std::max

template <typename T>
bool leftof(const Segment<T>& s1, const Segment<T>& s2) {
    auto t1{s1._t}, t2{s2._t}, h1{s1._h}, h2{s2._h};
    
    if (std::max(t1._y, h1._y) <= std::min(t2._y, h2._y)) return true;
    
    if (t1._x < t2._x) {
        if (p_area(t2, h1, t1) >= 0) return false;
    } else if (t1._x > t2._x) {
        if (p_area(t1, h2, t2) <= 0) return false;
    } else // t1._x == t2._x
        if (t1._y > t2._y) return false;

    if (h1._x < h2._x) {
        if (p_area(h1, h2, t2) <= 0) return false;
    } else if (h1._x > h2._x) {
        if (p_area(h2, h1, t1) >= 0) return false;
    } else // h1._x == h2._x
        if (h1._y > h2._y) return false;

    return true;
}

#include <set>
#include <list>

template <class Container, class Compare>
auto intersect(const Container& C, Compare cmp)
{
    using K = typename Container::value_type;
    std::set<K, Compare> S(cmp);
    std::list<std::pair<K,K>> L;

    for (auto& s : C) {
        auto it = S.find(s);
        if (it != S.end()) {
            L.emplace_back(std::make_pair(s, *it));
            S.erase(it);
        }
        else S.insert(it, s);
    }
    return L;
}

#include <iostream>
#include <vector>

int main()
{
    std::vector<Segment<int>> S = { 
        {{-14,6}, {-10,3}}, {{-10,6}, {-6,3}},
        {{-4,2}, {-6,4}}, {{-9,5}, {-1,3}},
        {{-2,4}, {-4,3}}, {{-3,5}, {2,2}},
        {{3,5}, {1,3}}, {{-8,4}, {-10,2}},
    };

    auto leftof = [](auto const& s1, auto const& s2)-> bool { 
        auto const& t1{s1._t}, t2{s2._t}, h1{s1._h}, h2{s2._h};
        if (std::max(t1._y, h1._y) <= std::min(t2._y, h2._y)) return true;    
        return (p_area(h1, t2, h2) < 0 && p_area(t1, t2, h2) < 0)
            || (p_area(t1, h1, h2) > 0 && p_area(t1, h1, t2) > 0);
    }; /* important! not strict weak ordering in general! */

    auto L = intersect(S, leftof);
    if (L.empty()) std::cout << "No intersect\n";
    else
        for (auto& p : L)
            std::cout << p.first << " and " << p.second << '\n';
}
