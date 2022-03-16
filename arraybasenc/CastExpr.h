/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Tp> EIGEN_STRONG_INLINE_DEVICE_FUNC const auto cast() const
EIGEN_REQUIRES((std::is_convertible_v<ChannelType, Tp>)) {
  const auto& fn = [](const auto& v) EIGEN_LAMBDA_INLINE { return internal::ops::cast<Tp>(v); };
  return derived().unaryExpr(internal::make_functor<NumTraits<Scalar>::AddCost>(fn));
}
