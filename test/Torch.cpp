// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#ifdef EIGEN_WITH_TORCH

template <typename> struct data_traits;

template <> struct data_traits<double>
  { static inline torch::Dtype func() { return torch::kF64; } };

template <> struct data_traits<float>
  { static inline torch::Dtype func() { return torch::kF32; } };

template <> struct data_traits<int64_t>
  { static inline torch::Dtype func() { return torch::kI64; } };

template <> struct data_traits<int32_t>
  { static inline torch::Dtype func() { return torch::kI32; } };

template <> struct data_traits<int16_t>
  { static inline torch::Dtype func() { return torch::kI16; } };

template <> struct data_traits<uint8_t>
  { static inline torch::Dtype func() { return torch:: kU8; } };

template <> struct data_traits<int8_t>
  { static inline torch::Dtype func() { return torch:: kI8; } };


INIT_TEST(TORCH_A, Types_3D_X_OpenCV)
  auto T = torch::from_blob(reinterpret_cast<Tp*>(A.data()),
      {1, A.rows(), A.cols(), A.channels()},
      data_traits<Tp>::func());

  EXPECT_TRUE(torch::allclose(T, A.torchTensor4D()));
  EXPECT_APPROX((Eigen::MakeMap<Tp, ND>(T)), A);
}

INIT_TEST(TORCH_B, Types_3D_S_OpenCV)
  auto T = torch::from_blob(reinterpret_cast<Tp*>(A.data()),
      {1, A.rows(), A.cols(), A.channels()},
      data_traits<Tp>::func());

  EXPECT_TRUE(torch::allclose(T, A.torchTensor4D()));
  EXPECT_APPROX((Eigen::MakeMap<Tp, ND>(T)), A);
}

INIT_TEST(TORCH_C, Types_2D_X_OpenCV)
  auto T = torch::from_blob(reinterpret_cast<Tp*>(A.data()),
      {1, A.channels(), A.rows(), A.cols()},
      data_traits<Tp>::func());

  EXPECT_TRUE(torch::allclose(T, A.torchTensor4D()));
  EXPECT_APPROX((Eigen::MakeMap<Tp, ND>(T)), A);
}

INIT_TEST(TORCH_D, Types_2D_S_OpenCV)
  auto T = torch::from_blob(reinterpret_cast<Tp*>(A.data()),
      {1, A.channels(), A.rows(), A.cols()},
      data_traits<Tp>::func());

  EXPECT_TRUE(torch::allclose(T, A.torchTensor4D()));
  EXPECT_APPROX((Eigen::MakeMap<Tp, ND>(T)), A);
}

#endif // EIGEN_WITH_TORCH
