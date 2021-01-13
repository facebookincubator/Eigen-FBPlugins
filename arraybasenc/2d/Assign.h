/* Copyright (c) Facebook, Inc. and its affiliates. */

#define /**/ CHANNELTYPE(Tp) typename internal::wrap_scalar<typename internal::traits<Tp>::Scalar>::ChannelType
#define /**/ ASSIGN_FUNC(op) internal::op##_assign_op<ChannelType, CHANNELTYPE(OtherDerived)>()

template <typename OtherDerived, typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
EIGEN_ENABLE_IFF_EXPR2D_EXISTS(OtherDerived, Derived)& operator +=(const ArrayBaseNCImpl2d<OtherDerived>& other)
  { typename Expr2d<Derived>::type p = derived().as2d(); internal::call_assignment_no_alias(p, other.derived().as2d(), ASSIGN_FUNC(add)); return derived(); }

template <typename OtherDerived, typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
EIGEN_ENABLE_IFF_EXPR2D_EXISTS(OtherDerived, Derived)& operator -=(const ArrayBaseNCImpl2d<OtherDerived>& other)
  { typename Expr2d<Derived>::type p = derived().as2d(); internal::call_assignment_no_alias(p, other.derived().as2d(), ASSIGN_FUNC(sub)); return derived(); }

template <typename OtherDerived, typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
EIGEN_ENABLE_IFF_EXPR2D_EXISTS(OtherDerived, Derived)& operator *=(const ArrayBaseNCImpl2d<OtherDerived>& other)
  { typename Expr2d<Derived>::type p = derived().as2d(); internal::call_assignment_no_alias(p, other.derived().as2d(), ASSIGN_FUNC(mul)); return derived(); }

template <typename OtherDerived, typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
EIGEN_ENABLE_IFF_EXPR2D_EXISTS(OtherDerived, Derived)& operator /=(const ArrayBaseNCImpl2d<OtherDerived>& other)
  { typename Expr2d<Derived>::type p = derived().as2d(); internal::call_assignment_no_alias(p, other.derived().as2d(), ASSIGN_FUNC(div)); return derived(); }

template <typename OtherDerived, typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
EIGEN_ENABLE_IFF_EXPR2D_EXISTS(OtherDerived, Derived)& operator =(const ArrayBaseNCImpl2d<OtherDerived>& other)
  { typename Expr2d<Derived>::type p = derived().as2d(); internal::call_assignment(p, other.derived().as2d()); return derived(); }

template <typename OtherDerived, typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
EIGEN_ENABLE_IFF_EXPR2D_EXISTS(OtherDerived, Derived)& operator =(const ArrayBaseNCImpl2d& other)
  { typename Expr2d<Derived>::type p = derived().as2d(); internal::call_assignment(p, other.derived().as2d()); return derived(); }

#undef /***/ ASSIGN_FUNC
#undef /***/ CHANNELTYPE
