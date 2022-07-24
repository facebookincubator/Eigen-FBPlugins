// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#if !defined(__clang__)
INIT_TEST(TEMPLATED_OPS_A, Types_F32_AnyMajor)
#else
INIT_TEST(TEMPLATED_OPS_A, All_Test_Types)
#endif
  for (int id = 0; id < A.cols(); ++id) {
    EXPECT_APPROX(A.template sliceAlong<0>(id), A.col(id));
  }

  for (int id = 0; id < A.rows(); ++id) {
    EXPECT_APPROX(A.template sliceAlong<1>(id), A.row(id));
  }

  const auto& colwiseSum = A.colwise().sum().eval();
  EXPECT_APPROX(A.template dimwise<0>().sum(), colwiseSum);

  const auto& rowwiseSum = A.rowwise().sum().eval();
  EXPECT_APPROX(A.template dimwise<1>().sum(), rowwiseSum);

  bool isRowMajor = decltype(A)::Flags&Eigen::RowMajorBit;
  EXPECT_FALSE((isRowMajor ^ A.isRowMajor()));
  EXPECT_TRUE((isRowMajor ^ A.isColMajor()));
}

#if !defined(__clang__)
INIT_TEST(TEMPLATED_OPS_CM, Types_F32_ColMajor)
#else
INIT_TEST(TEMPLATED_OPS_CM, Types_ColMajor)
#endif
  EXPECT_TRUE(A.outerSize() == A.cols());
  EXPECT_TRUE(A.innerSize() == A.rows());

  const auto& rowwiseSum = A.rowwise().sum().eval();
  const auto& colwiseSum = A.colwise().sum().eval();

  const auto& outerSum = A.alongOuterDim().sum();
  const auto& innerSum = A.alongInnerDim().sum();

  EXPECT_APPROX(outerSum, rowwiseSum);
  EXPECT_APPROX(innerSum, colwiseSum);

  for (int i = 0; i < A.outerSize(); ++i) {
    EXPECT_APPROX(A.innerSubVector(i), A.col(i));
  }

  for (int i = 0; i < A.innerSize(); ++i) {
    EXPECT_APPROX(A.outerSubVector(i), A.row(i));
  }
}

#if !defined(__clang__)
INIT_TEST(TEMPLATED_OPS_RM, Types_F32_RowMajor)
#else
INIT_TEST(TEMPLATED_OPS_RM, Types_RowMajor)
#endif
  EXPECT_TRUE(A.outerSize() == A.rows());
  EXPECT_TRUE(A.innerSize() == A.cols());

  const auto& outerSum = A.alongOuterDim().sum();
  const auto& innerSum = A.alongInnerDim().sum();

  const auto& rowwiseSum = A.rowwise().sum();
  const auto& colwiseSum = A.colwise().sum();

  EXPECT_APPROX(outerSum, colwiseSum);
  EXPECT_APPROX(innerSum, rowwiseSum);

  for (int i = 0; i < A.innerSize(); ++i) {
    EXPECT_APPROX(A.outerSubVector(i), A.col(i));
  }

  for (int i = 0; i < A.outerSize(); ++i) {
    EXPECT_APPROX(A.innerSubVector(i), A.row(i));
  }
}
