/* Copyright (c) Facebook, Inc. and its affiliates. */

#define /**/ OVERRIDE_MEMBER_FUNC(fn)                                                                                 \
  template <class Tp1, class Tp2, int N, int M, int Options, int P, int Q>                                            \
  struct member_##fn<Array<Tp1, N, M, Options, P, Q>, Array<Tp2, N, M, Options, P, Q> > {                             \
    template <int size> struct Cost { enum { value = N * M * member_##fn<Tp1, Tp2>::template Cost<size>::value }; };  \
                                                                                                                      \
    template <typename XprType> EIGEN_STRONG_INLINE_DEVICE_FUNC                                                       \
    Array<Tp1, N, M, Options, P, Q> operator()(const XprType& x) const                                                \
      { EIGEN_STATIC_ASSERT(N != Dynamic && M != Dynamic, THIS_TYPE_IS_NOT_SUPPORTED);                                \
        return x.cellwise().fn(); }                                                                                   \
                                                                                                                      \
    typedef Array<Tp1, N, M, Options, P, Q> result_type;                                                              \
    EIGEN_EMPTY_STRUCT_CTOR(member_##fn)                                                                              \
    struct BinaryOp { /* dummy */ };                                                                                  \
    enum { Vectorizable = 0 };                                                                                        \
                                                                                                                      \
    BinaryOp binaryFunc() const                                                                                       \
      { return BinaryOp(); }                                                                                          \
  };

OVERRIDE_MEMBER_FUNC(stableNorm)
OVERRIDE_MEMBER_FUNC(hypotNorm)
OVERRIDE_MEMBER_FUNC(blueNorm)
OVERRIDE_MEMBER_FUNC(minCoeff)
OVERRIDE_MEMBER_FUNC(maxCoeff)
OVERRIDE_MEMBER_FUNC(count)
OVERRIDE_MEMBER_FUNC(prod)
OVERRIDE_MEMBER_FUNC(all)
OVERRIDE_MEMBER_FUNC(any)
OVERRIDE_MEMBER_FUNC(sum)

// TODO(ygitman): lpNorm

#undef /***/ OVERRIDE_MEMBER_FUNC

template<typename Derived, int N, int M> struct all_unroller_nc {
  enum { RowIdx = (Derived::Flags & RowMajor) ? (N - 1) / M : (N - 1) % M };
  enum { ColIdx = (Derived::Flags & RowMajor) ? (N - 1) % M : (N - 1) / M };

  static EIGEN_STRONG_INLINE_DEVICE_FUNC bool run(const Derived &x)
    { return all_unroller_nc<Derived, N - 1, M>::run(x) && numext::all(x.coeff(RowIdx, ColIdx)); }
};

template<typename Derived, int N, int M> struct any_unroller_nc {
  enum { RowIdx = (Derived::Flags & RowMajor) ? (N - 1) / M : (N - 1) % M };
  enum { ColIdx = (Derived::Flags & RowMajor) ? (N - 1) % M : (N - 1) / M };

  static EIGEN_STRONG_INLINE_DEVICE_FUNC bool run(const Derived &x)
    { return any_unroller_nc<Derived, N - 1, M>::run(x) || numext::any(x.coeff(RowIdx, ColIdx)); }
};

template<typename Derived, int M> struct all_unroller_nc<Derived, Dynamic, M>
  { static EIGEN_STRONG_INLINE_DEVICE_FUNC bool run(const Derived&) { return false; } };

template<typename Derived, int M> struct all_unroller_nc<Derived, 0, M>
  { static EIGEN_STRONG_INLINE_DEVICE_FUNC bool run(const Derived&) { return  true; } };

template<typename Derived, int M> struct any_unroller_nc<Derived, Dynamic, M>
  { static EIGEN_STRONG_INLINE_DEVICE_FUNC bool run(const Derived&) { return false; } };

template<typename Derived, int M> struct any_unroller_nc<Derived, 0, M>
  { static EIGEN_STRONG_INLINE_DEVICE_FUNC bool run(const Derived&) { return false; } };
