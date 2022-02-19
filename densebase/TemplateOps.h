/* Copyright (c) Facebook, Inc. and its affiliates. */

#include "./TemplateOps-helper.h"

//! Return slicewise expression along direction
template <int Dimension> EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto dimwise() const EIGEN_REQUIRES(Dimension == 0 || Dimension == 1)
  { return VectorwiseOpExt<const Derived, (Dimension == 1 ? Horizontal : Vertical)>(derived()); }

//! Return slicewise expression along direction
template <int Dimension> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto dimwise() EIGEN_REQUIRES(Dimension == 0 || Dimension == 1)
  { return VectorwiseOpExt<Derived, (Dimension == 1 ? Horizontal : Vertical)>(derived()); }

//! Return idx's slice expression along direction
template <int Dimension> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto sliceAlong(int idx) const EIGEN_REQUIRES(Dimension == 0 || Dimension == 1)
  { return typename CSliceExpr<Dimension>::type(derived(), idx); }

//! Return idx's slice expression along direction
template <int Dimension> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto sliceAlong(int idx) EIGEN_REQUIRES(Dimension == 0 || Dimension == 1)
  { return typename MSliceExpr<Dimension>::type(derived(), idx); }

template <int N> EIGEN_STRONG_INLINE_DEVICE_FUNC auto nested_eval() const EIGEN_REQUIRES(N >= 1)
  { return typename internal::nested_eval<Derived, N>::type(derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC const auto alongInnerDim() const
  { return VectorwiseOpExt<const Derived, IsRowMajor ? Horizontal : Vertical>(derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC const auto alongOuterDim() const
  { return VectorwiseOpExt<const Derived, IsRowMajor ? Vertical : Horizontal>(derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC auto alongInnerDim()
  { return VectorwiseOpExt<Derived, IsRowMajor ? Horizontal : Vertical>(derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC auto alongOuterDim()
  { return VectorwiseOpExt<Derived, IsRowMajor ? Vertical : Horizontal>(derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto innerSubVector(int k) const { return sliceAlong<IsRowMajor ? 0 : 1>(k); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto outerSubVector(int k) const { return sliceAlong<IsRowMajor ? 1 : 0>(k); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
auto innerSubVector(int k) { return sliceAlong<IsRowMajor ? 0 : 1>(k); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
auto outerSubVector(int k) { return sliceAlong<IsRowMajor ? 1 : 0>(k); }

constexpr static bool isRowMajor() { return IsRowMajor ? 1 : 0; }
constexpr static bool isColMajor() { return IsRowMajor ? 0 : 1; }

template <int D> EIGEN_STRONG_INLINE_DEVICE_FUNC
Index sizeAlong() const EIGEN_REQUIRES(D == 0 || D == 1)
  { return D == 0 ? rows() : cols(); }
