/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Scalar> struct wrap_scalar;

template <typename Tp, int ...OtherArgs>
struct wrap_scalar<Array<Tp, OtherArgs...>> {
  static constexpr int NumChannels = Array<Tp, OtherArgs...>::SizeAtCompileTime;
  typedef typename Array<Tp, OtherArgs...>::Scalar ChannelType;

#ifdef EIGEN_WITH_OPENCV
#  if CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR >= 3
  static constexpr int has_cv2_type = (cv::traits::SafeType<ChannelType>::value != CV_MAKETYPE(-1, 1));
  static constexpr int cv2_depth_id = (has_cv2_type ? (cv::traits::SafeType<ChannelType>::value) : -1);
#  else
  static constexpr int cv2_depth_id = cv::DataType<typename Array<Tp, OtherArgs...>::Scalar>::depth;
#  endif
  static constexpr int cv2_type_id = cv2_depth_id != -1 ? CV_MAKETYPE(cv2_depth_id, NumChannels) : -1;
#endif
};

template <typename Scalar>
struct wrap_scalar {
#ifdef EIGEN_WITH_OPENCV
#  if CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR >= 3
  static constexpr int has_cv2_type = cv::traits::SafeType<Scalar>::value != CV_MAKETYPE(-1, 1);
  static constexpr int cv2_depth_id = has_cv2_type ? cv::traits::SafeType<Scalar>::value : -1;
#  else
  static constexpr int cv2_depth_id = cv::DataType<Scalar>::depth;
#  endif
  static constexpr int cv2_type_id = cv2_depth_id != -1 ? CV_MAKETYPE(cv2_depth_id, 1) : -1;
#endif

  static constexpr int NumChannels = 1;
  typedef Scalar ChannelType;
};
