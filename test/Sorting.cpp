// Copyright (c) Facebook, Inc. and its affiliates.

#define EIGEN_DISABLE_MULTICHANNEL_ARRAYS
#include "CommonHeader.h"  // Common definitions

INIT_TEST(SORTING, Types_2D_AnyMajor)
  const auto& vh = v.head(v.size() - 1);
  const auto& vt = v.tail(v.size() - 1);

  A.reshaped().sortDescInPlace();
  EXPECT_TRUE((vh >= vt).all());

  A.reshaped().sortAscInPlace();
  EXPECT_TRUE((vh <= vt).all());
}
