/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC const VectorwiseOpExt<const Derived, Horizontal> rowwise() const
  { return VectorwiseOpExt<const Derived, Horizontal>(derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC const VectorwiseOpExt<const Derived, Vertical> colwise() const
  { return VectorwiseOpExt<const Derived, Vertical>(derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC VectorwiseOpExt<Derived, Horizontal> rowwise()
  { return VectorwiseOpExt<Derived, Horizontal>(derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC VectorwiseOpExt<Derived, Vertical> colwise()
  { return VectorwiseOpExt<Derived, Vertical>(derived()); }

typedef typename Base::RowXpr RowXpr;
typedef typename Base::ColXpr ColXpr;
