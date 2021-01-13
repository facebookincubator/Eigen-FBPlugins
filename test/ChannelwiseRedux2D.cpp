// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#if !defined(__clang__)
INIT_TEST(CHANNELWISE_REDUX_2D, Types_2D_F32_AnyMajor)
#else
INIT_TEST(CHANNELWISE_REDUX_2D, Types_2D_AnyMajor)
#endif
  EXPECT_APPROX(A.channelwise().squaredNorm(), A.square());
  EXPECT_APPROX((A != 0).template cast<Index>(),
                A.channelwise().count());

  EXPECT_APPROX(A.channelwise().prod(), A);
  EXPECT_APPROX(A.channelwise().norm(), A);
  EXPECT_APPROX(A.channelwise().mean(), A);
  EXPECT_APPROX(A.channelwise().sum(), A);

  EXPECT_APPROX(A.channelwise().maxCoeff(), A);
  EXPECT_APPROX(A.channelwise().minCoeff(), A);

  EXPECT_APPROX(A.channelwise().all(), A != 0);
  EXPECT_APPROX(A.channelwise().any(), A != 0);
}
