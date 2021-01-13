/* Copyright (c) Facebook, Inc. and its affiliates. */

} // namespace internal

namespace /***/ numext {
template <typename Tp> EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
typename internal::enable_if<internal::is_convertible<Tp, bool>::value, bool>::type
    all(const Tp& x) { return static_cast<bool>(x); }

template <typename Tp> EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
bool all(const Eigen::DenseBase<Tp>& x) { return x.all(); }

template <typename Tp> EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
typename internal::enable_if<internal::is_convertible<Tp, bool>::value, bool>::type
    any(const Tp& x) { return static_cast<bool>(x); }

template <typename Tp> EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
bool any(const Eigen::DenseBase<Tp>& x) { return x.any(); }
}  // namespace numext

namespace /**/ internal {

template <typename> struct wrap_scalar;

} // namespace internal

template <typename T,
          bool=(bool)(internal::wrap_scalar<typename internal::traits<T>::Scalar>::NumChannels > 1),
          bool=(bool)(internal::traits<T>::Flags & DirectAccessBit)>
          struct Expr2d {
#ifndef EIGEN_FAIL_ON_EXPR2D
  typedef void type; static void make(const T&) {}
#endif
};

template <typename, typename, typename> struct SelectNC;
template <typename, int> struct VectorwiseOpExt;
template <typename> struct ArrayBaseNC;

namespace /**/ internal {

struct ArrayXprNC {};

#if /***/ !defined(EIGEN_DISABLE_MULTICHANNEL_ARRAYS)

template <typename Derived>
struct dense_xpr_base<Derived, ArrayXprNC>
  { typedef ArrayBaseNC<Derived> type; };

#endif // !defined(EIGEN_DISABLE_MULTICHANNEL_ARRAYS)

template <typename T, int O>
struct plain_matrix_type_dense<T, ArrayXprNC, O>
  { typedef typename plain_matrix_type_dense<T, ArrayXpr, O>::type type; };

template <> struct is_same<ArrayXprNC, ArrayXpr> : true_type {};
template <> struct is_same<ArrayXpr, ArrayXprNC> : true_type {};

template<typename A, typename B, typename Func>
EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
void call_assignment_no_alias(A& dst, const B& src, const Func& func);

template<typename A, typename B> EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
void call_assignment(A& dst, const B& src);

template <typename, int, typename> struct IndexedViewCompatibleType;

template <typename, typename> struct get_compile_time_incr;

template <int, typename, typename> struct member_lpNorm;
template <typename, typename> struct member_stableNorm;
template <typename, typename> struct member_hypotNorm;
template <typename, typename> struct member_blueNorm;
template <typename, typename> struct member_minCoeff;
template <typename, typename> struct member_maxCoeff;
template <typename, typename> struct member_count;
template <typename, typename> struct member_prod;
template <typename, typename> struct member_sum;
template <typename, typename> struct member_all;
template <typename, typename> struct member_any;

template <typename> struct scalar_boolean_and_op_nc;
template <typename> struct scalar_boolean_or_op_nc;

template <typename> struct scalar_bitwise_not_op;
template <typename> struct scalar_bitwise_and_op;
template <typename> struct scalar_bitwise_xor_op;
template <typename> struct scalar_bitwise_or_op;

template <typename, typename> struct add_assign_op;
template <typename, typename> struct sub_assign_op;
template <typename, typename> struct mul_assign_op;
template <typename, typename> struct div_assign_op;
template <typename, typename> struct assign_op;
template <typename> struct evaluator_base;

}  // namespace internal
}  // namespace Eigen

#ifdef /**/ EIGEN_WITH_OPENCV
#  include <opencv2/core.hpp>
#endif   // EIGEN_WITH_OPENCV

#ifdef /**/ EIGEN_WITH_IDEEP
#  include <ideep/tensor.hpp>
#endif   // EIGEN_WITH_IDEEP

#ifdef /**/ EIGEN_WITH_TORCH
#  include <torch/script.h>
#endif   // EIGEN_WITH_TORCH

#include <type_traits>
#include <algorithm>

namespace /***/ Eigen {
namespace /***/ internal {
