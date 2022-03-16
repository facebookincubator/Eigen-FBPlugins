/* Copyright (c) Facebook, Inc. and its affiliates. */

#define PRECISION \
    const typename NumTraits<ChannelType>::Real& prec = NumTraits<Scalar>::dummy_precision()

EIGEN_STRONG_INLINE_DEVICE_FUNC
bool isMuchSmallerThan(const typename NumTraits<ChannelType>::Real& other, PRECISION) const {
  return (std::is_same_v<ChannelType, typename NumTraits<ChannelType>::NonInteger>)
      ? derived().abs2().sum() <= prec * prec * other * other
      : (derived() == ChannelType(0)).all();
}

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
bool isMuchSmallerThan(const DenseBase<OtherDerived>& other, PRECISION) const {
  return (std::is_same_v<ChannelType, typename NumTraits<ChannelType>::NonInteger>)
      ? derived().abs2().sum() <= prec * prec * other.derived().abs2().sum()
      : (derived() == ChannelType(0)).all();
}

EIGEN_STRONG_INLINE_DEVICE_FUNC
bool isApproxToConstant(const ChannelType& val, PRECISION) const {
  if (std::is_same_v<ChannelType, typename NumTraits<ChannelType>::NonInteger>) {
    auto A = derived().template nested_eval<2>();
    auto rhs = numext::mini(A.abs2().sum(), numext::abs2(val));
    return (A - val).abs2().sum() <= prec * prec * rhs;
  } else {
    return (derived() == val).all();
  }
}

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
bool isApprox(const DenseBase<OtherDerived>& other, PRECISION) const {
  if (std::is_same_v<ChannelType, typename NumTraits<ChannelType>::NonInteger>) {
    auto B = other.derived().template nested_eval<2>();
    auto A = derived().template nested_eval<2>();

    auto rhs = numext::mini(A.abs2().sum(), B.abs2().sum());
    return (A - B).abs2().sum() <= prec * prec * rhs;
  } else {
    return (derived() == other.derived()).all();
  }
}

EIGEN_STRONG_INLINE_DEVICE_FUNC
bool isConstant(const ChannelType& val, PRECISION) const
  { return derived().isApproxToConstant(val, prec); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
bool isOnes(PRECISION) const
  { return derived().isApproxToConstant(1, prec); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
bool isZero(PRECISION) const
  { return derived().isMuchSmallerThan(1, prec); }

#undef /***/ PRECISION
