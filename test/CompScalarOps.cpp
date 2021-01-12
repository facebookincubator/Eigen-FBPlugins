// Copyright (c) Facebook, Inc. and its affiliates.

#include "CompScalarOps.h"  // Common definitions

#if !defined(__clang__)
  INIT_TEST_BY_TYPE_GROUP(double, F32, Types_F32_AnyMajor)
#else
  INIT_TEST_BY_TYPE_GROUP(double, F, Types_F_AnyMajor)
  INIT_TEST_BY_TYPE_GROUP(int, I, Types_I_AnyMajor)
#endif
