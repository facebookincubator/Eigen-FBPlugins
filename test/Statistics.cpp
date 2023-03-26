// Copyright (c) Facebook, Inc. and its affiliates.

#define EIGEN_DISABLE_MULTICHANNEL_ARRAYS
#include "CommonHeader.h"  // Common definitions

INIT_TEST(STATISTICS_CONST_RVALUE, Types_2D_AnyMajor)
  const auto& x = v.head(9);
  const auto& y = v.head(8);
  auto m1 = x.eval().middleElement();
  auto m2 = y.eval().median();

  const auto p = x.sortAsc();
  const auto q = y.sortAsc();

  for (int i = 0; i < y.size(); ++i) {
    EXPECT_TRUE(y.eval().quantile(i / 7.0f) == q[i]);
  }

  EXPECT_TRUE(m2 == (q[3] + q[4]) / 2);
  EXPECT_TRUE(m1 == p[4]);
}

INIT_TEST(STATISTICS_RVALUE, Types_2D_AnyMajor)
  auto x = v.head(9).eval();
  auto p = x.sortAsc();
  auto y = v.head(8).eval();
  auto q = y.sortAsc();

  auto m1 = std::move(x).middleElement();
  auto m2 = std::move(y).median();

  for (int i = 0; i < q.size(); ++i) {
    auto vals = v.head(8).eval();
    EXPECT_TRUE(std::move(vals).quantile(i / (q.size() - 1.0f)) == q[i]);
  }

  EXPECT_TRUE(m2 == (q[3] + q[4]) / 2);
  EXPECT_TRUE(m1 == p[4]);
}
