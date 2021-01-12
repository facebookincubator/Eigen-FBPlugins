// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#ifdef/**/EIGEN_WITH_OPENCV

#define WITH_COMMON                      \
  TypeParam B = TypeParam::Random(4, 7); \
  TypeParam C = TypeParam::Random(4, 7); \
  auto Af = A.template cast<double>();   \
  using Eigen::MakeMap;


INIT_TEST(OpenCV_X, Types_X_OpenCV) WITH_COMMON
  cv::absdiff((2 * A + 1), (2 * B - 1), C);
  EXPECT_APPROX(2 * (A - B + 1).abs(), C);

  Eigen::Array4d w = MakeMap(cv::sum(Af));
  EXPECT_NEAR(w.sum(), Af.sum(), 1e-2);
}

INIT_TEST(OpenCV_S, Types_S_OpenCV) WITH_COMMON
  Eigen::Array4d w = MakeMap(cv::sum(Af));
  EXPECT_NEAR(w.sum(), Af.sum(), 1e-2);
}

#endif // EIGEN_WITH_OPENCV
