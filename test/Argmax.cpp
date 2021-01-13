// Copyright (c) Facebook, Inc. and its affiliates.

#define EIGEN_DISABLE_MULTICHANNEL_ARRAYS
#include "CommonHeader.h"

INIT_TEST(ARGMAX, Types_2D_AnyMajor)
#ifdef/**/EIGEN_HAS_CXX17
  auto [x, y] = (A.argmin() + 1l).asTuple();
  EXPECT_TRUE((A(y - 1, x - 1) <= A).all());

  auto [x2, y2] = A.argmax();
  EXPECT_TRUE((A(y2, x2) >= A).all());
#endif // EIGEN_HAS_CXX17

  EXPECT_TRUE((v(v.argmin()) <= A).all());
  EXPECT_TRUE((v(v.argmax()) >= A).all());
}
