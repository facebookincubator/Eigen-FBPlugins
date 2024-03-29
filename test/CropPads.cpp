// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#if !defined(__clang__)
INIT_TEST(CROP_PADS, Types_F32_AnyMajor)
#else
INIT_TEST(CROP_PADS, All_Test_Types)
#endif
  int a = rand() % (A.rows() - 2);
  int b = rand() % (A.cols() - 2);

  using Eigen::cropPads;

  int c = rand() % (A.rows() - a - 1);
  int d = rand() % (A.cols() - b - 1);

  const auto& B = A(cropPads<0, 1>(), cropPads(b, d));
  const auto& C = A(cropPads(a, c), cropPads<2, 0>());

  EXPECT_APPROX(B, A.block(0, b, 3, 7 - (b + d)));
  EXPECT_APPROX(C, A.block(a, 2, 4 - (a + c), 5));
}
