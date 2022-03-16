/* Copyright (c) Facebook, Inc. and its affiliates. */

} // namespace internal

template <typename Derived>
struct ChannelwiseOp {
  template <int N>
  EIGEN_STRONG_INLINE_DEVICE_FUNC auto replicate() const {
    const auto& fn = [](const auto& x) EIGEN_LAMBDA_INLINE { return internal::ops::evaluate(internal::ops::replicate<N>(x)); };
    return ref.unaryExpr(internal::make_channelwise_functor<NumTraits<typename Derived::Scalar>::AddCost, N != 1>(fn));
  }

#define MAKE_CHANNELWISE_REDUX_METHOD(fn, cost)                                                      \
  EIGEN_STRONG_INLINE_DEVICE_FUNC const auto fn() const {                                            \
    const auto& fn = [](const auto& x) EIGEN_LAMBDA_INLINE { return internal::ops::redux_##fn(x); }; \
    return ref.unaryExpr(internal::make_channelwise_functor<cost, 0>(fn));                           \
  }

#define OP_COST(fn) internal::functor_traits<internal::scalar_##fn##_op<ChannelType>>::Cost

  typename internal::ultimate_ref_selector<Derived>::type ref;

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  ChannelwiseOp(Derived& refexpr) : ref(refexpr) {}

  typedef typename Derived::Scalar Scalar;
  EIGEN_IMPORT_CHANNELTYPE(Scalar);
  EIGEN_IMPORT_NUMCHANNELS(Scalar);

// TODO(ygitman): implement the rest

  static constexpr int AddCost = (NumTraits<ChannelType>::AddCost);
  static constexpr int MulCost = (NumTraits<ChannelType>::MulCost);
  static constexpr int AddReduxCost = AddCost * (NumChannels - 1);
  static constexpr int MulReduxCost = MulCost * (NumChannels - 1);

  static constexpr int NormCost = (NumChannels + 5) * MulCost + (NumChannels - 1) * AddCost;
  MAKE_CHANNELWISE_REDUX_METHOD(squaredNorm, AddReduxCost + NumChannels * OP_COST(abs2))
  MAKE_CHANNELWISE_REDUX_METHOD(hypotNorm, (NumChannels - 1) * OP_COST(hypot))
  MAKE_CHANNELWISE_REDUX_METHOD(mean, AddReduxCost + OP_COST(quotient))
  MAKE_CHANNELWISE_REDUX_METHOD(maxCoeff, AddReduxCost)
  MAKE_CHANNELWISE_REDUX_METHOD(minCoeff, AddReduxCost)
  MAKE_CHANNELWISE_REDUX_METHOD(stableNorm, NormCost)
  MAKE_CHANNELWISE_REDUX_METHOD(count, AddReduxCost)
  MAKE_CHANNELWISE_REDUX_METHOD(blueNorm, NormCost)
  MAKE_CHANNELWISE_REDUX_METHOD(prod, MulReduxCost)
  MAKE_CHANNELWISE_REDUX_METHOD(sum, AddReduxCost)
  MAKE_CHANNELWISE_REDUX_METHOD(all, AddReduxCost)
  MAKE_CHANNELWISE_REDUX_METHOD(any, AddReduxCost)
  MAKE_CHANNELWISE_REDUX_METHOD(norm, NormCost)

#undef MAKE_CHANNELWISE_REDUX_METHOD
#undef OP_COST
};

namespace internal {
