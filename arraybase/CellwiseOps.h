/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC const CellwiseOp<const Derived> cellwise() const
  { return CellwiseOp<const Derived>(this->derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC CellwiseOp<Derived> cellwise() /***/
  { return CellwiseOp<Derived>(this->derived()); }
