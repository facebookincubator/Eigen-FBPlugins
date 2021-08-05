/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:
  enum { BaseFlag = internal::is_same<typename internal::traits<Derived>::XprKind, ArrayXpr>::value };

  EIGEN_STRONG_INLINE void* void_data() const
    { return const_cast<void*>(reinterpret_cast<const void*>(data())); }

  EIGEN_STRONG_INLINE void* void_data() /* */
    { return const_cast<void*>(reinterpret_cast</* */ void*>(data())); }

  enum { OpenCVDepthId = internal::wrap_scalar<Scalar>::cv2_depth_id };
  enum { OpenCVTypeId = internal::wrap_scalar<Scalar>::cv2_type_id };

  typedef cv::Vec<ChannelType, NumChannels> cvPixelTp;
  enum { Guard = (BaseFlag && ((Flags & RowMajorBit)
         || internal::traits<Derived>::RowsAtCompileTime == 1
         || internal::traits<Derived>::ColsAtCompileTime == 1) && OpenCVDepthId != -1) };

  struct NONE1 { /* private class to disable conversion */ };
  struct NONE2 { /* private class to disable conversion */ };

  typedef internal::OpenCVOutputArrayHold OutputHold;
  typedef internal::OpenCVInputArrayHold InputHold;

 public:
  EIGEN_STRONG_INLINE operator typename internal::conditional<Guard, OutputHold, NONE1>::type() /**/
    { return OutputHold(rows(), cols(), OpenCVTypeId, void_data()); }

  EIGEN_STRONG_INLINE operator typename internal::conditional<Guard, InputHold, NONE2>::type() const
    { return InputHold(rows(), cols(), OpenCVTypeId, void_data()); }

#define /**/ cvElemTp \
  typename internal::conditional<NumChannels != 1, cvPixelTp, ChannelType >::type

#define /**/ ALWAYS_TRUE !internal::is_same<Derived, Tp>::value

  template <typename Tp=void> EIGEN_STRONG_INLINE
  typename internal::enable_if<Guard && ALWAYS_TRUE, cv::Mat_<cvElemTp> >::type cvMat()
    { return cv::Mat_<cvElemTp>(rows(), cols(), (cvElemTp*) void_data()); }

#undef /***/ cvElemTp  // typename internal::conditional<...>::type
#undef ALWAYS_TRUE     // internal::is_same<Derived, Tp>::value
