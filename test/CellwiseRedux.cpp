// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#define TEST_CELLWISE_REDUX(fn)                                  \
  { typedef Eigen::Map<Array<Tp, A.channels(), Dynamic> > MType; \
    MType MapObject((Tp*) A.data(), A.channels(), A.size());     \
    EXPECT_APPROX(MapObject.rowwise().fn(),                      \
                  A.cellwise().fn()); }

INIT_TEST(CELLWISE_REDUX_Y, Types_F_AnyMajor)
  TEST_CELLWISE_REDUX(prod)  // only floats because of the overflow
}

INIT_TEST(CELLWISE_REDUX_X, All_Test_Types)
  TEST_CELLWISE_REDUX(maxCoeff)
  TEST_CELLWISE_REDUX(minCoeff)
  TEST_CELLWISE_REDUX(sum)
}

#undef TEST_PARTIAL_REDUX
