/* Copyright (c) Facebook, Inc. and its affiliates. */

//! Converts expression to tuple-alike object, mainly for binding declarations
EIGEN_STRONG_INLINE_DEVICE_FUNC const internal::Tuple<const Derived> asTuple() const
  { return internal::Tuple<const Derived>(derived()); }

EIGEN_STRONG_INLINE void sortDescInPlace()
  { std::sort(derived().begin(), derived().end(), std::greater<Scalar>()); }

EIGEN_STRONG_INLINE void sortAscInPlace()
  { std::sort(derived().begin(), derived().end(), std::less<Scalar>()); }

#define EVAL_EXPR_TYPE typename internal::remove_all<EvalReturnType>::type

#define DeferredArray2i \
  EIGEN_ENABLE_IFF_NOT_VECTOR(EIGEN_PROTECT_TYPE((Array<Index, 2, 1>)))

// TODO(ygitman): remove extra copy?

EIGEN_STRONG_INLINE EVAL_EXPR_TYPE sortDesc() const
  { EVAL_EXPR_TYPE A = derived(); std::sort(A.begin(), A.end(), std::greater<Scalar>()); return A; }

EIGEN_STRONG_INLINE EVAL_EXPR_TYPE sortAsc() const
  { EVAL_EXPR_TYPE A = derived(); std::sort(A.begin(), A.end(), std::less<Scalar>()); return A; }

template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
EIGEN_DEFERRED_CHECK_ENABLE_IF(IsVectorAtCompileTime, Index)
  argmin() const { Index index; derived().minCoeff(&index); return index; }

template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC DeferredArray2i argmin() const
  { DeferredArray2i xy; derived().minCoeff(&xy[1], &xy[0]); return xy; }

template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
EIGEN_DEFERRED_CHECK_ENABLE_IF(IsVectorAtCompileTime, Index)
  argmax() const { Index index; derived().maxCoeff(&index); return index; }

template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC DeferredArray2i argmax() const
  { DeferredArray2i xy; derived().maxCoeff(&xy[1], &xy[0]); return xy; }

// TODO(ygitman): add 2D and 3D cases
template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
EIGEN_DEFERRED_CHECK_ENABLE_IF(IsVectorAtCompileTime, Index) argany() const {
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

auto clamp(const ChannelType& x, const ChannelType& y) const
  { return derived().max(x).min(y); }

#define _LINEAR_EVAL_TP_ \
   typename Reshaped<const Derived, SizeAtCompileTime, 1>::EvalReturnType

#define LINEAR_EVAL_TP \
   typename internal::remove_const<_LINEAR_EVAL_TP_>::type

EIGEN_STRONG_INLINE_DEVICE_FUNC
Scalar median() const {
  LINEAR_EVAL_TP A = derived().reshaped();
  Index p = A.size() / 2;

  // TODO(ygitman): remove extra copy?

  std::nth_element(A.data(), A.data() + p, A.data() + A.size());
  return A.size()&1 ? A[p] : (A[p] + A.head(p).maxCoeff()) / 2;
}

EIGEN_STRONG_INLINE_DEVICE_FUNC
Scalar middleElement() const {
  LINEAR_EVAL_TP A = derived().reshaped();
  Scalar* v = A.data();
  Index N = A.size();

  // TODO(ygitman): remove extra copy?

  std::nth_element(v, v + (N / 2), v + N);
  return A[(N - 1) / 2];
}

EIGEN_STRONG_INLINE_DEVICE_FUNC
Scalar quantile(float x) const {
  LINEAR_EVAL_TP A = derived().reshaped();
  eigen_assert(0 <= x && x <= 1.0);
  Scalar* v = A.data();
  Index N = A.size();

  // TODO(ygitman): remove extra copy?

  int q_index = (int) (x * (N - 1) + 0.5);
  std::nth_element(v, v + q_index, v + N);
  return A[q_index];
}

#undef /***/ _LINEAR_EVAL_TP_
#undef /***/ LINEAR_EVAL_TP

#undef /***/ DeferredArray2i
#undef /***/ EVAL_EXPR_TYPE
