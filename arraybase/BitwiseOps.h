/* Copyright (c) Facebook, Inc. and its affiliates. */

// TODO(ygitman): packet access

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto operator &(const ArrayBase<OtherDerived>& arg) const
EIGEN_REQUIRES((requires (const Scalar x, const typename OtherDerived::Scalar y) { x & y; })) {
  // Explicit result type is needed as bitwise operations are subject to integral promotions
  const auto& fn = [](const auto& x, const auto& y) EIGEN_LAMBDA_INLINE { return internal::ops::cast<ChannelType>(x & y); };
  return derived().binaryExpr(arg, internal::make_functor<NumTraits<Scalar>::AddCost>(fn));
}

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto operator |(const ArrayBase<OtherDerived>& arg) const
EIGEN_REQUIRES((requires (const Scalar x, const typename OtherDerived::Scalar y) { x | y; })) {
  // Explicit result type is needed as bitwise operations are subject to integral promotions
  const auto& fn = [](const auto& x, const auto& y) EIGEN_LAMBDA_INLINE { return internal::ops::cast<ChannelType>(x | y); };
  return derived().binaryExpr(arg, internal::make_functor<NumTraits<Scalar>::AddCost>(fn));
}

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto operator ^(const OtherDerived& arg) const
EIGEN_REQUIRES((requires (const Scalar x, const typename OtherDerived::Scalar y) { x ^ y; })) {
  // Explicit result type is needed as bitwise operations are subject to integral promotions
  const auto& fn = [](const auto& x, const auto& y) EIGEN_LAMBDA_INLINE { return internal::ops::cast<ChannelType>(x ^ y); };
  return derived().binaryExpr(arg, internal::make_functor<NumTraits<Scalar>::AddCost>(fn));
}

EIGEN_STRONG_INLINE_DEVICE_FUNC const auto operator~() const
EIGEN_REQUIRES((requires (const Scalar x) { ~x; })) {
  const auto& fn = [](const auto& x) EIGEN_LAMBDA_INLINE { return internal::ops::cast<ChannelType>(~x); };
  return derived().unaryExpr(internal::make_functor<NumTraits<Scalar>::AddCost>(fn));
}

EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto operator ^(const ChannelType& arg) const
  { return derived() ^ PlainObject::Constant(derived().rows(), derived().cols(), arg); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto operator &(const ChannelType& arg) const
  { return derived() & PlainObject::Constant(derived().rows(), derived().cols(), arg); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto operator |(const ChannelType& arg) const
  { return derived() | PlainObject::Constant(derived().rows(), derived().cols(), arg); }

EIGEN_STRONG_INLINE_DEVICE_FUNC friend
const auto operator ^(const ChannelType& arg, const ArrayBase& obj)
  { return PlainObject::Constant(obj.rows(), obj.cols(), arg) ^ obj.derived(); }

EIGEN_STRONG_INLINE_DEVICE_FUNC friend
const auto operator &(const ChannelType& arg, const ArrayBase& obj)
  { return PlainObject::Constant(obj.rows(), obj.cols(), arg) & obj.derived(); }

EIGEN_STRONG_INLINE_DEVICE_FUNC friend
const auto operator |(const ChannelType& arg, const ArrayBase& obj)
  { return PlainObject::Constant(obj.rows(), obj.cols(), arg) | obj.derived(); }
