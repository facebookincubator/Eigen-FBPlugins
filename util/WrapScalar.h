/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Scalar> struct wrap_scalar;

template <typename Tp, int ...OtherArgs>
struct wrap_scalar<Array<Tp, OtherArgs...>> {
#ifdef EIGEN_WITH_OPENCV
  static constexpr int has_cv2_type = cv::traits::SafeType<typename Array<Tp, OtherArgs...>::Scalar>::value != CV_MAKETYPE(-1, 1);
  static constexpr int cv2_depth_id = has_cv2_type ? (cv::traits::SafeType<typename Array<Tp, OtherArgs...>::Scalar>::value) : -1;
  static constexpr int cv2_type_id = has_cv2_type ? CV_MAKETYPE(cv2_depth_id, (Array<Tp, OtherArgs...>::SizeAtCompileTime)) : -1;
#endif

  static constexpr int NumChannels = Array<Tp, OtherArgs...>::SizeAtCompileTime;
  typedef typename Array<Tp, OtherArgs...>::Scalar ChannelType;
};

template <typename Scalar>
struct wrap_scalar {
#ifdef EIGEN_WITH_OPENCV
  static constexpr int has_cv2_type = cv::traits::SafeType<Scalar>::value != CV_MAKETYPE(-1, 1);
  static constexpr int cv2_depth_id = has_cv2_type ? cv::traits::SafeType<Scalar>::value : -1;
  static constexpr int cv2_type_id = cv2_depth_id;
#endif

  static constexpr int NumChannels = 1;
  typedef Scalar ChannelType;
};
