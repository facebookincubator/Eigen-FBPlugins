/* Copyright (c) Facebook, Inc. and its affiliates. */

template <int Order = ColMajor, typename NRowsType, typename NColsType>
EIGEN_STRONG_INLINE_DEVICE_FUNC const auto reshaped2d(NRowsType nRows, NColsType nCols) const
  { return this->template reshaped<Order>(nRows, nCols); }

template <int Order = ColMajor, typename NRowsType, typename NColsType>
EIGEN_STRONG_INLINE_DEVICE_FUNC auto reshaped2d(NRowsType nRows, NColsType nCols)
  { return this->template reshaped<Order>(nRows, nCols); }

template <int Order = ColMajor>
EIGEN_STRONG_INLINE_DEVICE_FUNC const auto reshaped2d() const
  { return this->template reshaped<Order>(); }

template <int Order = ColMajor>
EIGEN_STRONG_INLINE_DEVICE_FUNC auto reshaped2d()
  { return this->template reshaped<Order>(); }
