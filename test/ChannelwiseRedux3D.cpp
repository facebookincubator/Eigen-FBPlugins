// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#define TEST_CHANNELWISE_REDUX(fn)                                            \
  EXPECT_APPROX(A.unaryExpr([] (const Scalar& x) -> auto { return x.fn(); }), \
                A.channelwise().fn())

#if !defined(__clang__)
INIT_TEST(CHANNELWISE_REDUX_3D, Types_3D_F32_AnyMajor)
#else
INIT_TEST(CHANNELWISE_REDUX_3D, Types_3D_AnyMajor)
#endif
  TEST_CHANNELWISE_REDUX(squaredNorm);
  TEST_CHANNELWISE_REDUX(maxCoeff);
  TEST_CHANNELWISE_REDUX(minCoeff);
  TEST_CHANNELWISE_REDUX(count);
  TEST_CHANNELWISE_REDUX(norm);
  TEST_CHANNELWISE_REDUX(prod);
  TEST_CHANNELWISE_REDUX(mean);
  TEST_CHANNELWISE_REDUX(sum);
  TEST_CHANNELWISE_REDUX(all);
  TEST_CHANNELWISE_REDUX(any);
}

#undef TEST_CHANNELWISE_REDUX
