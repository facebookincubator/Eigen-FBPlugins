/* Copyright (c) Facebook, Inc. and its affiliates. */

private:
 struct DISABLE_CONVERSION1 {};
 struct DISABLE_CONVERSION2 {};
 struct DISABLE_CONVERSION3 {};
 struct DISABLE_CONVERSION4 {};

public:
#define IS_ROWMAJOR_AND_CV_TYPE                         \
  (internal::wrap_scalar<Scalar>::cv2_depth_id != -1 && \
  ((Flags & RowMajorBit) || IsVectorAtCompileTime))

#define IS_WRITABLE \
  ((Flags & DirectAccessBit) && (Flags & LvalueBit))

 EIGEN_STRONG_INLINE operator
 typename internal::conditional<IS_ROWMAJOR_AND_CV_TYPE && !IS_WRITABLE, internal::OpenCVInputArrayHold, DISABLE_CONVERSION1>::type() const {
     return internal::OpenCVInputArrayHold(rows(), cols(), internal::wrap_scalar<Scalar>::cv2_type_id, derived());
 }

 EIGEN_STRONG_INLINE operator
 typename internal::conditional<IS_ROWMAJOR_AND_CV_TYPE && IS_WRITABLE, internal::OpenCVOutputArrayHold, DISABLE_CONVERSION4>::type() {
     return internal::OpenCVOutputArrayHold(rows(), cols(), internal::wrap_scalar<Scalar>::cv2_type_id, derived().data());
 }

#undef IS_ROWMAJOR_AND_CV_TYPE
#undef IS_WRITABLE

 EIGEN_STRONG_INLINE
 operator typename internal::conditional<IsVectorAtCompileTime &&
                                             SizeAtCompileTime == 2,
                                         cv::Point_<Scalar>,
                                         DISABLE_CONVERSION2>::type() const {
     return typename internal::conditional < IsVectorAtCompileTime &&
                SizeAtCompileTime == 2,
            cv::Point_<Scalar>,
            DISABLE_CONVERSION2 > ::type(this->x(), this->y());
 }

 EIGEN_STRONG_INLINE
 operator typename internal::conditional<IsVectorAtCompileTime &&
                                             SizeAtCompileTime == 2,
                                         cv::Size_<Scalar>,
                                         DISABLE_CONVERSION3>::type() const {
     return typename internal::conditional < IsVectorAtCompileTime &&
                SizeAtCompileTime == 2,
            cv::Size_<Scalar>,
            DISABLE_CONVERSION3 > ::type(this->x(), this->y());
 }

 public:
#if EIGEN_HAS_CONSTEXPR
  constexpr static int cvDepthId()
   { return internal::wrap_scalar<Scalar>::cv2_depth_id; }

  constexpr static int cvTypeId()
   { return internal::wrap_scalar<Scalar>::cv2_type_id; }
#else
  static int cvDepthId()
   { return internal::wrap_scalar<Scalar>::cv2_depth_id; }

  static int cvTypeId()
   { return internal::wrap_scalar<Scalar>::cv2_type_id; }
#endif
