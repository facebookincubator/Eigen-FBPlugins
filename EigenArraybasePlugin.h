/* Copyright (c) Facebook, Inc. and its affiliates. */

constexpr static Index channels()
  { return internal::wrap_scalar<Scalar>::NumChannels; }

enum { IsRowMajor = ((int) Flags & RowMajor) };

EIGEN_IMPORT_CHANNELTYPE(Scalar)
EIGEN_IMPORT_NUMCHANNELS(Scalar)

#if !EIGEN_VERSION_AT_LEAST(3, 4, 9)
  template <int Direction> EIGEN_STRONG_INLINE_DEVICE_FUNC auto getVectorwiseOpImpl() const
    { return VectorwiseOpProxy<const Derived, Direction>(derived()); }
#endif

EIGEN_STRONG_INLINE_DEVICE_FUNC const auto rowwise() const
  { return derived().template getVectorwiseOpImpl<Horizontal>(); }

EIGEN_STRONG_INLINE_DEVICE_FUNC auto rowwise()
  { return derived().template getVectorwiseOpImpl<Horizontal>(); }

EIGEN_STRONG_INLINE_DEVICE_FUNC const auto colwise() const
  { return derived().template getVectorwiseOpImpl<Vertical>(); }

EIGEN_STRONG_INLINE_DEVICE_FUNC auto colwise()
  { return derived().template getVectorwiseOpImpl<Vertical>(); }

#include "./arraybase/ChannelwiseOps.h"
#include "./arraybase/CellwiseOps.h"
#include "./arraybase/Reshaped.h"
#include "./arraybase/LinAlg.h"

#ifdef EIGEN_WITH_OPENCV
# include "./arraybase/OpenCV.h"
#endif

#ifdef EIGEN_ARRAYBASE_EXTRA_PLUGIN
#  include EIGEN_ARRAYBASE_EXTRA_PLUGIN
#endif
