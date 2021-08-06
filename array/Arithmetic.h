/* Copyright (c) Facebook, Inc. and its affiliates. */

#define ITRAITS/**/internal::traits<Array>

template <typename Tp> EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
explicit Array(const Array<Tp, ITRAITS::RowsAtCompileTime, ITRAITS::ColsAtCompileTime, ITRAITS::Options,
                               ITRAITS::MaxRowsAtCompileTime, ITRAITS::MaxColsAtCompileTime>& arg)
  : Array(arg.template cast<Scalar>()) {}

#undef ITRAITS  // internal::traits<Array>
