/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename T> struct functor_traits<scalar_boolean_and_op_nc<T> >
  { enum { Cost = NumTraits<T>::AddCost, PacketAccess = false }; };

template <typename T> struct functor_traits<scalar_boolean_or_op_nc<T> >
  { enum { Cost = NumTraits<T>::AddCost, PacketAccess = false }; };

template <typename T> struct functor_traits<scalar_bitwise_xor_op<T> >
  { enum { Cost = NumTraits<T>::AddCost, PacketAccess = false }; };

template <typename T> struct functor_traits<scalar_bitwise_and_op<T> >
  { enum { Cost = NumTraits<T>::AddCost, PacketAccess = false }; };

template <typename T> struct functor_traits<scalar_bitwise_or_op<T> >
  { enum { Cost = NumTraits<T>::AddCost, PacketAccess = false }; };

// TODO(ygitman): vectorization for bitwise ops

#define /**/ BOOL_ARRAY Array<bool, N, M, Options, P, Q>

template <typename>
struct scalar_boolean_and_op_nc {
  template <int N, int M, int Options, int P, int Q> EIGEN_STRONG_INLINE_DEVICE_FUNC
  BOOL_ARRAY operator()(const BOOL_ARRAY& a, const BOOL_ARRAY& b) const
    { return a && b; }

  bool operator()(const bool& a, const bool& b) const
    { return a && b; }

  EIGEN_EMPTY_STRUCT_CTOR(scalar_boolean_and_op_nc)
};

template <typename>
struct scalar_boolean_or_op_nc {
  template <int N, int M, int Options, int P, int Q> EIGEN_STRONG_INLINE_DEVICE_FUNC
  BOOL_ARRAY operator()(const BOOL_ARRAY& a, const BOOL_ARRAY& b) const
    { return a || b; }

  bool operator()(const bool& a, const bool& b) const
    { return a || b; }

  EIGEN_EMPTY_STRUCT_CTOR(scalar_boolean_or_op_nc)
};

template <typename Scalar>
struct scalar_bitwise_xor_op {
  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar operator()(const Scalar& a, const Scalar& b) const
    { return a ^ b; }

  EIGEN_EMPTY_STRUCT_CTOR(scalar_bitwise_xor_op)
};

template <typename Scalar>
struct scalar_bitwise_and_op {
  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar operator()(const Scalar& a, const Scalar& b) const
    { return a & b; }

  EIGEN_EMPTY_STRUCT_CTOR(scalar_bitwise_and_op)
};

template <typename Scalar>
struct scalar_bitwise_or_op {
  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar operator()(const Scalar& a, const Scalar& b) const
    { return a | b; }

  EIGEN_EMPTY_STRUCT_CTOR(scalar_bitwise_or_op)
};

#undef /***/ BOOL_ARRAY
