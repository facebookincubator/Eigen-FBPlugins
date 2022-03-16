/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Tp, typename ScalarArgType, EIGEN_ENABLE_IF_PROMOTABLE(typename Tp::ChannelType, ScalarArgType)>
EIGEN_STRONG_INLINE_DEVICE_FUNC const auto select(const DenseBase<Tp>& thenArray, const ScalarArgType& elseArg) const {
  const auto& cnt = Tp::Constant(derived().rows(), derived().cols(), static_cast<typename Tp::ChannelType>(elseArg));
  const auto& fn = [](const auto& x, const auto& y, const auto& z) EIGEN_LAMBDA_INLINE { return internal::ops::select(x, y, z); };
  return derived().ternaryExprHelper(thenArray.derived(), cnt, internal::make_functor<NumTraits<Scalar>::AddCost>(fn));
}

template <typename Tp, typename ScalarArgType, EIGEN_ENABLE_IF_PROMOTABLE(typename Tp::ChannelType, ScalarArgType)>
EIGEN_STRONG_INLINE_DEVICE_FUNC const auto select(const ScalarArgType& thenArg, const DenseBase<Tp>& elseArray) const {
  const auto& cnt = Tp::Constant(derived().rows(), derived().cols(), static_cast<typename Tp::ChannelType>(thenArg));
  const auto& fn = [](const auto& x, const auto& y, const auto& z) EIGEN_LAMBDA_INLINE { return internal::ops::select(x, y, z); };
  return derived().ternaryExprHelper(cnt, elseArray.derived(), internal::make_functor<NumTraits<Scalar>::AddCost>(fn));
}

template <typename Tp1, typename Tp2> EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto select(const DenseBase<Tp1>& thenArray, const DenseBase<Tp2>& elseArray) const
EIGEN_REQUIRES((std::is_same_v<typename Tp1::Scalar, typename Tp2::Scalar>)) {
  const auto& fn = [](const auto& x, const auto& y, const auto& z) EIGEN_LAMBDA_INLINE { return internal::ops::select(x, y, z); };
  return derived().ternaryExprHelper(thenArray.derived(), elseArray.derived(), internal::make_functor<NumTraits<Scalar>::AddCost>(fn));
}
