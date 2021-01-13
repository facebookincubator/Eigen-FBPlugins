/* Copyright (c) Facebook, Inc. and its affiliates. */

#define /**/ CONSTANT_XPR CwiseNullaryOp<internal::scalar_constant_op<Scalar>, PlainObject>
#define /**/ BIT_FUNC(x) internal::scalar_bitwise_##x##_op<Scalar>

#define /**/ LHS(x) CwiseBinaryOp<BIT_FUNC(x), const Derived, const CONSTANT_XPR >
#define /**/ RHS(x) CwiseBinaryOp<BIT_FUNC(x), const CONSTANT_XPR, const Derived >

EIGEN_STRONG_INLINE_DEVICE_FUNC /****/
const LHS(xor) operator ^(const ChannelType& arg) const
  { return LHS(xor)(derived(), PlainObject::Constant(derived().rows(), derived().cols(), arg)); }

EIGEN_STRONG_INLINE_DEVICE_FUNC /****/
const LHS(and) operator &(const ChannelType& arg) const
  { return LHS(and)(derived(), PlainObject::Constant(derived().rows(), derived().cols(), arg)); }

EIGEN_STRONG_INLINE_DEVICE_FUNC /****/
const LHS(or)  operator |(const ChannelType& arg) const
  { return LHS(or) (derived(), PlainObject::Constant(derived().rows(), derived().cols(), arg)); }

EIGEN_STRONG_INLINE_DEVICE_FUNC friend
const RHS(xor) operator ^(const ChannelType& arg, const ArrayBase& obj)
  { return RHS(xor)(PlainObject::Constant(obj.rows(), obj.cols(), arg), obj.derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC friend
const RHS(and) operator &(const ChannelType& arg, const ArrayBase& obj)
  { return RHS(and)(PlainObject::Constant(obj.rows(), obj.cols(), arg), obj.derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC friend
const RHS(or)  operator |(const ChannelType& arg, const ArrayBase& obj)
  { return RHS(or) (PlainObject::Constant(obj.rows(), obj.cols(), arg), obj.derived()); }

#undef /***/ CONSTANT_XPR
#undef /***/ BIT_FUNC
#undef /***/ LHS
#undef /***/ RHS
