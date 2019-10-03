template <typename V, typename S = V::value_type>
concept bool Vector_space = requires(V v, V w, S a) {
    { -v } -> V;
    { v + w } -> V;
    { a * v } -> V;
  };


template <typename V, typename S>
void verify_Vector_space(V u, V v, V w, S a, S b) {
  using __requires = decltype(Vector_space<V, S>());

  assert(u + (v + w) == (u + v) + w);
  assert(v + w == w + v);
  assert(v + V(0) == v);
  assert(a * (v + w) == a * v + a * w);
  assert((a + b) * v == a * v + b * v);
  assert(a * (b * v) == (a * b) * v);
  assert(S(1) * v == v);
}

template <typename P, Vector V>
concept bool Affine_space = requires(P a, P b, V v) { 
    { a + v } -> P;
    { b - a } -> V;
  };

template <typename P, Vector V> void verify_Affine_space(P a, V u, V v) {
  assert(a + V(0) == a);
  assert((a + u) + v == a + (u + v));
}
