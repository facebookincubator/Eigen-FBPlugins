// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

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
