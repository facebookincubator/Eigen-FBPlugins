/* Copyright (c) Facebook, Inc. and its affiliates. */

#define /**/ ASSERT_INTEGRAL_SCALAR                                                                                                \
  EIGEN_STATIC_ASSERT((EIGEN_IS_INTEGRAL_TYPE(typename internal::wrap_scalar<typename OtherDerived::Scalar>::ChannelType)          \
                    && EIGEN_IS_INTEGRAL_TYPE(ChannelType)), THIS_TYPE_IS_NOT_SUPPORTED);

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
const CwiseBinaryOp<internal::scalar_bitwise_and_op<Scalar>, Derived, OtherDerived> operator &(const ArrayBase<OtherDerived>& arg) const
  { ASSERT_INTEGRAL_SCALAR; return CwiseBinaryOp<internal::scalar_bitwise_and_op<Scalar>, Derived, OtherDerived>(derived(), arg.derived()); }

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
const CwiseBinaryOp<internal::scalar_bitwise_xor_op<Scalar>, Derived, OtherDerived> operator ^(const OtherDerived& arg) const
  { ASSERT_INTEGRAL_SCALAR; return CwiseBinaryOp<internal::scalar_bitwise_xor_op<Scalar>, Derived, OtherDerived>(derived(), arg.derived()); }

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
const CwiseBinaryOp<internal::scalar_bitwise_or_op<Scalar>, Derived, OtherDerived>  operator |(const ArrayBase<OtherDerived>& arg) const
  { ASSERT_INTEGRAL_SCALAR; return CwiseBinaryOp<internal::scalar_bitwise_or_op<Scalar>, Derived, OtherDerived>(derived(),  arg.derived()); }

#undef /***/ ASSERT_INTEGRAL_SCALAR
