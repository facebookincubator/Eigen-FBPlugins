/* Copyright (c) Facebook, Inc. and its affiliates. */

#ifndef EIGEN_DISABLE_EXPRESSION_OPTIMISAZTIONS
#  define SWITCH_BASE \
    std::conditional_t<Expr2d<Derived>::value, ArrayBaseNCImpl2d<Derived>, ArrayBaseNCImpl<Derived>>
#else
#  define SWITCH_BASE std::enable_if_t<true, ArrayBaseNCImpl<Derived> >
#endif

#if !defined(EIGEN_DISABLE_MULTICHANNEL_ARRAYS)

template<typename Tp, int N, int M, int Opts, int P, int Q, int U, int V>
struct traits<Array<Array<Tp, U, V, 0, U, V>, N, M, Opts, P, Q> >
  : traits<Matrix<Array<Tp, U, V, 0, U, V>, N, M, Opts, P, Q> >
  { typedef ArrayXprNC XprKind; };

#endif

}  // namespace internal

template <typename Derived>
struct ArrayBaseNCImpl2d : ArrayBase<Derived> {
  auto as2d() const { return Expr2d<const Derived>::make(derived()); }
  auto as2d() { return Expr2d<Derived>::make(derived()); }
  typedef ArrayBase<Derived> Base;

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
  typedef ArrayBase<Derived> Base;

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
  using Base::Base;
};

template <typename Derived> struct ArrayBaseNC : SWITCH_BASE {
  template <int Direction> EIGEN_STRONG_INLINE_DEVICE_FUNC auto getVectorwiseOpImpl() const
    { return VectorwiseOpNC<const Derived, Direction>(derived()); }

  typedef SWITCH_BASE Base;

  EIGEN_DEFINE_PUBLIC_INTERFACE(Derived)
  enum { IsRowMajor = Flags&RowMajor };

  EIGEN_IMPORT_CHANNELTYPE(Scalar)
  EIGEN_IMPORT_NUMCHANNELS(Scalar)

# include "./arraybasenc/Select-helper.h"

# include "./arraybasenc/NullaryOps.h"
# include "./arraybasenc/BooleanOps.h"
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
  using Base::Base;
};

namespace internal {

#undef /***/ SWITCH_BASE
