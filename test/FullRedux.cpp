// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

INIT_TEST(FULL_REDUX_Y, Types_F_AnyMajor)
  int N = static_cast<int>(A.rows() * A.cols() * A.channels());
  Eigen::Map<Eigen::Array<Tp, Eigen::Dynamic, 1>> M((Tp*) A.data(), N);
  // EXPECT_NEAR(A.template lpNorm<1>(), M.template lpNorm<1>(), 1e-2);
  // EXPECT_NEAR(A.template lpNorm<2>(), M.template lpNorm<2>(), 1e-2);
  // EXPECT_NEAR(A.template lpNorm<3>(), M.template lpNorm<3>(), 1e-2);
  EXPECT_NEAR(A.squaredNorm(), M.squaredNorm(), 1e-2);
  EXPECT_NEAR(A.maxCoeff(), M.maxCoeff(), 1e-2);
  EXPECT_NEAR(A.minCoeff(), M.minCoeff(), 1e-2);

  EXPECT_NEAR(A.norm(), M.norm(), 1e-2);
  EXPECT_NEAR(A.mean(), M.mean(), 1e-2);
  EXPECT_NEAR(A.prod(), M.prod(), 1e-2);
  EXPECT_NEAR(A.sum(), M.sum(), 1e-2);
}

INIT_TEST(FULL_REDUX_X, Types_I_AnyMajor)
  int N = static_cast<int>(A.rows() * A.cols() * A.channels());
  Eigen::Map<Eigen::Array<Tp, Eigen::Dynamic, 1>> M((Tp*) A.data(), N);
  EXPECT_EQ(A.squaredNorm(), M.squaredNorm());
  EXPECT_EQ(A.maxCoeff(), M.maxCoeff());
  EXPECT_EQ(A.minCoeff(), M.minCoeff());

  EXPECT_EQ(A.mean(), M.mean());
  EXPECT_EQ(A.sum(), M.sum());
}
