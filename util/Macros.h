/* Copyright (c) Facebook, Inc. and its affiliates. */

#ifdef NDEBUG
#  define EIGEN_STRONG_INLINE_DEVICE_FUNC EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
#  if EIGEN_COMP_GNUC && !defined(SYCL_DEVICE_ONLY)
#    define EIGEN_LAMBDA_INLINE __attribute__((always_inline))
#  endif
#else
#  define EIGEN_STRONG_INLINE_DEVICE_FUNC inline EIGEN_DEVICE_FUNC
#  define EIGEN_LAMBDA_INLINE

#if !defined(EIGEN_DISABLE_EXPRESSION_OPTIMISAZTIONS) \
 && !defined(EIGEN_FAIL_ON_EXPR2D)
#  define EIGEN_DISABLE_EXPRESSION_OPTIMISAZTIONS
#endif
#endif

#define EIGEN_ENABLE_IF_PROMOTABLE(T1, T2) \
  typename internal::make_int<typename internal::promote_scalar_arg<T1, T2, 0>::type>::type = 0

#define EIGEN_PROTECT_TYPE(Type) typename internal::type_wrapper<void (*)Type >::type

#define EIGEN_IMPORT_NUMCHANNELS(Scalar) \
  static constexpr int NumChannels = internal::wrap_scalar<Scalar>::NumChannels;

#define EIGEN_IMPORT_CHANNELTYPE(Scalar) \
  typedef typename internal::wrap_scalar<Scalar>::ChannelType ChannelType;

#define EIGEN_ENABLE_IF(cnd, T) \
  typename internal::enable_if<cnd, T>::type

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
