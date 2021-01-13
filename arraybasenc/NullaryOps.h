/* Copyright (c) Facebook, Inc. and its affiliates. */

#define /**/ DEFINE_CONST_NULLARY_OP(FuncName, value)                                     \
  EIGEN_STRONG_INLINE_DEVICE_FUNC static                                                  \
  const typename DenseBase<Derived>::ConstantReturnType FuncName(Index rows, Index cols)  \
    { return Constant(rows, cols, ChannelType(value)); }                                  \
                                                                                          \
  EIGEN_STRONG_INLINE_DEVICE_FUNC static                                                  \
  const typename DenseBase<Derived>::ConstantReturnType FuncName(Index size)              \
    { return Constant(size, ChannelType(value)); }                                        \
                                                                                          \
  EIGEN_STRONG_INLINE_DEVICE_FUNC                                                         \
  Derived& set##FuncName() { return setConstant(ChannelType(value)); }                    \
                                                                                          \
  EIGEN_STRONG_INLINE_DEVICE_FUNC static                                                  \
  const typename DenseBase<Derived>::ConstantReturnType FuncName()                        \
    { return Constant(ChannelType(value)); }

EIGEN_STRONG_INLINE_DEVICE_FUNC static
const typename DenseBase<Derived>::ConstantReturnType Constant(Index N, Index M, const ChannelType& value)
  { return DenseBase<Derived>::NullaryExpr(N, M, internal::scalar_constant_op<Scalar>(value)); }

EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE static
const typename DenseBase<Derived>::ConstantReturnType Constant(Index size, const ChannelType& value)
  { return DenseBase<Derived>::NullaryExpr(size, internal::scalar_constant_op<Scalar>(value)); }

EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE static
const typename DenseBase<Derived>::ConstantReturnType Constant(const ChannelType& value)
  { EIGEN_STATIC_ASSERT_FIXED_SIZE(Derived); enum { N = RowsAtCompileTime, M = ColsAtCompileTime };
    return DenseBase<Derived>::NullaryExpr(N, M, internal::scalar_constant_op<Scalar>(value)); }

EIGEN_STRONG_INLINE_DEVICE_FUNC void fill(const ChannelType& val) { setConstant(val); }

EIGEN_STRONG_INLINE_DEVICE_FUNC Derived& setConstant(const ChannelType& val)
  { return derived() = Constant(derived().rows(), derived().cols(), val); }

DEFINE_CONST_NULLARY_OP(Zero, 0)
DEFINE_CONST_NULLARY_OP(Ones, 1)

#undef /***/ DEFINE_CONST_NULLARY_OP
