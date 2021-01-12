/* Copyright (c) Facebook, Inc. and its affiliates. */

}  // namespace internal

template <typename ExprTp>
struct CellwiseOp {
#define REDUX_FUNC(funcname) \
  internal::scalar_##funcname##_op<typename ExprTp::Scalar, typename ExprTp::Scalar>()

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  explicit CellwiseOp(typename internal::ultimate_ref_selector<ExprTp>::type exprArg)
    : nestedXpr(exprArg) {}

  typename internal::ultimate_ref_selector<ExprTp>::type nestedXpr;

  typedef typename NumTraits<typename ExprTp::Scalar>::Real RealT;

  typedef typename internal::remove_all<ExprTp>::type CleanExprTp;

  template <class BinaryOp> EIGEN_STRONG_INLINE_DEVICE_FUNC
  typename ExprTp::Scalar redux(const BinaryOp& fn) const
    { return nestedXpr.DenseBase<CleanExprTp>::redux(fn); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  typename ExprTp::Scalar prod() const
    { return redux(REDUX_FUNC(product)); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  typename ExprTp::Scalar mean() const
    { return sum() / nestedXpr.size(); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  typename ExprTp::Scalar minCoeff() const
    { return redux(REDUX_FUNC(min)); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  typename ExprTp::Scalar maxCoeff() const
    { return redux(REDUX_FUNC(max)); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  typename ExprTp::Scalar sum() const
    { return redux(REDUX_FUNC(sum)); }

#undef /***/ REDUX_FUNC

// TODO(ygitman): implement hnormalized
// TODO(ygitman): implement homogeneous
// TODO(ygitman): implement squaredNorm
// TODO(ygitman): implement stableNorm
// TODO(ygitman): implement normalized
// TODO(ygitman): implement operator+=
// TODO(ygitman): implement operator-=
// TODO(ygitman): implement operator*=
// TODO(ygitman): implement operator/=
// TODO(ygitman): implement operator+
// TODO(ygitman): implement operator-
// TODO(ygitman): implement operator*
// TODO(ygitman): implement operator/
// TODO(ygitman): implement operator=
// TODO(ygitman): implement normalize
// TODO(ygitman): implement hypotNorm
// TODO(ygitman): implement blueNorm
// TODO(ygitman): implement lpNorm
// TODO(ygitman): implement count
// TODO(ygitman): implement cross
// TODO(ygitman): implement norm
// TODO(ygitman): implement all
// TODO(ygitman): implement any
};

namespace /***/ internal {
