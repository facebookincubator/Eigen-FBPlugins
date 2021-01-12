/* Copyright (c) Facebook, Inc. and its affiliates. */

#define /**/ PROMOTED_SCALAR typename internal::promote_scalar_arg<typename Tp::Scalar, ScalarArgType, false>::type
#define /**/ CONSTANT_XPR CwiseNullaryOp<internal::scalar_constant_op<PROMOTED_SCALAR>, typename Tp::PlainObject>

template <typename Tp, typename ScalarArgType> EIGEN_STRONG_INLINE_DEVICE_FUNC
const SelectNC<Derived, Tp, CONSTANT_XPR> select(const DenseBase<Tp>& x, const ScalarArgType& y) const {
  const auto& cnt = Tp::Constant(derived().rows(), derived().cols(), static_cast<typename Tp::ChannelType>(y));
  return SelectNC<Derived, Tp, CONSTANT_XPR>(derived(), x.derived(), cnt);
}

template <typename Tp, typename ScalarArgType> EIGEN_STRONG_INLINE_DEVICE_FUNC
const SelectNC<Derived, CONSTANT_XPR, Tp> select(const ScalarArgType& x, const DenseBase<Tp>& y) const {
  const auto& cnt = Tp::Constant(derived().rows(), derived().cols(), static_cast<typename Tp::ChannelType>(x));
  return SelectNC<Derived, CONSTANT_XPR, Tp>(derived(), cnt, y.derived());
}

template <typename Tp1, typename Tp2> EIGEN_STRONG_INLINE_DEVICE_FUNC
const SelectNC<Derived, Tp1, Tp2> select(const DenseBase<Tp1>& x, const DenseBase<Tp2>& elseArray) const
  { return SelectNC<Derived, Tp1, Tp2>(derived(), x.derived(), elseArray.derived()); }

#undef /***/ PROMOTED_SCALAR
#undef /***/ CONSTANT_XPR
