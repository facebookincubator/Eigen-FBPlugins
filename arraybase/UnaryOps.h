/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC
const CwiseUnaryOp<internal::scalar_bitwise_not_op<Scalar>, Derived> operator~() const {
  EIGEN_STATIC_ASSERT((EIGEN_IS_INTEGRAL_TYPE(ChannelType)), THIS_TYPE_IS_NOT_SUPPORTED);
  return CwiseUnaryOp<internal::scalar_bitwise_not_op<Scalar>, Derived>(derived());
}
