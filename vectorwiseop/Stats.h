/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Tp, typename Func>
EIGEN_STRONG_INLINE_DEVICE_FUNC const auto partialReduxHelper(const Tp& arg, const Func& fn) const
  { return PartialReduxExpr<const Tp, Func, Direction>(arg, fn); }

EIGEN_STRONG_INLINE_DEVICE_FUNC const auto quantile(float x) const {
  const auto& fn = [x](const auto& slice) EIGEN_LAMBDA_INLINE
    { return slice.copy().quantile(x); };

  typedef decltype(fn(this->_expression().template sliceAlong<Direction>(std::declval<Index>()))) T;
  return partialReduxHelper(this->_expression(), internal::make_redux_functor<100, 0, T>(fn));
}
