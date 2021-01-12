/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC
const CwiseUnaryOp<internal::scalar_boolean_not_op<Scalar>, Derived> operator!() const {
  EIGEN_STATIC_ASSERT((internal::is_same<ChannelType, bool>::value), THIS_TYPE_IS_NOT_SUPPORTED);
  return CwiseUnaryOp<internal::scalar_boolean_not_op<Scalar>, Derived>(derived());
}

#define /**/ RTYPE typename internal::result_of<F(const Scalar&)>::type
#define /**/ COND (internal::wrap_scalar<RTYPE>::NumChannels == 1)
#define /**/ G internal::channelwise_redux_wrapper<F, Scalar>

#define /**/ WRAP_FN \
  typename internal::conditional<COND, G, F>::type

template<typename F> EIGEN_STRONG_INLINE_DEVICE_FUNC
const CwiseUnaryOp<WRAP_FN, const Derived> unaryExpr(const F& fn = F()) const
  { return CwiseUnaryOp<WRAP_FN, const Derived>(derived(), WRAP_FN(fn)); }

#undef /***/ WRAP_FN
#undef /***/ RTYPE
#undef /***/ COND
#undef /***/ G
