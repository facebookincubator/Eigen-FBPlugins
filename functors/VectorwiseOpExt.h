/* Copyright (c) Facebook, Inc. and its affiliates. */

}  // namespace internal

template<typename ExpressionType, int D>
struct VectorwiseOpExt : VectorwiseOp<ExpressionType, D> {
  typedef typename ExpressionType::PlainObject EvalTp;
  typedef typename EvalTp::RowXpr::PlainObject RowXpr;
  typedef typename EvalTp::ColXpr::PlainObject ColXpr;

  typedef VectorwiseOp<ExpressionType, D> Base;

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  ExpressionType& operator =(ExpressionType& x)
    { return Base::operator =(x); }

  explicit EIGEN_STRONG_INLINE_DEVICE_FUNC
  VectorwiseOpExt(ExpressionType& x)
    : Base(x) {}

  typedef typename EvalTp::Scalar Scalar;
  enum { X = (D != Horizontal) };
  enum { Y = (D == Horizontal) };

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  auto quantile(float x) const {
    auto A = this->_expression();
    const Index h = A.template sizeAlong<X>();
    const Index w = A.template sizeAlong<Y>();
    int qt_index = round(x * (w - 1));

    eigen_assert(0 <= x && x <= 1.0);

    const Index n = X ? 1 : A.rows();
    const Index m = X ? A.cols() : 1;

    EIGEN_META_IF(X, RowXpr, ColXpr) result(n, m);

    for (int i = 0; i < h; ++i) {
      auto v = A.template sliceAlong<Y>(i).eval();
      Scalar* dt = v.data();

      std::nth_element(dt, dt + qt_index, dt + w);
      result[i] = v[qt_index];
    }

    return result;
  }
};

namespace internal {
