/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto operator &&(const ArrayBaseNC<OtherDerived>& arg) const
EIGEN_REQUIRES((std::is_same_v<ChannelType, bool> && std::is_same_v<typename OtherDerived::ChannelType, bool>)) {
  const auto& fn = [](const auto& x, const auto& y) EIGEN_LAMBDA_INLINE { return x && y; };
  return derived().binaryExpr(arg.derived(), internal::make_functor<NumTraits<Scalar>::AddCost>(fn));
}

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto operator ||(const ArrayBaseNC<OtherDerived>& arg) const
EIGEN_REQUIRES((std::is_same_v<ChannelType, bool> && std::is_same_v<typename OtherDerived::ChannelType, bool>)) {
  const auto& fn = [](const auto& x, const auto& y) EIGEN_LAMBDA_INLINE { return x || y; };
  return derived().binaryExpr(arg.derived(), internal::make_functor<NumTraits<Scalar>::AddCost>(fn));
}

EIGEN_STRONG_INLINE_DEVICE_FUNC const auto operator !() const
EIGEN_REQUIRES((std::is_same_v<ChannelType, bool>)) {
  const auto& fn = [](const auto& x) EIGEN_LAMBDA_INLINE { return !x; };
  return derived().unaryExpr(internal::make_functor<NumTraits<Scalar>::AddCost>(fn));
}
