/* Copyright (c) Facebook, Inc. and its affiliates. */

#define ITRAITS/**/internal::traits<Matrix>

template <typename Tp> EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
explicit Matrix(const Matrix<Tp, ITRAITS::RowsAtCompileTime, ITRAITS::ColsAtCompileTime, ITRAITS::Options,
                                 ITRAITS::MaxRowsAtCompileTime, ITRAITS::MaxColsAtCompileTime>& arg)
  : Matrix(arg.template cast<Scalar>()) {}

#undef ITRAITS  // internal::traits<Matrix>
