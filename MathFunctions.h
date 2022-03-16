/* Copyright (c) Facebook, Inc. and its affiliates. */

namespace ops {

template <typename T1, typename T2, typename T3, bool=std::is_base_of<DenseBase<T1>, T1>::value> struct SelectImpl;
template <int N, typename T, int=(N == 1) ? -1 : std::is_base_of<DenseBase<T>, T>::value> struct ReplicateImpl;
template <int cnd, typename T, bool=cnd && std::is_base_of<DenseBase<T>, T>::value> struct EvaluateImpl;
template <typename T1, typename T2, bool=std::is_base_of<DenseBase<T1>, T1>::value> struct MinImpl;
template <typename T1, typename T2, bool=std::is_base_of<DenseBase<T1>, T1>::value> struct MaxImpl;
template <typename T1, typename T2, bool=std::is_base_of<DenseBase<T1>, T1>::value> struct PowImpl;
template <typename Tp, typename T, bool=std::is_base_of<DenseBase<T>, T>::value> struct CastImpl;

#define MAKE_REDUX_OP(Fn, fn, fallback)                                                      \
template <typename T, bool=std::is_base_of<DenseBase<T>, T>::value> struct Redux##Fn##Impl;  \
                                                                                             \
template <typename T> EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC                                  \
auto redux_##fn(const T& x) { return Redux##Fn##Impl<T>::run(x); }                           \
                                                                                             \
template <typename Tp> struct Redux##Fn##Impl<Tp, 0> {                                       \
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC                                                      \
  static auto run(const Tp& x) { return (fallback); }                                        \
};                                                                                           \
                                                                                             \
template <typename Tp> struct Redux##Fn##Impl<Tp, 1> {                                       \
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC                                                      \
  static auto run(const Tp& x) { return x.fn(); }                                            \
};

MAKE_REDUX_OP(SquaredNorm, squaredNorm, decltype(x)(x * x))
MAKE_REDUX_OP(Count, count, Index(x != 0))
MAKE_REDUX_OP(StableNorm, stableNorm, x)
MAKE_REDUX_OP(HypotNorm, hypotNorm, x)
MAKE_REDUX_OP(All, all, bool(x != 0))
MAKE_REDUX_OP(Any, any, bool(x != 0))
MAKE_REDUX_OP(BlueNorm, blueNorm, x)
MAKE_REDUX_OP(MaxCoeff, maxCoeff, x)
MAKE_REDUX_OP(MinCoeff, minCoeff, x)
MAKE_REDUX_OP(Norm, norm, x)
MAKE_REDUX_OP(Prod, prod, x)
MAKE_REDUX_OP(Mean, mean, x)
MAKE_REDUX_OP(Sum, sum, x)

#undef MAKE_REDUX_OP

template <typename T1, typename T2, typename T3>
EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC auto select(const T1& x, const T2& y, const T3& z)
  { return SelectImpl<T1, T2, T3>::run(x, y, z); }

template <typename T1, typename T2>
EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC auto pow(const T1& x, const T2& y)
  { return PowImpl<T1, T2>::run(x, y); }

template <typename T1, typename T2>
EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC auto min(const T1& x, const T2& y)
  { return MinImpl<T1, T2>::run(x, y); }

template <typename T1, typename T2>
EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC auto max(const T1& x, const T2& y)
  { return MaxImpl<T1, T2>::run(x, y); }

template <int N, typename T>
EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC auto replicate(const T& x)
  { return ReplicateImpl<N, T>::run(x); }

template <int cnd=1, typename Tp>
EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC auto evaluate(const Tp& x)
  { return EvaluateImpl<cnd, Tp>::run(x); }

template <typename Tp, typename T>
EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC auto cast(const T& x)
  { return CastImpl<Tp, T>::run(x); }

template <typename T1, typename T2, typename T3>
struct SelectImpl<T1, T2, T3, 1> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const T1& x, const T2& y, const T3& z) { return x.select(y, z); }
};

template <typename T1, typename T2, typename T3>
struct SelectImpl<T1, T2, T3, 0> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const T1& x, const T2& y, const T3& z) { return x ? y : z; }
};

template <typename T1, typename T2>
struct PowImpl<T1, T2, 0> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const T1& x, const T2& y) { return numext::pow(x, y); }
};

template <typename T1, typename T2>
struct MinImpl<T1, T2, 0> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const T1& x, const T2& y) { return x < y ? x : y; }
};

template <typename T1, typename T2>
struct MaxImpl<T1, T2, 0> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const T1& x, const T2& y) { return x > y ? x : y; }
};

template <int N, typename T>
struct ReplicateImpl<N, T, 1> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC static auto run(const T& x)
    { return x.template replicate<N, 1>(); }
};

template <int N, typename T>
struct ReplicateImpl<N, T, 0> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC static auto run(const T& x)
    { return Array<T, N, 1>::Constant(x); }
};

template <int N, typename T>
struct ReplicateImpl<N, T, -1> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC static auto run(const T& x)
    { return x; }
};

template <typename T1, typename T2>
struct PowImpl<T1, T2, 1> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const T1& x, const T2& y) { return x.pow(y); }
};

template <typename T1, typename T2>
struct MinImpl<T1, T2, 1> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const T1& x, const T2& y) { return x.min(y); }
};

template <typename T1, typename T2>
struct MaxImpl<T1, T2, 1> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const T1& x, const T2& y) { return x.max(y); }
};

template <typename Tp, typename T>
struct CastImpl<Tp, T, 1> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const T& x) { return x.template cast<Tp>(); }
};

template <typename Tp, typename T>
struct CastImpl<Tp, T, 0> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const T& x) { return static_cast<Tp>(x); }
};

template <int cnd, typename Tp>
struct EvaluateImpl<cnd, Tp, 1> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const Tp& x) { return x.eval(); }
};

template <int cnd, typename Tp>
struct EvaluateImpl<cnd, Tp, 0> {
  EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
  static auto run(const Tp& x) { return x; }
};
}
