/* Copyright (c) Facebook, Inc. and its affiliates. */

#include "./MissingOps-helper.h"

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

// TODO(ygitman): add 2D and 3D cases
EIGEN_STRONG_INLINE_DEVICE_FUNC Index argany() const
EIGEN_REQUIRES(internal::IsVectorExpression<Derived>) {
#ifdef /****/ EIGEN_EXTRA_SAFETY
  EIGEN_STATIC_ASSERT((internal::is_same<ChannelType, bool>::value), THIS_TYPE_IS_NOT_SUPPORTED);
#endif /**/// EIGEN_EXTRA_SAFETY

  typedef internal::evaluator<Derived> Evaluator;
  Evaluator evaluator(derived());

  // TODO(ygitman): add unrolling

  for (Index i = 0; i < derived().size(); ++i)
    if (evaluator.coeff(i))
      return i;

  return false;
}

EIGEN_STRONG_INLINE_DEVICE_FUNC
Scalar median() const {
  auto A = derived().reshaped().eval();
  Index p = A.size() / 2;

  // TODO(ygitman): remove extra copy?

  std::nth_element(A.data(), A.data() + p, A.data() + A.size());
  return A.size()&1 ? A[p] : (A[p] + A.head(p).maxCoeff()) / 2;
}

EIGEN_STRONG_INLINE_DEVICE_FUNC
Scalar middleElement() const {
  auto vals = derived().reshaped().eval();
  Scalar* p = vals.data();
  Index N = vals.size();

  // TODO(ygitman): remove extra copy?

  std::nth_element(p, p + (N / 2), p + N);
  return vals[(N - 1) / 2];
}

EIGEN_STRONG_INLINE_DEVICE_FUNC
Scalar quantile(float x) const {
  auto vals = derived().reshaped().eval();
  int q_index = x * vals.size() - x + 0.5;
  eigen_assert(0 <= x && x <= 1.0);
  Scalar* p = vals.data();
  Index N = vals.size();

  // TODO(ygitman): remove extra copy?

  std::nth_element(p, p + q_index, p + N);
  return vals[q_index];
}
