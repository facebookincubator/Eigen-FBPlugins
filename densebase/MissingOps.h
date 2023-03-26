/* Copyright (c) Facebook, Inc. and its affiliates. */

#include "./MissingOps-helper.h"

template <int N> EIGEN_STRONG_INLINE_DEVICE_FUNC auto nested_eval() const EIGEN_REQUIRES(N >= 1)
  { return typename internal::nested_eval<Derived, N>::type(derived()); }

// TODO(ygitman): remove extra copy?
EIGEN_STRONG_INLINE auto sortDesc() const EIGEN_REQUIRES(internal::IsVectorExpression<Derived>)
  { auto A = derived().eval(); A.sortDescInPlace(); return A; }

// TODO(ygitman): remove extra copy?
EIGEN_STRONG_INLINE auto sortAsc() const EIGEN_REQUIRES(internal::IsVectorExpression<Derived>)
  { auto A = derived().eval(); A.sortAscInPlace(); return A; }

EIGEN_STRONG_INLINE void sortDescInPlace()
EIGEN_REQUIRES(internal::IsLValueExpression<Derived> && internal::IsVectorExpression<Derived>)
  { std::sort(derived().begin(), derived().end(), std::greater<Scalar>()); }

EIGEN_STRONG_INLINE void sortAscInPlace()
EIGEN_REQUIRES(internal::IsLValueExpression<Derived> && internal::IsVectorExpression<Derived>)
  { std::sort(derived().begin(), derived().end(), std::less<Scalar>()); }

//! Converts expression to tuple-alike object, mainly for binding declarations
EIGEN_STRONG_INLINE_DEVICE_FUNC const internal::Tuple<const Derived> asTuple() const
  { return internal::Tuple<const Derived>(derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC auto argmin() const {
  std::conditional_t<!IsVectorAtCompileTime, Array<Index, 2, 1>, Index> xy;
  derived().minCoeffHelper(&xy);
  return xy;
}

EIGEN_STRONG_INLINE_DEVICE_FUNC auto argmax() const {
  std::conditional_t<!IsVectorAtCompileTime, Array<Index, 2, 1>, Index> xy;
  derived().maxCoeffHelper(&xy);
  return xy;
}

auto clamp(const ChannelType& x, const ChannelType& y) const
  { return derived().max(x).min(y); }

// TODO(ygitman): Add min/max specializations for booleans
EIGEN_STRONG_INLINE_DEVICE_FUNC auto argany() const {
  if (!std::is_same<ChannelType, bool>::value)
    return derived().template cast<bool>().argmax();
  else
    return derived().argmax();
}

EIGEN_STRONG_INLINE_DEVICE_FUNC auto copy() const {
  return derived().eval();
}
