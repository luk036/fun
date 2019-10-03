#include <utility>
#include <tuple>

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
    return std::tie(p._x, p._y) < std::tie(q._x, q._y);
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
ostream& operator<<(ostream& os, const Segment<T>& s) { 
    os << '[' << s._h << ", " << s._t << ']'; return os; 
}


#include <algorithm> // std::min, std::max

#include <set>
#include <list>
#include <queue>
#include <map>

template <typename T, class Compare>
class segment_sweeper
{
private:
    struct Share_Info; // forward declare
    
    using K = const Segment<T>*;
    using ShVec = std::vector<Share_Info>;
    using ShVec_Itr = typename ShVec::iterator;
    using Event_Info = std::tuple<T, bool, ShVec_Itr>;
    using EvPQ = std::priority_queue<Event_Info>;
    //using EvPQ_Itr = typename EvPQ::iterator;
    using EvPQ_Itr = int*;
    using Map = std::map<K, ShVec_Itr, Compare>;
    using Map_Itr = typename Map::iterator;
    
    // local class
    struct Share_Info
    {
        K           _s;
        Map_Itr     _mIt; 
        EvPQ_Itr    _pIt; // current not used
    };

    EvPQ _event_pq;    
    ShVec _shares;
    Map _S;
    
public:
    // Constructor
    template <class Container, class F1, class F2>
    segment_sweeper(Container& C, Compare cmp, F1 f1, F2 f2) : _S(cmp) {
        //_event_pq.reserve(2*C.size());
        _shares.reserve(C.size());
        for (const auto& s : C) {
            //_shares.emplace_back(Share_Info{&s, _S.end(), _event_pq.end()}); 
            _shares.emplace_back(Share_Info{&s, _S.end(), nullptr}); 
            _event_pq.emplace(std::make_tuple(f1(&s), true, _shares.end()-1)); 
            _event_pq.emplace(std::make_tuple(f2(&s), false, _shares.end()-1)); 
        }
    }

    auto scan() {
        std::list<std::pair<K, K>> L;

        while (!_event_pq.empty()) {
            auto event = _event_pq.top();
            auto is_tail = std::get<1>(event);
            auto shIt = std::get<2>(event);
            _event_pq.pop();    
            if (is_tail) {
                if (shIt->_mIt != _S.end())
                    _S.erase(shIt->_mIt);
                continue;
            } 
            // is_head
            auto mIt = _S.find(shIt->_s);
            if (mIt != _S.end()) {
                L.emplace_back(std::make_pair(mIt->first, shIt->_s));
                mIt->second->_mIt = _S.end();
                _S.erase(mIt);
                continue;
            }

            auto pair = _S.emplace(std::make_pair(shIt->_s, shIt));
            mIt = pair.first;
            shIt->_mIt = mIt;
        }
        return L;
    }    
};


/*
\begin{tikzpicture}
\draw (-3,4) -- (-2,2);
\draw (-6,7) -- (-4,6);
\draw (-7,4) -- (-6,3);
\draw (-1,8) -- (-2,6);
\draw (-9,8) -- (-8,6);
\draw (-5,1) -- (-7,1);
\draw (-6,11) -- (-4,9);
\draw (-9,6) -- (-7,7);
\draw (-9,4) -- (-8,2);
\draw (-11,9) -- (-11,6);
\draw (-11,4) -- (-11,2);
\draw (-6,6) -- (-5,3);
\draw (-5,8) -- (-10,9);
\draw (-10,5) -- (-7,5);
\draw (-4,5) -- (-2,5);
\draw (-8,3) -- (-5,4);
\end{tikzpicture}
*/
#include <iostream>
#include <vector>

int main()
{
    std::vector<Segment<int>> S = { 
        {{-3,4}, {-2,2}}, {{-6,7}, {-4,6}}, 
        {{-7,4}, {-6,3}}, {{-1,8}, {-2,6}}, 
        {{-9,8}, {-8,6}}, {{-5,1}, {-7,1}}, 
        {{-6,11}, {-4,9}}, {{-9,6}, {-7,7}}, 
        {{-9,4}, {-8,2}}, {{-11,9}, {-11,6}}, 
        {{-11,4}, {-11,2}}, {{-6,6}, {-5,3}}, 
        {{-5,8}, {-10,9}}, {{-10,5}, {-7,5}}, 
        {{-4,5}, {-2,5}}, {{-8,3}, {-5,4}} 
    };

    auto leftof = [](auto& s1, auto& s2)-> bool { 
        auto t1{s1->_t}, t2{s2->_t}, h1{s1->_h}, h2{s2->_h};    
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
    };

    auto ftail = [](auto s) -> int { return s->_t._x; };
    auto fhead = [](auto s) -> int { return s->_h._x; };

    segment_sweeper<int, decltype(leftof)> sweeper(S, leftof, ftail, fhead);
    auto L = sweeper.scan();
    if (L.empty()) std::cout << "No intersect\n";
    else
        for (auto& p : L)
            std::cout << *p.first << " and " << *p.second << '\n';
}
