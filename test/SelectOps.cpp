// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#if !defined(__clang__)
INIT_TEST(SELECT_OPS, Types_F32_AnyMajor)
#else
INIT_TEST(SELECT_OPS, All_Test_Types)
#endif
  auto c = static_cast<Tp>(A.mean());
  const auto& p1 = A * (A >= c).template cast<Tp>();
  const auto& p2 = A * (A < c).template cast<Tp>();
  EXPECT_APPROX((A >= c).select(A, -A), p1 - p2);
  EXPECT_APPROX((A >= c).select(A, 0), p1);
  EXPECT_APPROX((A >= c).select(0, A), p2);
}
