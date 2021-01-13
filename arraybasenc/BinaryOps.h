/* Copyright (c) Facebook, Inc. and its affiliates. */

#define /**/ ASSERT_BOOLEAN_SCALAR                                                                                                 \
  EIGEN_STATIC_ASSERT((internal::is_same<bool, typename internal::wrap_scalar<typename OtherDerived::Scalar>::ChannelType>::value  \
                    && internal::is_same<bool, ChannelType>::value), THIS_METHOD_IS_ONLY_FOR_EXPRESSIONS_OF_BOOL);

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
const CwiseBinaryOp<internal::scalar_boolean_and_op_nc<Scalar>, Derived, OtherDerived> operator &&(const ArrayBaseNC<OtherDerived>& arg) const
  { ASSERT_BOOLEAN_SCALAR; return CwiseBinaryOp<internal::scalar_boolean_and_op_nc<Scalar>, Derived, OtherDerived>(derived(), arg.derived()); }

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
const CwiseBinaryOp<internal::scalar_boolean_or_op_nc<Scalar>, Derived, OtherDerived>  operator ||(const ArrayBaseNC<OtherDerived>& arg) const
  { ASSERT_BOOLEAN_SCALAR; return CwiseBinaryOp<internal::scalar_boolean_or_op_nc<Scalar>, Derived, OtherDerived>(derived(),  arg.derived()); }

#undef /***/ ASSERT_BOOLEAN_SCALAR
