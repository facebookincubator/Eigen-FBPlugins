/* Copyright (c) Facebook, Inc. and its affiliates. */

#define DEFINE_CONST_CONVERSION(condition, outtype, ...)                                                     \
   EIGEN_STRONG_INLINE operator std::conditional_t<condition, outtype, internal::NoneType<outtype>>() const  \
     { return std::conditional_t<condition, outtype, internal::NoneType<outtype>>(__VA_ARGS__); }

#define DEFINE_CONVERSION(condition, outtype, ...)                                                     \
   EIGEN_STRONG_INLINE operator std::conditional_t<condition, outtype, internal::NoneType<outtype>>()  \
     { return std::conditional_t<condition, outtype, internal::NoneType<outtype>>(__VA_ARGS__); }

DEFINE_CONST_CONVERSION(
  (internal::wrap_scalar<Scalar>::cv2_depth_id != -1 && ((Flags & RowMajorBit) || IsVectorAtCompileTime)) && !((Flags & DirectAccessBit) && (Flags & LvalueBit)),
  internal::OpenCVInputArrayHold, rows(), cols(), internal::wrap_scalar<Scalar>::cv2_type_id, derived()
)

DEFINE_CONVERSION(
  (internal::wrap_scalar<Scalar>::cv2_depth_id != -1 && ((Flags & RowMajorBit) || IsVectorAtCompileTime)) &&  ((Flags & DirectAccessBit) && (Flags & LvalueBit)),
  internal::OpenCVOutputArrayHold, rows(), cols(), internal::wrap_scalar<Scalar>::cv2_type_id, derived().data()
)

DEFINE_CONST_CONVERSION(IsVectorAtCompileTime && SizeAtCompileTime == 2,
                        cv::Point_<Scalar>, this->x(), this->y())

DEFINE_CONST_CONVERSION(IsVectorAtCompileTime && SizeAtCompileTime == 2,
                        cv::Size_<Scalar>, this->x(), this->y())

constexpr static int cvDepthId()
  { return internal::wrap_scalar<Scalar>::cv2_depth_id; }

constexpr static int cvTypeId()
  { return internal::wrap_scalar<Scalar>::cv2_type_id; }

#undef DEFINE_CONST_CONVERSION
#undef DEFINE_CONVERSION
