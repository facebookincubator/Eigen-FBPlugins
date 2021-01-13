/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Tp> EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
explicit Array(const Array<Tp, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& arg)
  : Array(arg.template cast<Scalar>()) {}
