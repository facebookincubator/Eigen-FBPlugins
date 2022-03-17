/* Copyright (c) Facebook, Inc. and its affiliates. */

#include "./OpenCV-helper.h"

EIGEN_STRONG_INLINE
operator typename std::conditional_t<IsConvertibleToCVMat, internal::OpenCVInputArrayHold, internal::NoneType<internal::OpenCVInputArrayHold>>() const
  { return internal::OpenCVInputArrayHold(rows(), cols(), internal::wrap_scalar<Scalar>::cv2_type_id, void_data()); }

EIGEN_STRONG_INLINE
operator typename std::conditional_t<IsConvertibleToCVMat, internal::OpenCVOutputArrayHold, internal::NoneType<internal::OpenCVOutputArrayHold>>()
  { return internal::OpenCVOutputArrayHold(rows(), cols(), internal::wrap_scalar<Scalar>::cv2_type_id, void_data()); }

template <typename Tp=void> EIGEN_STRONG_INLINE
typename std::enable_if_t<IsConvertibleToCVMat && std::is_same<Tp, void>::value, cv::Mat_<OpenCVElemType>> cvMat()
  { return cv::Mat_<OpenCVElemType>(rows(), cols(), (OpenCVElemType*) void_data()); }
