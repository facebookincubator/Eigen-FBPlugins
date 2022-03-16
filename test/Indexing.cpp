// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#if !defined(__clang__)
INIT_TEST(INDEXING, Types_F32_AnyMajor)
#else
INIT_TEST(INDEXING, All_Test_Types)
#endif
  EXPECT_APPROX((v[Eigen::cropPads<1,0>()]), v.tail(v.size() - 1));
  EXPECT_APPROX(v, v[Eigen::indexing::all]);
}
