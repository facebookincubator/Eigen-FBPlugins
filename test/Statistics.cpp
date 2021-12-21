// Copyright (c) Facebook, Inc. and its affiliates.

#define EIGEN_DISABLE_MULTICHANNEL_ARRAYS
#include "CommonHeader.h"  // Common definitions

INIT_TEST(STATISTICS, Types_2D_AnyMajor)
  const auto& x = v.head(9);
  const auto& y = v.head(8);
  auto m1 = x.middleElement();
  auto m2 = y.median();

  const auto zx = x.sortAsc();
  const auto zy = y.sortAsc();

  EXPECT_TRUE(m2 == (zy[3] + zy[4]) / 2);
  EXPECT_TRUE(m1 == zx[4]);

  for (int i = 0; i < y.size(); ++i) {
    EXPECT_TRUE(y.quantile(i / 7.0f) == zy[i]);
  }
}
