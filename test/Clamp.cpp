// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

INIT_TEST(CLAMP, All_Test_Types)
  auto minv = A.minCoeff();
  auto maxv = A.maxCoeff();
  auto x = minv + 1 * (maxv - minv) / 3;
  auto y = minv + 2 * (maxv - minv) / 3;
  EXPECT_APPROX(A.max(x).min(y),
      A.clamp(x, y));
}
