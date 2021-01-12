/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:
  template <int Dimension> struct SliceDims {
    enum {
      kRows = ((Dimension == 1) ? 1 : RowsAtCompileTime),
      kCols = ((Dimension == 1) ? ColsAtCompileTime : 1)
    };
  };

  enum { InnerDimension = IsRowMajor ? 1 : 0 };
  enum { OuterDimension = IsRowMajor ? 0 : 1 };

  enum { IsColMajor = IsRowMajor ? 0 : 1 };

  template <int Dimension> struct MSliceExpr {
    enum { kRows = SliceDims<Dimension>::kRows };
    enum { kCols = SliceDims<Dimension>::kCols };
    enum { x = ((Dimension == 0) ^ IsRowMajor) };
    typedef Block</* */ Derived, kRows, kCols, x> type;
  };

  template <int Dimension> struct CSliceExpr {
    enum { kRows = SliceDims<Dimension>::kRows };
    enum { kCols = SliceDims<Dimension>::kCols };
    enum { x = ((Dimension == 0) ^ IsRowMajor) };
    typedef Block<const Derived, kRows, kCols, x> type;
  };

 public:
  //! Return idx's slice expression along direction
  template <int Dimension> EIGEN_STRONG_INLINE_DEVICE_FUNC
  typename CSliceExpr<Dimension>::type sliceAlong(int idx) const
    { return typename CSliceExpr<Dimension>::type(derived(), idx); }

  //! Return idx's slice expression along direction
  template <int Dimension> EIGEN_STRONG_INLINE_DEVICE_FUNC
  typename MSliceExpr<Dimension>::type sliceAlong(int idx) /***/
    { return typename MSliceExpr<Dimension>::type(derived(), idx); }

  template <int D> EIGEN_STRONG_INLINE_DEVICE_FUNC
  Index sizeAlong() const { return D == 0 ? rows() : cols(); }

#define /**/ DIRECTION (Dimension == 1 ? Horizontal : Vertical)

  //! Return slicewise expression along direction
  template <int Dimension> EIGEN_STRONG_INLINE_DEVICE_FUNC
  const VectorwiseOpExt<const Derived, DIRECTION> dimwise() const
    { return VectorwiseOpExt<const Derived, DIRECTION>(derived()); }

  //! Return slicewise expression along direction
  template <int Dimension> EIGEN_STRONG_INLINE_DEVICE_FUNC
  /* */ VectorwiseOpExt</* */ Derived, DIRECTION> dimwise() /*(*/
    { return VectorwiseOpExt</* */ Derived, DIRECTION>(derived()); }

#undef /***/ DIRECTION /*Dimension == 1 ? Horizontal : Vertical*/

  enum { InnerDirection = IsRowMajor ? Horizontal : Vertical };
  enum { OuterDirection = IsRowMajor ? Vertical : Horizontal };

   constexpr static bool isRowMajor() { return IsRowMajor; }
   constexpr static bool isColMajor() { return IsColMajor; }

  template <int N> EIGEN_STRONG_INLINE_DEVICE_FUNC auto nested_eval() const
    { return typename internal::nested_eval<Derived, N>::type(derived()); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  const VectorwiseOpExt<const Derived, InnerDirection> alongInnerDim() const
    { return VectorwiseOpExt<const Derived, InnerDirection>(derived()); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  /***/ VectorwiseOpExt</***/ Derived, InnerDirection> alongInnerDim() /***/
    { return VectorwiseOpExt</***/ Derived, InnerDirection>(derived()); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  const VectorwiseOpExt<const Derived, OuterDirection> alongOuterDim() const
    { return VectorwiseOpExt<const Derived, OuterDirection>(derived()); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  /***/ VectorwiseOpExt</***/ Derived, OuterDirection> alongOuterDim() /***/
    { return VectorwiseOpExt</***/ Derived, OuterDirection>(derived()); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  /***/ typename MSliceExpr<IsRowMajor>::type outerSubVector(int k) /***/
    { return sliceAlong<IsRowMajor>(k); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  const typename CSliceExpr<IsRowMajor>::type outerSubVector(int k) const
    { return sliceAlong<IsRowMajor>(k); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  /***/ typename MSliceExpr<IsColMajor>::type innerSubVector(int k) /***/
    { return sliceAlong<IsColMajor>(k); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  const typename CSliceExpr<IsColMajor>::type innerSubVector(int k) const
    { return sliceAlong<IsColMajor == 0>(k); }
