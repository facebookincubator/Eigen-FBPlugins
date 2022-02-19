/* Copyright (c) Facebook, Inc. and its affiliates. */

#ifdef NDEBUG
#  define EIGEN_STRONG_INLINE_DEVICE_FUNC EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
#else
#  define EIGEN_STRONG_INLINE_DEVICE_FUNC inline EIGEN_DEVICE_FUNC

#if !defined(EIGEN_DISABLE_EXPRESSION_OPTIMISAZTIONS) \
 && !defined(EIGEN_FAIL_ON_EXPR2D)
#  define EIGEN_DISABLE_EXPRESSION_OPTIMISAZTIONS
#endif
#endif

#define EIGEN_DEFER_CHECK(v) internal::is_same<EnableIf, void>::value && (v)

#define EIGEN_IMPORT_CHANNELTYPE(Scalar) \
  typedef typename internal::wrap_scalar<Scalar>::ChannelType ChannelType;

#define EIGEN_COMMON_SUBEXPR(Type, expr, alias, N) \
  typename internal::nested_eval<Type, N>::type alias((expr).derived());

#define EIGEN_INFER_NESTED_TYPE(T) \
  typedef typename internal::ultimate_ref_selector<T>::type NestedType;

#define EIGEN_IMPORT_NUMCHANNELS(Scalar) \
  enum { NumChannels = internal::wrap_scalar<Scalar>::NumChannels };

#define EIGEN_IS_INTEGRAL_TYPE(T) \
  (!internal::is_same<T, typename NumTraits<T>::NonInteger>::value)

#define EIGEN_PROTECT_TYPE(Type) typename internal::type_wrapper<void (*)Type >::type

#define EIGEN_DEFERRED_CHECK_ENABLE_IF(defer_check_condition, Type) \
  typename internal::enable_if<EIGEN_DEFER_CHECK(defer_check_condition), Type >::type

#define EIGEN_ENABLE_IFF_NC(Tp) \
  EIGEN_DEFERRED_CHECK_ENABLE_IF(internal::wrap_scalar<Scalar>::NumChannels >= 2, Tp)

#define EIGEN_ENABLE_IFF_1C(Tp) \
  EIGEN_DEFERRED_CHECK_ENABLE_IF(internal::wrap_scalar<Scalar>::NumChannels == 1, Tp)

#define EIGEN_MUL_NUM_CHANNELS(xpr) \
    ((xpr) == Dynamic ? Dynamic : (xpr) * internal::wrap_scalar<Scalar>::NumChannels)

#define EIGEN_ENABLE_IFF_ROWVECTOR(Tp) \
  EIGEN_DEFERRED_CHECK_ENABLE_IF(IsVectorAtCompileTime && ColsAtCompileTime == 1, Tp)

#define EIGEN_ENABLE_IFF_COLVECTOR(Tp) \
  EIGEN_DEFERRED_CHECK_ENABLE_IF(IsVectorAtCompileTime && RowsAtCompileTime == 1, Tp)

#define EIGEN_ENABLE_IFF_EXPR2D_EXISTS(T, R) \
  EIGEN_DEFERRED_CHECK_ENABLE_IF(!internal::is_void<typename Expr2d<T>::type>::value, R)

#define EIGEN_STATIC_ASSERT_IS_COMPILE_TIME_VECTOR(T) \
  EIGEN_STATIC_ASSERT_VECTOR_ONLY(T); EIGEN_STATIC_ASSERT_FIXED_SIZE(T);

#define EIGEN_STATIC_ASSERT_SCALAR_IS_COMPILE_TIME_VECTOR         \
  EIGEN_STATIC_ASSERT_VECTOR_ONLY(internal::wrap_scalar<Scalar>); \
  EIGEN_STATIC_ASSERT_FIXED_SIZE (internal::wrap_scalar<Scalar>);

#define EIGEN_STATIC_ASSERT_NON_NEGATIVE(p) \
    EIGEN_STATIC_ASSERT((p) >= 0, NUMERIC_TYPE_MUST_BE_REAL);

#define EIGEN_ENABLE_IFF_NOT_VECTOR(Tp) \
  EIGEN_DEFERRED_CHECK_ENABLE_IF(!IsVectorAtCompileTime, Tp)

#define EIGEN_ENABLE_IFF_VECTOR(Tp) \
  EIGEN_DEFERRED_CHECK_ENABLE_IF(IsVectorAtCompileTime, Tp)

#define EIGEN_META_IF(cnd, T1, T2) \
  typename internal::conditional<cnd, T1, T2>::type

#define EIGEN_ENABLE_IF(cnd, T) \
  typename internal::enable_if<cnd, T>::type

#define EIGEN_PLUGINS_PLAIN_ENUM_MAX(a, b) \
  (((int) a >= (int) b) ? (int) a : (int) b)

#define EIGEN_PLUGINS_PLAIN_ENUM_MIN(a, b) \
  (((int) a <= (int) b) ? (int) a : (int) b)

// We need to export MaxRows/MaxCols to avoid enum-compare warning
#define EIGEN_DEFINE_PUBLIC_INTERFACE(Derived)                                                        \
  constexpr static int MaxRowsAtCompileTime = Eigen::internal::traits<Derived>::MaxRowsAtCompileTime; \
  constexpr static int MaxColsAtCompileTime = Eigen::internal::traits<Derived>::MaxColsAtCompileTime; \
  constexpr static int RowsAtCompileTime = Eigen::internal::traits<Derived>::RowsAtCompileTime;       \
  constexpr static int ColsAtCompileTime = Eigen::internal::traits<Derived>::ColsAtCompileTime;       \
  constexpr static int IsVectorAtCompileTime = Base::IsVectorAtCompileTime;                           \
  constexpr static int MaxSizeAtCompileTime = Base::MaxSizeAtCompileTime;                             \
  constexpr static int Flags = Eigen::internal::traits<Derived>::Flags;                               \
  constexpr static int SizeAtCompileTime = Base::SizeAtCompileTime;                                   \
                                                                                   \
  typedef typename Eigen::internal::traits<Derived>::StorageIndex StorageIndex;    \
  typedef typename Eigen::internal::traits<Derived>::StorageKind StorageKind;      \
  typedef typename Eigen::internal::ref_selector<Derived>::type Nested;            \
  typedef typename Eigen::internal::traits<Derived>::Scalar Scalar;                \
  typedef typename Eigen::NumTraits<Scalar>::Real RealScalar;                      \
  typedef typename Base::CoeffReturnType CoeffReturnType;                          \
  typedef typename Base::PacketScalar PacketScalar;                                \
  using Base::const_cast_derived;                                                  \
  using Base::derived;

#ifdef __cpp_concepts
#  define EIGEN_REQUIRES(v) requires (bool(v))
#else
#  define EIGEN_REQUIRES(v)
#endif
