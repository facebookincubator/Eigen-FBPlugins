// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#if /**/ EIGEN_VERSION_AT_LEAST(3, 3, 9)

INIT_TEST(SUBSAMPLE, All_Test_Types)
  int a = rand() % (A.rows() / 2 - 1) + 1;
  int b = rand() % (A.cols() / 2 - 1) + 1;

  using Eigen::indexing::last;
  using Eigen::subsample;
  using Eigen::seq;
  using Eigen::fix;

  const auto& B = A(subsample<2>(), subsample(b));
  EXPECT_APPROX(B, A(seq(0, last, fix<2>), seq(0, last, b)));

  const auto& C = A(subsample(a), subsample<2>());
  EXPECT_APPROX(C, A(seq(0, last, a), seq(0, last, fix<2>)));
}

#endif // EIGEN_VERSION_AT_LEAST(3, 3, 9)
