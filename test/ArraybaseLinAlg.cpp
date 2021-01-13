// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

INIT_TEST(ARRAYBASE_LINALG_Y, Types_2D_F_ColMajor)
  EXPECT_NEAR(v.template lpNorm<2>(), v.matrix().template lpNorm<2>(), 1e-2f);
  EXPECT_NEAR(v.template lpNorm<3>(), v.matrix().template lpNorm<3>(), 1e-2f);
  EXPECT_NEAR(v.template lpNorm<1>(), v.matrix().template lpNorm<1>(), 1e-2f);
  EXPECT_APPROX(v.normalized(), v.matrix().normalized().array());
  EXPECT_NEAR(v.squaredNorm(), v.matrix().squaredNorm(), 1e-2f);
  EXPECT_NEAR(v.norm(), v.matrix().norm(), 1e-2f);
}

INIT_TEST(ARRAYBASE_LINALG_X, Types_2D_L_ColMajor)
  EXPECT_TRUE(v.template lpNorm<1>() == v.matrix().template lpNorm<1>());
  EXPECT_TRUE(v.squaredNorm() == v.matrix().squaredNorm());
}
