/* Copyright (c) Facebook, Inc. and its affiliates. */

#define MAKE_CHANNELWISE_FN(RType, fn, expr1d)      \
  template <typename T,                             \
            int=(wrap_scalar<T>::NumChannels > 1)>  \
  struct channelwise_##fn;                          \
                                                    \
  template <typename T>                             \
  struct channelwise_##fn<T, 1> {                   \
    EIGEN_IMPORT_CHANNELTYPE(T)                     \
    typedef RType result_type;                      \
                                                    \
    EIGEN_STRONG_INLINE_DEVICE_FUNC                 \
    RType operator() (const T& x) const             \
      { return x.fn(); }                            \
  };                                                \
                                                    \
  template <typename T>                             \
  struct channelwise_##fn<T, 0> {                   \
    EIGEN_IMPORT_CHANNELTYPE(T)                     \
    typedef RType result_type;                      \
                                                    \
    EIGEN_STRONG_INLINE_DEVICE_FUNC                 \
    RType operator() (const T& x) const             \
      { return expr1d; }                            \
  };

#define /**/ NORM_RESULT_TYPE \
    typename NumTraits<ChannelType>::Real

template <typename Func, typename Scalar>
struct channelwise_redux_wrapper {
  explicit channelwise_redux_wrapper(const Func& func)
    : func_(func) {}

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  typename result_of<Func(const Scalar&)>::type
  operator ()(const Scalar& arg) const
    { return func_(arg); }

  const Func& func_;
};

// TODO(ygitman): 1D case will prevent vectorization
// TODO(ygitman): Provide functor_traits

MAKE_CHANNELWISE_FN(NORM_RESULT_TYPE, squaredNorm, (x * x))
MAKE_CHANNELWISE_FN(NORM_RESULT_TYPE, stableNorm, (x))
MAKE_CHANNELWISE_FN(NORM_RESULT_TYPE, hypotNorm, (x))
MAKE_CHANNELWISE_FN(NORM_RESULT_TYPE, blueNorm, (x))
MAKE_CHANNELWISE_FN(NORM_RESULT_TYPE, norm, (x))

MAKE_CHANNELWISE_FN(ChannelType, maxCoeff, (x))
MAKE_CHANNELWISE_FN(ChannelType, minCoeff, (x))

MAKE_CHANNELWISE_FN(ChannelType, prod, (x))
MAKE_CHANNELWISE_FN(ChannelType, mean, (x))
MAKE_CHANNELWISE_FN(ChannelType, sum, (x))

MAKE_CHANNELWISE_FN(Index, count, (x != 0))
MAKE_CHANNELWISE_FN(bool, all, (x != 0))
MAKE_CHANNELWISE_FN(bool, any, (x != 0))

#undef /***/ MAKE_CHANNELWISE_FN
#undef /***/ NORM_RESULT_TYPE

} // namespace internal

template <typename Derived>
struct ChannelwiseOp {
#define /**/ CHANNELWISE_FUNCTOR(func)                                \
  internal::channelwise_##func<typename internal::remove_all<Derived>::type::Scalar>

#define /**/ REDUX_UNARY_OP(fn) CwiseUnaryOp<CHANNELWISE_FUNCTOR(fn), const Derived>

#define /**/ MAKE_CHANNELWISE_METHOD(fn)                              \
  EIGEN_STRONG_INLINE_DEVICE_FUNC const REDUX_UNARY_OP(fn) fn() const \
    { return REDUX_UNARY_OP(fn)(ref); }

  typename internal::ultimate_ref_selector<Derived>::type ref;
  ChannelwiseOp(Derived& refexpr) : ref(refexpr) {}

// TODO(ygitman): implement reverseInPlace
// TODO(ygitman): implement normalized
// TODO(ygitman): implement normalize
// TODO(ygitman): implement replicate
// TODO(ygitman): implement reverse
// TODO(ygitman): implement lpNorm
// TODO(ygitman): implement redux

  MAKE_CHANNELWISE_METHOD(squaredNorm)
  MAKE_CHANNELWISE_METHOD(stableNorm)
  MAKE_CHANNELWISE_METHOD(hypotNorm)
  MAKE_CHANNELWISE_METHOD(blueNorm)
  MAKE_CHANNELWISE_METHOD(maxCoeff)
  MAKE_CHANNELWISE_METHOD(minCoeff)
  MAKE_CHANNELWISE_METHOD(count)
  MAKE_CHANNELWISE_METHOD(norm)
  MAKE_CHANNELWISE_METHOD(prod)
  MAKE_CHANNELWISE_METHOD(mean)
  MAKE_CHANNELWISE_METHOD(sum)
  MAKE_CHANNELWISE_METHOD(all)
  MAKE_CHANNELWISE_METHOD(any)

#undef /***/ MAKE_CHANNELWISE_METHOD
#undef /***/ CHANNELWISE_FUNCTOR
#undef /***/ REDUX_UNARY_OP
};

namespace /**/ internal {

#define RTYPE(fn) typename result_of<channelwise_##fn<typename Expr::Scalar, 1>(const typename Expr::Scalar&) >::type

template <typename Expr, typename Func>
struct traits<CwiseUnaryOp<channelwise_redux_wrapper<Func, typename Expr::Scalar>, const Expr> > : traits<Expr> {
  typedef typename result_of<Func(const typename Expr::Scalar&)>::type Scalar;
  enum { Flags = traits<Expr>::Flags & RowMajorBit };
  typedef ArrayXpr XprKind;
};

#define DEFINE_CHANNELWISE_REDUX_TRAITS(fn)                                                             \
  template <typename Expr>                                                                              \
  struct traits<CwiseUnaryOp<channelwise_##fn<typename Expr::Scalar, 1>, const Expr> > : traits<Expr> { \
    enum { Flags = traits<Expr>::Flags & RowMajorBit };                                                 \
    typedef RTYPE(fn) Scalar;                                                                           \
    typedef ArrayXpr XprKind;                                                                           \
  };

DEFINE_CHANNELWISE_REDUX_TRAITS(squaredNorm)
DEFINE_CHANNELWISE_REDUX_TRAITS(stableNorm)
DEFINE_CHANNELWISE_REDUX_TRAITS(hypotNorm)
DEFINE_CHANNELWISE_REDUX_TRAITS(blueNorm)
DEFINE_CHANNELWISE_REDUX_TRAITS(norm)

DEFINE_CHANNELWISE_REDUX_TRAITS(maxCoeff)
DEFINE_CHANNELWISE_REDUX_TRAITS(minCoeff)

DEFINE_CHANNELWISE_REDUX_TRAITS(prod)
DEFINE_CHANNELWISE_REDUX_TRAITS(mean)
DEFINE_CHANNELWISE_REDUX_TRAITS(sum)

DEFINE_CHANNELWISE_REDUX_TRAITS(count)
DEFINE_CHANNELWISE_REDUX_TRAITS(all)
DEFINE_CHANNELWISE_REDUX_TRAITS(any)

#undef DEFINE_CHANNELWISE_REDUX_TRAITS
#undef RTYPE
