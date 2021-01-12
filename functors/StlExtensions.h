/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename T>
struct Tuple {
  EIGEN_STRONG_INLINE_DEVICE_FUNC
  explicit Tuple(const T& arg) : nestedExpression(arg.eval())
    { EIGEN_STATIC_ASSERT_IS_COMPILE_TIME_VECTOR(T); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  const typename T::EvalReturnType nestedExpr() const
    { return nestedExpression; }

  typename T::EvalReturnType nestedExpression;

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  typename T::EvalReturnType nestedExpr()
    { return nestedExpression; }

  // TODO(ygitman): redo without eval
};

}  // namespace internal

#if /***/ EIGEN_HAS_CXX11 == 1

}  // namespace Eigen
namespace /***/ std {

template <typename Xpr>
struct tuple_size<Eigen::internal::Tuple<Xpr>> {
  enum { value = Xpr::SizeAtCompileTime };
  typedef std::size_t value_type;
  typedef Xpr type;

#if /***/ EIGEN_HAS_CXX14 == 0
  operator value_type() const noexcept
    { return value; }
#else  // EIGEN_HAS_CXX14 == 0
  constexpr   operator value_type() const noexcept
    { return value; }
  constexpr value_type operator()() const noexcept
    { return value; }
#endif // EIGEN_HAS_CXX14 == 0
};

template <std::size_t N, typename T, int ...Vs>
struct tuple_element<N, Eigen::Matrix<T, Vs...>>
  { typedef T type; };

template <typename T, int ...Vs>
struct tuple_size<Eigen::Matrix<T, Vs...>>
  : tuple_size<Eigen::internal::Tuple<Eigen::Matrix<T, Vs...>>> {};

template <std::size_t N, typename T, int ...Vs>
struct tuple_element<N, Eigen::Array<T,  Vs...>>
  { typedef T type; };

template <typename T, int ...Vs>
struct tuple_size<Eigen::Array<T, Vs...>>
  : tuple_size<Eigen::internal::Tuple<Eigen::Matrix<T, Vs...>>> {};

template <std::size_t N, typename Xpr>
struct tuple_element<N, Eigen::internal::Tuple<Xpr>>
  { typedef typename Xpr::Scalar type; };

}  // namespace std
namespace /***/ Eigen {

#endif // EIGEN_HAS_CXX11 == 1

template <int Idx, typename Derived>
EIGEN_STRONG_INLINE_DEVICE_FUNC
typename internal::enable_if<Derived::IsVectorAtCompileTime, typename Derived::Scalar>::type
  get(const internal::Tuple<Derived>& arg) { return arg.nestedExpr()[Idx]; }

template <int Idx, typename Derived>
EIGEN_STRONG_INLINE_DEVICE_FUNC
typename internal::enable_if<Derived::IsVectorAtCompileTime, typename Derived::Scalar&>::type
  get(/***/ ArrayBase<Derived>& arg)  { return arg.derived()[Idx]; }

template <int Idx, typename Derived>
EIGEN_STRONG_INLINE_DEVICE_FUNC
typename internal::enable_if<Derived::IsVectorAtCompileTime, typename Derived::Scalar&>::type
  get(/***/ MatrixBase<Derived>& arg) { return arg.derived()[Idx]; }

template <int Idx, typename Derived>
EIGEN_STRONG_INLINE_DEVICE_FUNC
typename internal::enable_if<Derived::IsVectorAtCompileTime, typename Derived::Scalar>::type
  get(const ArrayBase<Derived>& arg)  { return arg.derived()[Idx]; }

template <int Idx, typename Derived>
EIGEN_STRONG_INLINE_DEVICE_FUNC
typename internal::enable_if<Derived::IsVectorAtCompileTime, typename Derived::Scalar>::type
  get(const MatrixBase<Derived>& arg) { return arg.derived()[Idx]; }

namespace /***/ internal {
