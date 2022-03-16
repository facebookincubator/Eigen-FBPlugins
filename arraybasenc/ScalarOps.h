/* Copyright (c) Facebook, Inc. and its affiliates. */

#define DEFINE_RHS_OPERATION_WITH_SCALARS(op)                                                                         \
  template <typename ScalarType, EIGEN_ENABLE_IF_PROMOTABLE(ChannelType, ScalarType)> EIGEN_STRONG_INLINE_DEVICE_FUNC \
  friend const auto op(const ScalarType& y, const ArrayBaseNC& x) { return Derived::Constant(x.rows(), x.cols(), static_cast<ChannelType>(y)).op(x.derived()); }

#define DEFINE_LHS_OPERATION_WITH_SCALARS(op)                                                                         \
  template <typename ScalarType, EIGEN_ENABLE_IF_PROMOTABLE(ChannelType, ScalarType)> EIGEN_STRONG_INLINE_DEVICE_FUNC \
  const auto op(const ScalarType& y) const { return derived().op(Derived::Constant(derived().rows(), derived().cols(), static_cast<ChannelType>(y))); }

#define DEFINE_OPERATION_WITH_SCALARS(op) \
  DEFINE_LHS_OPERATION_WITH_SCALARS(op) DEFINE_RHS_OPERATION_WITH_SCALARS(op)

DEFINE_OPERATION_WITH_SCALARS(operator ==)
DEFINE_OPERATION_WITH_SCALARS(operator !=)
DEFINE_OPERATION_WITH_SCALARS(operator <=)
DEFINE_OPERATION_WITH_SCALARS(operator >=)
DEFINE_OPERATION_WITH_SCALARS(operator <)
DEFINE_OPERATION_WITH_SCALARS(operator >)

DEFINE_OPERATION_WITH_SCALARS(operator +)
DEFINE_OPERATION_WITH_SCALARS(operator -)
DEFINE_OPERATION_WITH_SCALARS(operator *)
DEFINE_OPERATION_WITH_SCALARS(operator /)

DEFINE_OPERATION_WITH_SCALARS(operator &)
DEFINE_OPERATION_WITH_SCALARS(operator |)
DEFINE_OPERATION_WITH_SCALARS(operator ^)

// TODO(ygitman): Support NaN propagation
DEFINE_LHS_OPERATION_WITH_SCALARS(min)
DEFINE_LHS_OPERATION_WITH_SCALARS(max)

DEFINE_LHS_OPERATION_WITH_SCALARS(pow)

#undef DEFINE_LHS_OPERATION_WITH_SCALARS
#undef DEFINE_RHS_OPERATION_WITH_SCALARS
#undef DEFINE_OPERATION_WITH_SCALARS

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
