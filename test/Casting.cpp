// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

INIT_TEST(CASTING, All_Test_Types)
  const auto Af = A.template cast<float>() + 0.1f;
  EXPECT_TRUE(Af.channels() == A.channels());
  EXPECT_TRUE(Af.rows() == A.rows());
  EXPECT_TRUE(Af.cols() == A.cols());
}
