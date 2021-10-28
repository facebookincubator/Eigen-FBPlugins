// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#if 0
// TODO(ygitman): Eigen master is broken, reenable once fixed

#if !defined(__clang__)
// INIT_TEST(CLAMP, Types_F32_AnyMajor)
INIT_TEST(CLAMP, Types_F32_AnyMajor)
#else
INIT_TEST(CLAMP, All_Test_Types)
#endif
  auto minv = A.minCoeff();
  auto maxv = A.maxCoeff();
  auto x = minv + 1 * (maxv - minv) / 3;
  auto y = minv + 2 * (maxv - minv) / 3;
  EXPECT_APPROX(A.max(x).min(y),
      A.clamp(x, y));
}

#endif
