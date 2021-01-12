// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#if !defined(__clang__)
INIT_TEST(BITWISE_OPS, Types_I32_AnyMajor)
#else
INIT_TEST(BITWISE_OPS, Types_I_AnyMajor)
#endif
  auto constant = [N = A.rows(), M = A.cols()]
    (auto u) -> auto { return TypeParam::Constant(N, M, u); };
  auto u = static_cast<int>(A.mean());

  EXPECT_TRUE((~A + A == (Tp) -1).isOnes());

  EXPECT_APPROX(A & constant(u), A & u);
  EXPECT_APPROX(constant(u) & A, u & A);

  EXPECT_APPROX(A | constant(u), A | u);
  EXPECT_APPROX(constant(u) | A, u | A);

  EXPECT_APPROX(constant(u) ^ A, u ^ A);
  // TODO(ygitman): Add symmetric case
}
