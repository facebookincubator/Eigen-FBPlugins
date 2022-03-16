/* Copyright (c) Facebook, Inc. and its affiliates. */

#include "./ForwardDeclarations.h"
#include "./util/Macros.h"

#ifdef __cpp_concepts
#  include "./util/Concepts.h"
#endif

#include "./util/TypeTraits.h"
#include "./util/WrapScalar.h"

#include "./util/MetaFunctors.h"
#include "./util/Helpers.h"

#include "./functors/GlobalFunctions.h"
#include "./functors/VectorwiseOpNC.h"

#include "./functors/ChannelwiseOps.h"
#include "./functors/StlExtensions.h"
#include "./functors/CellwiseOps.h"
#include "./functors/ScalarOps.h"
#include "./functors/Indexing.h"
#include "./functors/TypeDefs.h"
#include "./functors/NaryOps.h"
#include "./functors/IO.h"

#ifdef EIGEN_WITH_OPENCV
#  include "./functors/OpenCV.h"
#endif

#ifdef EIGEN_WITH_TORCH
#  include "./functors/Torch.h"
#endif

#include "./functors/Expr2d.h"
#include "./ArrayBaseNC.h"

#ifdef EIGEN_FUNCTORS_EXTRA_PLUGIN
#  include EIGEN_FUNCTORS_EXTRA_PLUGIN
#endif
