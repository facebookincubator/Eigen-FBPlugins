// Copyright (c) Facebook, Inc. and its affiliates.

#include "BooleanOps.h"  // Common definitions

#if !defined(__clang__)
  INIT_TEST_BY_TYPE_GROUP(F32, Types_F32_AnyMajor)
#else
  INIT_TEST_BY_TYPE_GROUP(A, All_Test_Types)
#endif
