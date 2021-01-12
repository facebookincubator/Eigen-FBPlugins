/* Copyright (c) Facebook, Inc. and its affiliates. */

}  // namespace internal

#define /**/ DISABLE_DANGEROUS_ARITHMETIC(T)                                                                 \
  template<> struct ScalarBinaryOpTraits<T, T, internal::scalar_max_op<T, T> > { typedef T ReturnType; };    \
  template<> struct ScalarBinaryOpTraits<T, T, internal::scalar_min_op<T, T> > { typedef T ReturnType; };    \
                                                                                                             \
  template<internal::ComparisonName CmpTp>                                                                   \
  struct ScalarBinaryOpTraits<T, T, internal::scalar_cmp_op<T, T, CmpTp> > { typedef bool ReturnType; };     \
  template<> struct ScalarBinaryOpTraits<T, T, internal::assign_op<T, T> > { typedef T ReturnType; };        \
                                                                                                             \
  template<> struct internal::scalar_opposite_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_opposite_op) };         \
  template<> struct internal::scalar_inverse_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_inverse_op) };           \
  template<> struct internal::scalar_square_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_square_op) };             \
  template<> struct internal::scalar_cube_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_cube_op) };                 \
  template<> struct internal::scalar_abs2_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_abs2_op) };                 \
  template<> struct internal::scalar_exp_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_exp_op) };                   \
                                                                                                             \
  template<typename BinaryOp> struct ScalarBinaryOpTraits<T, T, BinaryOp> {};

#define /**/ DISABLE_DIFFERENCE(T)                                                                           \
  template<> struct internal::scalar_opposite_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_opposite_op) };         \
  template<> struct ScalarBinaryOpTraits<T, T, internal::scalar_difference_op<T, T> > {};

#define /**/ DISABLE_FLOAT_OPS(T)                                                                            \
  template<> struct internal::scalar_bessel_i1e_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_i1e_op) };     \
  template<> struct internal::scalar_bessel_k1e_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_k1e_op) };     \
  template<> struct internal::scalar_bessel_i0e_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_i0e_op) };     \
  template<> struct internal::scalar_bessel_k0e_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_k0e_op) };     \
  template<> struct internal::scalar_bessel_i1_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_i1_op) };       \
  template<> struct internal::scalar_bessel_j1_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_j1_op) };       \
  template<> struct internal::scalar_bessel_y1_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_y1_op) };       \
  template<> struct internal::scalar_bessel_k1_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_k1_op) };       \
  template<> struct internal::scalar_bessel_i0_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_i0_op) };       \
  template<> struct internal::scalar_bessel_j0_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_j0_op) };       \
  template<> struct internal::scalar_bessel_y0_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_y0_op) };       \
  template<> struct internal::scalar_bessel_k0_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_bessel_k0_op) };       \
  template<> struct internal::scalar_logistic_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_logistic_op) };         \
  template<> struct internal::scalar_betainc_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_betainc_op) };           \
  template<> struct internal::scalar_digamma_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_digamma_op) };           \
  template<> struct internal::scalar_igammac_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_igammac_op) };           \
  template<> struct internal::scalar_lgamma_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_lgamma_op) };             \
  template<> struct internal::scalar_igamma_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_igamma_op) };             \
  template<> struct internal::scalar_ndtri_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_ndtri_op) };               \
  template<> struct internal::scalar_rsqrt_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_rsqrt_op) };               \
  template<> struct internal::scalar_expm1_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_expm1_op) };               \
  template<> struct internal::scalar_log1p_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_log1p_op) };               \
  template<> struct internal::scalar_zeta_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_zeta_op) };                 \
  template<> struct internal::scalar_erfc_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_erfc_op) };                 \
  template<> struct internal::scalar_sqrt_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_sqrt_op) };                 \
  template<> struct internal::scalar_atan_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_atan_op) };                 \
  template<> struct internal::scalar_asin_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_asin_op) };                 \
  template<> struct internal::scalar_acos_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_acos_op) };                 \
  template<> struct internal::scalar_tanh_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_tanh_op) };                 \
  template<> struct internal::scalar_sinh_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_sinh_op) };                 \
  template<> struct internal::scalar_cosh_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_cosh_op) };                 \
  template<> struct internal::scalar_erf_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_erf_op) };                   \
  template<> struct internal::scalar_exp_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_exp_op) };                   \
  template<> struct internal::scalar_log_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_log_op) };                   \
  template<> struct internal::scalar_tan_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_tan_op) };                   \
  template<> struct internal::scalar_sin_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_sin_op) };                   \
  template<> struct internal::scalar_cos_op<T> { EIGEN_EMPTY_STRUCT_CTOR(scalar_cos_op) };                   \
  template<> struct ScalarBinaryOpTraits<T, T, internal::scalar_pow_op<T, double> > {};                      \
  template<> struct ScalarBinaryOpTraits<T, T, internal::scalar_pow_op<T, float> > {};                       \
  template<> struct ScalarBinaryOpTraits<T, T, internal::scalar_hypot_op<T, T> > {};

namespace /***/ numext {

// TODO(ygitman): lpNorm bypasses this
template<typename T, typename T2>
EIGEN_STRONG_INLINE_DEVICE_FUNC
typename internal::enable_if<EIGEN_IS_INTEGRAL_TYPE(T), T>::type
  pow(const T& x, const T2& y) {}

template<typename T>
EIGEN_STRONG_INLINE_DEVICE_FUNC
typename internal::enable_if<EIGEN_IS_INTEGRAL_TYPE(T), T>::type
  sqrt(const T& x) {}

}  // namespace numext

DISABLE_DANGEROUS_ARITHMETIC(numext::uint8_t);
DISABLE_DANGEROUS_ARITHMETIC(numext::int8_t);

DISABLE_DIFFERENCE(numext::uint64_t);
DISABLE_DIFFERENCE(numext::uint32_t);
DISABLE_DIFFERENCE(numext::uint16_t);

DISABLE_FLOAT_OPS(numext::uint64_t);
DISABLE_FLOAT_OPS(numext::int64_t);
DISABLE_FLOAT_OPS(numext::uint32_t);
DISABLE_FLOAT_OPS(numext::int32_t);
DISABLE_FLOAT_OPS(numext::uint16_t);
DISABLE_FLOAT_OPS(numext::int16_t);

#undef /**/ DISABLE_DIFFERENCE
#undef /**/ DISABLE_FLOAT_OPS
#undef /**/ DISABLE_DANGEROUS_ARITHMETIC

namespace /***/ internal {
