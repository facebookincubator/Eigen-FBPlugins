/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename> struct wrap_scalar;
#include "./MathFunctions.h"

} // namespace internal

template <typename T,
          bool=(bool)(internal::wrap_scalar<typename internal::traits<T>::Scalar>::NumChannels > 1),
          bool=(bool)(internal::traits<T>::Flags & DirectAccessBit)>
          struct Expr2d {
#ifndef EIGEN_FAIL_ON_EXPR2D
  static constexpr bool value = false;
#endif
};

template <typename, int> struct VectorwiseOpNC;
template <typename> struct ArrayBaseNC;

namespace internal {

struct ArrayXprNC {};

#if /***/ !defined(EIGEN_DISABLE_MULTICHANNEL_ARRAYS)

template <typename Derived>
struct dense_xpr_base<Derived, ArrayXprNC> {
  typedef typename internal::traits<Derived>::Scalar Scalar;
  typedef ArrayBaseNC<Derived> XprTpA;
  typedef ArrayBase<Derived> XprTpB;

  enum { val = internal::wrap_scalar<Scalar>::NumChannels };
  typedef std::conditional_t<val != 1, XprTpA, XprTpB> type;
};

#endif // !defined(EIGEN_DISABLE_MULTICHANNEL_ARRAYS)

template <typename T, int O>
struct plain_matrix_type_dense<T, ArrayXprNC, O>
  { typedef typename plain_matrix_type_dense<T, ArrayXpr, O>::type type; };

template <> struct is_same<ArrayXprNC, ArrayXpr> : true_type {};
template <> struct is_same<ArrayXpr, ArrayXprNC> : true_type {};

template <typename, int, typename> struct IndexedViewCompatibleType;
template <typename, typename> struct get_compile_time_incr;

}  // namespace internal
}  // namespace Eigen

#ifdef EIGEN_WITH_OPENCV
#  include <opencv2/core.hpp>
#endif

#ifdef EIGEN_WITH_IDEEP
#  include <ideep/tensor.hpp>
#endif

#ifdef EIGEN_WITH_TORCH
#  include <torch/script.h>
#endif

#include <type_traits>
#include <algorithm>

namespace /***/ Eigen {
namespace internal {
