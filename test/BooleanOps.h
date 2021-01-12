// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#define INIT_TEST_BY_TYPE_GROUP(X, ...)                          \
  INIT_TEST(BOOL_OPS##X, __VA_ARGS__)                            \
    EXPECT_TRUE((((A >= A.mean()) && (A < A.mean())).isZero())); \
    EXPECT_TRUE((((A >= A.mean()) || (A < A.mean())).isOnes())); \
    EXPECT_TRUE((!decltype(A)::Zero(A.rows(), A.cols())          \
                 .template cast<bool>()).all());                 \
  }
