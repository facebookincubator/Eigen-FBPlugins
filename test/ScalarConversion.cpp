// Copyright (c) Facebook, Inc. and its affiliates.

#define EIGEN_DISABLE_MULTICHANNEL_ARRAYS
#include "CommonHeader.h"  // Common definitions

INIT_TEST(SCALAR_CONVERSION, Types_2D_ColMajor)
  const Scalar q = v.matrix().transpose() * v.matrix();
  EXPECT_TRUE((q * A).isApprox((A * A).sum() * A));

  const Scalar p = A.template block<1, 1>(0, 0);
  EXPECT_TRUE((p * A).isApprox(A(0, 0) * A));
}
