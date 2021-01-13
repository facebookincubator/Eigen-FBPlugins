/* Copyright (c) Facebook, Inc. and its affiliates. */

#include "./ForwardDeclarations.h"
#include "./util/Macros.h"

#include "./util/TypeTraits.h"
#include "./util/WrapScalar.h"
#include "./util/Helpers.h"

#include "./functors/ChannelwiseOps.h"
#include "./functors/VectorwiseOpExt.h"
#include "./functors/StlExtensions.h"
#include "./functors/CellwiseOps.h"
#include "./functors/Reductions.h"
#include "./functors/BinaryOps.h"
#include "./functors/ScalarOps.h"
#include "./functors/UnaryOps.h"
#include "./functors/Indexing.h"
#include "./functors/TypeDefs.h"
#include "./functors/Select.h"
#include "./functors/Expr2d.h"
#include "./functors/IO.h"

#include "./ArrayBaseNC.h"

#ifdef /**/ EIGEN_EXTRA_SAFETY
#  include "./functors/ExtraSafety.h"
#endif   // EIGEN_EXTRA_SAFETY

#ifdef /**/ EIGEN_WITH_OPENCV
#  include "./functors/OpenCV.h"
#endif   // EIGEN_WITH_OPENCV

#ifdef /**/ EIGEN_FUNCTORS_EXTRA_PLUGIN
#  include EIGEN_FUNCTORS_EXTRA_PLUGIN
#endif   // EIGEN_FUNCTORS_EXTRA_PLUGIN
