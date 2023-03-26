/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_IMPORT_CHANNELTYPE(Scalar) /****/
EIGEN_IMPORT_NUMCHANNELS(Scalar) /****/

#ifdef EIGEN_WITH_OPENCV
#  include "./plainobjectbase/OpenCV.h"
#endif

#ifdef EIGEN_WITH_IDEEP
#  include "./plainobjectbase/IDeep.h"
#endif

#ifdef EIGEN_WITH_TORCH
#  include "./plainobjectbase/Torch.h"
#endif

#include "./plainobjectbase/Stats.h"

#ifdef EIGEN_PLAINOBJECT_BASE_EXTRA_PLUGIN
#  include EIGEN_PLAINOBJECT_BASE_EXTRA_PLUGIN
#endif
