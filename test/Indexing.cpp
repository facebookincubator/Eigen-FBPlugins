// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#if /**/ EIGEN_VERSION_AT_LEAST(3, 3, 9)

#if !defined(__clang__)
INIT_TEST(INDEXING, Types_F32_AnyMajor)
#else
INIT_TEST(INDEXING, All_Test_Types)
#endif
  EXPECT_APPROX(A(Eigen::all, 2), A("", 2));
  EXPECT_APPROX(A(2, Eigen::all), A(2, ""));

  EXPECT_APPROX(A(Eigen::all, 2), A("", 2));
  EXPECT_APPROX(A(2, Eigen::all), A(2, ""));

  EXPECT_APPROX((v[Eigen::cropPads<1,0>()]),
                v.tail(v.size() - 1));
  EXPECT_APPROX(v, v[Eigen::all]);
}

#endif // EIGEN_VERSION_AT_LEAST(3, 3, 9)
