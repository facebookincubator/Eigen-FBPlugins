/* Copyright (c) Facebook, Inc. and its affiliates. */

constexpr static Index channels()
  { return internal::wrap_scalar<Scalar>::NumChannels; }

enum { IsRowMajor = (Flags & RowMajor) };

EIGEN_IMPORT_CHANNELTYPE(Scalar)
EIGEN_IMPORT_NUMCHANNELS(Scalar)

#include "./arraybase/ChannelwiseOps.h"
#include "./arraybase/VectorwiseOpExt.h"
#include "./arraybase/CellwiseOps.h"
#include "./arraybase/Reductions.h"
#include "./arraybase/ScalarOps.h"
#include "./arraybase/BinaryOps.h"
#include "./arraybase/UnaryOps.h"
#include "./arraybase/Reshaped.h"
#include "./arraybase/Indexing.h"
#include "./arraybase/LinAlg.h"

#ifdef /**/ EIGEN_WITH_OPENCV
# include "./arraybase/OpenCV.h"
#endif   // EIGEN_WITH_OPENCV

#ifdef /**/ EIGEN_ARRAYBASE_EXTRA_PLUGIN
#  include EIGEN_ARRAYBASE_EXTRA_PLUGIN
#endif   // EIGEN_ARRAYBASE_EXTRA_PLUGIN
