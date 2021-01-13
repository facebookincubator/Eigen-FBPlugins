/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename T> struct functor_traits<scalar_bitwise_not_op<T> >
  { enum { Cost = NumTraits<T>::AddCost, PacketAccess = false }; };

template <typename Scalar> struct scalar_bitwise_not_op {
  EIGEN_STRONG_INLINE_DEVICE_FUNC Scalar operator() (const Scalar& a) const { return ~a; }
  EIGEN_EMPTY_STRUCT_CTOR(scalar_bitwise_not_op)
};

#define /**/ BOOL_ARRAY Array<bool, N, M, Options, P, Q>

template <int N, int M, int Options, int P, int Q>
struct scalar_boolean_not_op<BOOL_ARRAY> {
  EIGEN_STRONG_INLINE_DEVICE_FUNC BOOL_ARRAY operator() (const BOOL_ARRAY& a) const { return !a; }
  EIGEN_EMPTY_STRUCT_CTOR(scalar_boolean_not_op)
};

#undef /***/ BOOL_ARRAY
