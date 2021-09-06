// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#if !defined(__clang__)
INIT_TEST(REPLICATE_OPS_3D, Types_F32_3D_AnyMajor)
#else
INIT_TEST(REPLICATE_OPS_3D, Types_3D_AnyMajor)
#endif
  const auto& M = A.channelwise().template replicate<2>();

  for (int i = 0; i < M.size(); ++i)
    EXPECT_APPROX((A.coeff(i).template replicate<2, 1>()),
                  M.coeff(i));
}

#if !defined(__clang__)
INIT_TEST(REPLICATE_OPS_2D, Types_F32_2D_AnyMajor)
#else
INIT_TEST(REPLICATE_OPS_2D, Types_2D_AnyMajor)
#endif
  const auto& M = A.channelwise().template replicate<2>();
  typedef Eigen::Array<Tp, 2, 1> RScalar;

  for (int i = 0; i < M.rows(); ++i)
    for (int j = 0; j < M.cols(); ++j)
      EXPECT_APPROX(M(i, j), RScalar::Constant(A(i, j)));
}
