// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#define INIT_TEST_BY_TYPE_GROUP(ConstantType, X, ...)                                  \
  INIT_TEST(BASE_SCALAR_OPS_##X, __VA_ARGS__)                                          \
    auto constant = [N = A.rows(), M = A.cols()] (ConstantType val)                    \
      { return TypeParam::Constant(N, M, static_cast<Tp>(val)); };                     \
                                                                                       \
    auto c1 = Eigen::internal::random<ConstantType>(1, 100);                           \
    auto c2 = Eigen::internal::random<ConstantType>(1, 100);                           \
                                                                                       \
    EXPECT_APPROX(constant(c1) - constant(c2) / (abs(A) + 1), c1 - c2 / (abs(A) + 1)); \
                                                                                       \
    EXPECT_APPROX(abs(A / 2).pow(constant(2)), abs(A / 2).pow(2));                     \
    EXPECT_APPROX(abs(A / 2).pow(constant(3)), abs(A / 2).pow(3));                     \
    EXPECT_APPROX(Eigen::pow(2, (A / 2).abs() + 1), Eigen::pow(2, (A / 2).abs() + 1)); \
                                                                                       \
    EXPECT_APPROX(constant(c1) * A + constant(c2), c1 * A + c2);                       \
    EXPECT_APPROX(constant(c1) + A * constant(c2), c1 + A * c2);                       \
    EXPECT_APPROX(A / constant(c1) - constant(c2), A / c1 - c2);                       \
                                                                                       \
    /*TODO(ygitman): Eigen master is broken, reenable once fixed*/                     \
    /*EXPECT_APPROX(A.min(constant(c1)), A.min(c1));*/                                 \
    /*EXPECT_APPROX(A.max(constant(c1)), A.max(c1));*/                                 \
  }
