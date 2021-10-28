/* Copyright (c) Facebook, Inc. and its affiliates. */

#define INHERIT_OP(op)                                             \
  template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC \
  const auto op(const ArrayBaseNC<OtherDerived>& arg) const {      \
    return derived().ArrayBase::op(arg.derived());                 \
  }

INHERIT_OP(operator !=)
INHERIT_OP(operator ==)
INHERIT_OP(operator >=)
INHERIT_OP(operator <=)

INHERIT_OP(operator >)
INHERIT_OP(operator <)
INHERIT_OP(operator &)
INHERIT_OP(operator |)

INHERIT_OP(min)
INHERIT_OP(max)

#undef INHERIT_OP

#define PROMOTED_TP typename internal::promote_scalar_arg<ChannelType, ScalarType, 0>::type
#define /**/ GUARD typename internal::make_int<PROMOTED_TP>::type = 0

#define /**/ CONSTANT_XPR CwiseNullaryOp<internal::scalar_constant_op<Scalar>, PlainObject>
#define /**/ _COMP_FUNC_(fn) internal::scalar_cmp_op<Scalar, Scalar, internal::cmp_##fn>
#define /**/ _BASE_FUNC_(fn) internal::scalar_##fn##_op<Scalar, Scalar>
#define /**/ _BIT_FUNC_(fn) internal::scalar_bitwise_##fn##_op<Scalar>
#define /**/ COMP_FUNC(fn) EIGEN_PROTECT_TYPE((_COMP_FUNC_(fn)))
#define /**/ BASE_FUNC(fn) EIGEN_PROTECT_TYPE((_BASE_FUNC_(fn)))
#define /**/ BIT_FUNC(fn) EIGEN_PROTECT_TYPE((_BIT_FUNC_(fn)))

#define /**/ _LHS_(x) CwiseBinaryOp<x, const Derived, const CONSTANT_XPR >
#define /**/ LHS(x) EIGEN_PROTECT_TYPE((_LHS_(x)))

#define /**/ _RHS_(x) CwiseBinaryOp<x, const CONSTANT_XPR, const Derived >
#define /**/ RHS(x) EIGEN_PROTECT_TYPE((_RHS_(x)))

#define /**/ DEFINE_LHS_OPERATION_WITH_SCALARS(x, op)                   \
  template <typename ScalarType, GUARD> EIGEN_STRONG_INLINE_DEVICE_FUNC \
  const LHS(x) op(const ScalarType& arg /**********************/) const \
    { return LHS(x)(derived(), PlainObject::Constant(derived().rows(), derived().cols(), static_cast<ChannelType>(arg))); }

#define /**/ DEFINE_RHS_OPERATION_WITH_SCALARS(x, op)                   \
  template <typename ScalarType, GUARD> EIGEN_STRONG_INLINE_DEVICE_FUNC \
  friend const RHS(x) op(const ScalarType& arg, const ArrayBaseNC& obj) \
    { return RHS(x)(PlainObject::Constant(obj.rows(), obj.cols(), static_cast<ChannelType>(arg)), obj.derived()); }

#define /**/ DEFINE_OPERATION_WITH_SCALARS(x, op) \
  DEFINE_LHS_OPERATION_WITH_SCALARS(x, op)        \
  DEFINE_RHS_OPERATION_WITH_SCALARS(x, op)

DEFINE_OPERATION_WITH_SCALARS(COMP_FUNC(NEQ), operator !=)
DEFINE_OPERATION_WITH_SCALARS(COMP_FUNC(EQ), operator ==)
DEFINE_OPERATION_WITH_SCALARS(COMP_FUNC(LE), operator <=)
DEFINE_OPERATION_WITH_SCALARS(COMP_FUNC(GE), operator >=)
DEFINE_OPERATION_WITH_SCALARS(COMP_FUNC(LT), operator <)
DEFINE_OPERATION_WITH_SCALARS(COMP_FUNC(GT), operator >)

// TODO(ygitman): Support NaN propagation
DEFINE_LHS_OPERATION_WITH_SCALARS(BASE_FUNC(min), (min))
DEFINE_LHS_OPERATION_WITH_SCALARS(BASE_FUNC(max), (max))

DEFINE_OPERATION_WITH_SCALARS(BIT_FUNC(and), operator &)
DEFINE_OPERATION_WITH_SCALARS(BIT_FUNC(or), operator |)

#undef /***/ DEFINE_LHS_OPERATION_WITH_SCALARS
#undef /***/ DEFINE_RHS_OPERATION_WITH_SCALARS
#undef /***/ DEFINE_OPERATION_WITH_SCALARS
#undef /***/ CONSTANT_XPR
#undef /***/ PROMOTED_TP
#undef /***/ _COMP_FUNC_
#undef /***/ _BASE_FUNC_
#undef /***/ _BIT_FUNC_
#undef /***/ COMP_FUNC
#undef /***/ BASE_FUNC
#undef /***/ BIT_FUNC
#undef /***/ GUARD
#undef /***/ _LHS_
#undef /***/ _RHS_
#undef /***/ LHS
#undef /***/ RHS

using Base::operator !=;
using Base::operator ==;
using Base::operator <=;
using Base::operator >=;

using Base::operator <;
using Base::operator >;
using Base::operator &;
using Base::operator |;

using Base::min;
using Base::max;
