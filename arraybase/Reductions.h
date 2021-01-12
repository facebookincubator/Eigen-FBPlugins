/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC
bool all() const {
  typedef internal::evaluator<Derived> Evaluator;
  Evaluator evaluator(derived());

  enum { unroll = SizeAtCompileTime != Dynamic && SizeAtCompileTime * (Evaluator::CoeffReadCost + NumTraits<Scalar>::AddCost) <= EIGEN_UNROLLING_LIMIT };
  enum { N = unroll ? SizeAtCompileTime : Dynamic, M = (IsRowMajor ? ColsAtCompileTime : RowsAtCompileTime) };
  if (unroll) { return internal::all_unroller_nc<Evaluator, N, M>::run(evaluator); }

  for (Index i = 0; i < derived().outerSize(); ++i) for(Index j = 0; j < derived().innerSize(); ++j)
    if (!numext::all(evaluator.coeff(IsRowMajor ? i : j, IsRowMajor ? j : i)))
      return false;

#ifdef /****/ EIGEN_EXTRA_SAFETY
  EIGEN_STATIC_ASSERT(internal::is_same<ChannelType, bool>::value, THIS_TYPE_IS_NOT_SUPPORTED);
#endif /**/// EIGEN_EXTRA_SAFETY

  return true;
}

EIGEN_STRONG_INLINE_DEVICE_FUNC
bool any() const {
  typedef internal::evaluator<Derived> Evaluator;
  Evaluator evaluator(derived());

  enum { K = (IsRowMajor ? ColsAtCompileTime : RowsAtCompileTime) };
  enum { unroll = SizeAtCompileTime != Dynamic && SizeAtCompileTime * (Evaluator::CoeffReadCost + NumTraits<Scalar>::AddCost) <= EIGEN_UNROLLING_LIMIT };
  enum { N = unroll ? SizeAtCompileTime : Dynamic, M = (IsRowMajor ? ColsAtCompileTime : RowsAtCompileTime) };
  if (unroll) { return internal::any_unroller_nc<Evaluator, N, M>::run(evaluator); }

  for (Index i = 0; i < derived().outerSize(); ++i) for(Index j = 0; j < derived().innerSize(); ++j)
    if (numext::any(evaluator.coeff(IsRowMajor ? i : j, IsRowMajor ? j : i)))
      return true;

#ifdef /****/ EIGEN_EXTRA_SAFETY
  EIGEN_STATIC_ASSERT(internal::is_same<ChannelType, bool>::value, THIS_TYPE_IS_NOT_SUPPORTED);
#endif /**/// EIGEN_EXTRA_SAFETY

  return false;
}
