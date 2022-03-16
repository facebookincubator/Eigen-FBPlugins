/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:

  template <int Dimension> struct SliceDims {
    static constexpr int kRows = ((Dimension == 1) ? 1 : RowsAtCompileTime);
    static constexpr int kCols = ((Dimension == 1) ? ColsAtCompileTime : 1);
  };

  template <int Dimension> struct CSliceExpr
    { typedef Block<const Derived, SliceDims<Dimension>::kRows, SliceDims<Dimension>::kCols, ((Dimension == 0) ^ IsRowMajor)> type; };

  template <int Dimension> struct MSliceExpr
    { typedef Block<Derived, SliceDims<Dimension>::kRows, SliceDims<Dimension>::kCols, ((Dimension == 0) ^ IsRowMajor)> type; };

 public:

  template <int Direction> EIGEN_STRONG_INLINE_DEVICE_FUNC const auto getVectorwiseOpImpl() const
    { return VectorwiseOp<const Derived, Direction>(derived()); }

  template <int Direction> EIGEN_STRONG_INLINE_DEVICE_FUNC const auto getVectorwiseOp() const
    { return derived().template getVectorwiseOpImpl<Direction>(); }

  template <int Direction> EIGEN_STRONG_INLINE_DEVICE_FUNC auto getVectorwiseOpImpl()
      { return VectorwiseOp<Derived, Direction>(derived()); }

  template <int Direction> EIGEN_STRONG_INLINE_DEVICE_FUNC auto getVectorwiseOp()
    { return derived().template getVectorwiseOpImpl<Direction>(); }
