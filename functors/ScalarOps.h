/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Scalar, int N, int M, int Options, int P, int Q>
struct scalar_random_op<Array<Scalar, N, M, Options, P, Q> > {
  inline const Array<Scalar, N, M, Options, P, Q>  operator()() const
    { return Array<Scalar, N, M, Options, P, Q>::Random(); }

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
  scalar_random_op(const scalar_random_op&) {};

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
  scalar_random_op() {};
};

template<typename Tp, int N, int M, int Options, int Q, int P>
struct scalar_constant_op<Array<Tp, N, M, Options, Q, P> > {
  typedef Array<Tp, N, M, Options, Q, P> Scalar;

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  scalar_constant_op(const scalar_constant_op& other)
    : m_other(other.m_other) {}

  operator scalar_constant_op<Tp>() const
    { return scalar_constant_op<Tp>(m_other); }

  template<typename PacketType>
  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
  const PacketType packetOp() const
    { return pset1<PacketType>(m_other); }

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
  scalar_constant_op(const Tp& other)
    : m_other(other) {}

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
  const Scalar operator() () const
    { return Scalar(m_other); }

  const Tp m_other;
};
