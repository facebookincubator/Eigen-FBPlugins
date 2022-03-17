 private:
  static constexpr bool IsConvertibleToCVMat = std::is_same<typename internal::traits<Derived>::XprKind, ArrayXpr>::value
    && (RowsAtCompileTime == 1 || ColsAtCompileTime == 1 || (Flags & RowMajorBit))
    && internal::wrap_scalar<Scalar>::cv2_depth_id != -1;

  typedef typename std::conditional_t<NumChannels != 1, cv::Vec<ChannelType, NumChannels>, ChannelType> OpenCVElemType;

  EIGEN_STRONG_INLINE void* void_data() const
    { return const_cast<void*>(reinterpret_cast<const void*>(data())); }

  EIGEN_STRONG_INLINE void* void_data() /* */
    { return const_cast<void*>(reinterpret_cast<void*>(data())); }

 public:
