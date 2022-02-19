/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:

  template <int Dimension> struct SliceDims
    { enum { kRows = ((Dimension == 1) ? 1 : RowsAtCompileTime), kCols = ((Dimension == 1) ? ColsAtCompileTime : 1) }; };

  template <int Dimension> struct CSliceExpr
    { typedef Block<const Derived, SliceDims<Dimension>::kRows, SliceDims<Dimension>::kCols, ((Dimension == 0) ^ IsRowMajor)> type; };

  template <int Dimension> struct MSliceExpr
    { typedef Block<Derived, SliceDims<Dimension>::kRows, SliceDims<Dimension>::kCols, ((Dimension == 0) ^ IsRowMajor)> type; };

 public:
