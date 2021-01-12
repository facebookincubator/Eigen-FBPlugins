/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Tp> EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
explicit Matrix(const Matrix<Tp, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& arg)
  : Matrix(arg.template cast<Scalar>()) {}
