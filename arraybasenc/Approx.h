/* Copyright (c) Facebook, Inc. and its affiliates. */

#define /**/ PRECISION const typename NumTraits<ChannelType>::Real& prec = NumTraits<Scalar>::dummy_precision()
#define /**/ BOOLEAN_IF_INTEGRAL EIGEN_DEFERRED_CHECK_ENABLE_IF(EIGEN_IS_INTEGRAL_TYPE(ChannelType) == 1, bool)
#define /**/ BOOLEAN_IF_FLOATING EIGEN_DEFERRED_CHECK_ENABLE_IF(EIGEN_IS_INTEGRAL_TYPE(ChannelType) == 0, bool)

template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
BOOLEAN_IF_FLOATING isMuchSmallerThan(const typename NumTraits<ChannelType>::Real& other, PRECISION) const
  { return derived().abs2().sum() <= prec * prec * other * other; }

template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
BOOLEAN_IF_INTEGRAL isMuchSmallerThan(const typename NumTraits<ChannelType>::Real&, PRECISION) const
  { return (derived() == ChannelType(0)).all(); }

template <typename OtherDerived, typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
BOOLEAN_IF_FLOATING isMuchSmallerThan(const DenseBase<OtherDerived>& other, PRECISION) const
  { return derived().abs2().sum() <= prec * prec * other.derived().abs2().sum(); }

template <typename OtherDerived, typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
BOOLEAN_IF_INTEGRAL isMuchSmallerThan(const DenseBase<OtherDerived>&, PRECISION) const
  { return (derived() == ChannelType(0)).all(); }

template <typename OtherDerived, typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
BOOLEAN_IF_FLOATING isApprox(const DenseBase<OtherDerived>& other, PRECISION) const
  { EIGEN_COMMON_SUBEXPR(OtherDerived, other, B, 2); EIGEN_COMMON_SUBEXPR(Derived, (*this), A, 2);
    return (A - B).abs2().sum() <= prec * prec * numext::mini(A.abs2().sum(), B.abs2().sum()); }

template <typename OtherDerived, typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
BOOLEAN_IF_INTEGRAL isApprox(const DenseBase<OtherDerived>& other, PRECISION) const
  { return (derived() == other.derived()).all(); }

template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
BOOLEAN_IF_FLOATING isApproxToConstant(const ChannelType& val, PRECISION) const
  { EIGEN_COMMON_SUBEXPR(Derived, (*this), A, 2); return ((A - val).abs2().sum() <= prec * prec * numext::mini(A.abs2().sum(), numext::abs2(val).sum())); }

template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
BOOLEAN_IF_INTEGRAL isApproxToConstant(const ChannelType& val, PRECISION) const
  { return (derived() == val).all(); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
bool isConstant(const ChannelType& val, PRECISION) const
  { return derived().isApproxToConstant(val, prec); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
bool isOnes(PRECISION) const
  { return derived().isApproxToConstant(1, prec); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
bool isZero(PRECISION) const
  { return derived().isMuchSmallerThan(1, prec); }

#undef /***/ BOOLEAN_IF_INTEGRAL
#undef /***/ BOOLEAN_IF_FLOATING
#undef /***/ PRECISION
