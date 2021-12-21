// Copyright (c) Facebook, Inc. and its affiliates.

#define EIGEN_DISABLE_MULTICHANNEL_ARRAYS
#include "CommonHeader.h"

INIT_TEST(NARY_OPS, Types_2D_AnyMajor)
  TypeParam X = TypeParam::Random(4, 7);
  TypeParam Y = TypeParam::Random(4, 7);
  TypeParam Z = TypeParam::Random(4, 7);
  EXPECT_APPROX(Eigen::min(X, Y, Z),
                X.min(Y).min(Z));
  EXPECT_APPROX(Eigen::max(X, Y, Z),
                X.max(Y).max(Z));
}
