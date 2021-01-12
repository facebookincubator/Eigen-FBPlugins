/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Scalar> struct wrap_scalar;

template <typename Scalar>
struct wrap_scalar {
  template <class Tp> struct CastXpr
    { struct Type { typedef Tp EvalReturnType; }; };

  typedef Scalar ChannelType;

  enum { IsVectorAtCompileTime = 1 };
  enum { SizeAtCompileTime = 1 };
  enum { NumChannels = 1 };

#ifdef /**/ EIGEN_WITH_OPENCV
  enum { cv2_depth_id = cv::traits::SafeType<ChannelType>::value != CV_MAKETYPE(-1, 1) ? cv::traits::SafeType<ChannelType>::value : -1};
  enum { cv2_type_id = cv2_depth_id };
#endif   // EIGEN_WITH_OPENCV
};

template <typename Tp, int N, int M, int Options, int P, int Q>
struct wrap_scalar<Array<Tp, N, M, Options, P, Q> > {
  typedef Array<Tp, N, M, Options, P, Q> Scalar;

  template <class DstType> struct CastXpr {
    struct Type {
      typedef typename Scalar::template CastXpr<DstType>::Type CastType;
      typedef typename remove_all<CastType>::type CastTypeCleaned;
      typedef typename CastTypeCleaned::EvalReturnType EvalReturnType;
    };
  };

  typedef typename Scalar::Scalar ChannelType;

  enum { IsVectorAtCompileTime = Scalar::IsVectorAtCompileTime };
  enum { SizeAtCompileTime = Scalar::SizeAtCompileTime };
  enum { NumChannels = Scalar::SizeAtCompileTime };

#ifdef /**/ EIGEN_WITH_OPENCV
  enum { cv2_depth_id = cv::traits::SafeType<ChannelType>::value != CV_MAKETYPE(-1, 1) ? cv::traits::SafeType<ChannelType>::value : -1};
  enum { cv2_type_id = cv2_depth_id == -1 ? -1 : CV_MAKETYPE(cv2_depth_id, NumChannels) };
#endif   // EIGEN_WITH_OPENCV
};
