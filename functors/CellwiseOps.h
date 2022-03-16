/* Copyright (c) Facebook, Inc. and its affiliates. */

}  // namespace internal

template <typename XprTp>
struct CellwiseOp {
  EIGEN_STRONG_INLINE_DEVICE_FUNC auto minCoeff() const
    { return redux([](const auto& x, const auto& y) EIGEN_LAMBDA_INLINE { return internal::ops::evaluate(internal::ops::min(x, y)); }); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC auto maxCoeff() const
    { return redux([](const auto& x, const auto& y) EIGEN_LAMBDA_INLINE { return internal::ops::evaluate(internal::ops::max(x, y)); }); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC auto prod() const
    { return redux([](const auto& x, const auto& y) -> std::decay_t<decltype(x)> { return internal::ops::evaluate(x * y); }); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC auto sum() const
    { return redux([](const auto& x, const auto& y) -> std::decay_t<decltype(x)> { return internal::ops::evaluate(x + y); }); }

  template <class BinaryOp> EIGEN_STRONG_INLINE_DEVICE_FUNC auto redux(const BinaryOp& fn) const
    { return nestedXpr.DenseBase<std::decay_t<XprTp>>::redux(fn); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC auto mean() const { return sum() / nestedXpr.size(); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  explicit CellwiseOp(typename internal::ultimate_ref_selector<XprTp>::type exprArg)
    : nestedXpr(exprArg) {}

 private:
  typename internal::ultimate_ref_selector<XprTp>::type nestedXpr;

  // TODO(ygitman): add other functions
};

namespace internal {
