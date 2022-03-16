// Copyright (c) Facebook, Inc. and its affiliates.

#ifdef EIGEN_FAIL_ON_EXPR2D
#undef EIGEN_FAIL_ON_EXPR2D
#endif

#include "CommonHeader.h"

#if !defined(__clang__)
INIT_TEST(CHANNELWISE_OPS, Types_F32_AnyMajor)
#else
INIT_TEST(CHANNELWISE_OPS, Types_3D_F32_AnyMajor)
#endif
  EXPECT_APPROX(A.unaryExpr([] (const Scalar& x) { return x.template replicate<4, 1>().eval(); }),
                A.channelwise().template replicate<4>());

  // I can't use lambda to move from array to array-nc, but I can do reverse
  const auto& expr = A.unaryExpr([] (const Scalar& x) { return x[0]; });
  EXPECT_APPROX(expr.unaryExpr([] (const Tp& x) { return Array<Tp, 4, 1>::Constant(x).eval(); }),
                expr.channelwise().template replicate<4>());
  EXPECT_APPROX(A, A.channelwise().template replicate<1>());
}
