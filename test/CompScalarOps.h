// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#define INIT_TEST_BY_TYPE_GROUP(ConstantType, X, ...)                      \
  INIT_TEST(COMP_SCALAR_OPS_##X, __VA_ARGS__)                              \
    auto constant = [N = A.rows(), M = A.cols()] (ConstantType val)        \
      { return TypeParam::Constant(N, M, static_cast<Tp>(val)); };         \
    ConstantType cnt = static_cast<ConstantType>(A.mean());                \
                                                     \
    EXPECT_APPROX(constant(cnt) == A, cnt == A);     \
    EXPECT_APPROX(constant(cnt) != A, cnt != A);     \
                                                     \
    EXPECT_APPROX(A == constant(cnt), A == cnt);     \
    EXPECT_APPROX(A != constant(cnt), A != cnt);     \
                                                     \
    EXPECT_APPROX(constant(cnt) <= A, cnt <= A);     \
    EXPECT_APPROX(constant(cnt) < A, cnt < A);       \
                                                     \
    EXPECT_APPROX(constant(cnt) >= A, cnt >= A);     \
    EXPECT_APPROX(constant(cnt) > A, cnt > A);       \
                                                     \
    EXPECT_APPROX(A <= constant(cnt), A <= cnt);     \
    EXPECT_APPROX(A < constant(cnt), A < cnt);       \
                                                     \
    EXPECT_APPROX(A >= constant(cnt), A >= cnt);     \
    EXPECT_APPROX(A > constant(cnt), A > cnt);       \
  }
