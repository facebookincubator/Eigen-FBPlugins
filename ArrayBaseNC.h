/* Copyright (c) Facebook, Inc. and its affiliates. */

#define /**/ HAS_EXPR2D(ExprType) internal::is_void<typename Expr2d<ExprType>::type>::value

#ifndef /**/ EIGEN_DISABLE_EXPRESSION_OPTIMISAZTIONS

#define /**/ SWITCH_BASE                                               \
  internal::conditional<HAS_EXPR2D(Derived), ArrayBaseNCImpl<Derived>, \
                                             ArrayBaseNCImpl2d<Derived> >::type

#else /**/// EIGEN_DISABLE_EXPRESSION_OPTIMISAZTIONS

#define /**/ SWITCH_BASE \
  internal::enable_if<true, ArrayBaseNCImpl<Derived> >::type

#endif /**///EIGEN_DISABLE_EXPRESSION_OPTIMISAZTIONS

#if /***/ !defined(EIGEN_DISABLE_MULTICHANNEL_ARRAYS)

template<typename Tp, int N, int M, int Opts, int P, int Q, int U, int V>
struct traits<Array<Array<Tp, U, V, 0, U, V>, N, M, Opts, P, Q> >
  : traits<Matrix<Array<Tp, U, V, 0, U, V>, N, M, Opts, P, Q> >
  { typedef ArrayXprNC XprKind; };

#endif // !defined(EIGEN_DISABLE_MULTICHANNEL_ARRAYS)

}  // namespace internal

template <typename Derived>
struct ArrayBaseNCImpl2d : ArrayBase<Derived> {
  template<typename T>
  explicit ArrayBaseNCImpl2d(const ArrayBaseNC<T>& arg)
    : ArrayBase<Derived>(arg) {}

  typename Expr2d<const Derived>::type as2d() const
    { return Expr2d<const Derived>::make(derived()); }

  typename Expr2d<Derived>::type as2d()
    { return Expr2d<Derived>::make(derived()); }

  typedef ArrayBase<Derived> Base;
  typedef typename Base::PlainObject PlainObject;

 protected:
  EIGEN_DEFAULT_EMPTY_CONSTRUCTOR_AND_DESTRUCTOR(ArrayBaseNCImpl2d)
  EIGEN_DEFAULT_COPY_CONSTRUCTOR(ArrayBaseNCImpl2d)

 public:
  ArrayBaseNCImpl2d(Index x, Index y) : Base(x, y) {}
  explicit ArrayBaseNCImpl2d(Index x) : Base(x) {}
  EIGEN_DEFINE_PUBLIC_INTERFACE(Derived)
  enum { IsRowMajor = Flags&RowMajor };

  EIGEN_IMPORT_CHANNELTYPE(Scalar)
  EIGEN_IMPORT_NUMCHANNELS(Scalar)

# include "./arraybasenc/2d/Reductions.h"
# include "./arraybasenc/2d/Assign.h"

  using Base::operator +=;
  using Base::operator -=;
  using Base::operator *=;
  using Base::operator /=;
  using Base::operator  =;
};

template <typename Derived>
struct ArrayBaseNCImpl : ArrayBase<Derived> {
  template<typename T>
  explicit ArrayBaseNCImpl(const ArrayBaseNC<T>& arg)
    : ArrayBase<Derived>(arg) {}

  typedef ArrayBase<Derived> Base;
  typedef typename Base::PlainObject PlainObject;

 protected:
  EIGEN_DEFAULT_EMPTY_CONSTRUCTOR_AND_DESTRUCTOR(ArrayBaseNCImpl)
  EIGEN_DEFAULT_COPY_CONSTRUCTOR(ArrayBaseNCImpl)

 public:
  ArrayBaseNCImpl(Index x, Index y) : Base(x, y) {}
  explicit ArrayBaseNCImpl(Index x) : Base(x) {}
  EIGEN_DEFINE_PUBLIC_INTERFACE(Derived)
  enum { IsRowMajor = Flags&RowMajor };

  EIGEN_IMPORT_CHANNELTYPE(Scalar)
  EIGEN_IMPORT_NUMCHANNELS(Scalar)

# include "./arraybasenc/Reductions.h"

  using Base::operator +=;
  using Base::operator -=;
  using Base::operator *=;
  using Base::operator /=;
  using Base::operator  =;
};

template <typename Derived>
struct ArrayBaseNC : SWITCH_BASE {
  template<typename T>
  explicit ArrayBaseNC(const ArrayBaseNC<T>& arg)
    : SWITCH_BASE(arg) {}

  typedef typename SWITCH_BASE Base;
  typedef typename Base::PlainObject PlainObject;

 protected:
  EIGEN_DEFAULT_EMPTY_CONSTRUCTOR_AND_DESTRUCTOR(ArrayBaseNC)
  EIGEN_DEFAULT_COPY_CONSTRUCTOR(ArrayBaseNC)

 public:
  ArrayBaseNC(Index x, Index y) : Base(x, y) {}
  explicit ArrayBaseNC(Index x) : Base(x) {}
  EIGEN_DEFINE_PUBLIC_INTERFACE(Derived)
  enum { IsRowMajor = Flags&RowMajor };

  EIGEN_IMPORT_CHANNELTYPE(Scalar)
  EIGEN_IMPORT_NUMCHANNELS(Scalar)

# include "./arraybasenc/NullaryOps.h"
# include "./arraybasenc/BinaryOps.h"
# include "./arraybasenc/ScalarOps.h"
# include "./arraybasenc/UnaryOps.h"
# include "./arraybasenc/CastExpr.h"
# include "./arraybasenc/Reshaped.h"
# include "./arraybasenc/Approx.h"
# include "./arraybasenc/Select.h"
# include "./arraybasenc/Coeffs.h"
# include "./arraybasenc/Assign.h"

  using Base::operator +=;
  using Base::operator -=;
  using Base::operator *=;
  using Base::operator /=;
  using Base::operator  =;
};

namespace internal {

#undef /***/ SWITCH_BASE
#undef /***/ HAS_EXPR2D
