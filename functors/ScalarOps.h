/* Copyright (c) Facebook, Inc. and its affiliates. */

#define /**/ LHS_ARRAY Array<LhsScalar, N, M, Options, P, Q>
#define /**/ RHS_ARRAY Array<RhsScalar, N, M, Options, P, Q>
#define /**/ BOOL_ARRAY Array<bool, N, M, Options, P, Q>

template<class Tp1, class Tp2, int N, int M, int Opts, int Q, int P>
struct promote_scalar_arg_to_array { typedef Array<typename promote_scalar_arg<Tp1, Tp2, false>::type, N, M, Opts, Q, P> type; };

template <typename LhsScalar, typename RhsScalar, int Options, int N, int M, int P, int Q, ComparisonName cmp>
struct result_of<scalar_cmp_op<LHS_ARRAY, RHS_ARRAY, cmp>(LHS_ARRAY, RHS_ARRAY)> { typedef bool type; };

#define /**/ OVERDEFINE_CMP_OPERATOR(x, expression)                                              \
  template <typename LhsScalar, typename RhsScalar, int Options, int N, int M, int P, int Q >    \
  struct scalar_cmp_op<LHS_ARRAY, RHS_ARRAY, cmp_##x> : binary_op_base<LHS_ARRAY, RHS_ARRAY > {  \
    EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE                                                        \
    BOOL_ARRAY operator()(const LHS_ARRAY& a, const RHS_ARRAY& b) const                          \
      { return expression; }                                                                     \
                                                                                                 \
    EIGEN_EMPTY_STRUCT_CTOR(scalar_cmp_op)                                                       \
    typedef BOOL_ARRAY result_type;                                                              \
  }

template <typename, typename>
struct void_struct {};

template <typename Tp1, typename Tp2, int N, int M, int Options, int Q, int P>
struct promote_scalar_arg<Array<Tp1, N, M, Options, Q, P>, Tp2, 0>
  : conditional<!is_eigen_type<Tp1>::value && !is_eigen_type<Tp2>::value,
      promote_scalar_arg_to_array<Tp1, Tp2, N, M, Options, Q, P>,
      void_struct<Tp1, Tp2> >::type {};

template <>
struct promote_scalar_arg<std::complex<float>, std::complex<double>, 0>
  { typedef std::complex<double> type; };

template <typename Scalar, int N, int M, int Options, int P, int Q>
struct scalar_random_op<Array<Scalar, N, M, Options, P, Q> > {
  inline const Array<Scalar, N, M, Options, P, Q>  operator()() const
    { return Array<Scalar, N, M, Options, P, Q>::Random(); }
  EIGEN_EMPTY_STRUCT_CTOR(scalar_random_op)
};

#define /**/ SPECIALIZE_BINARY_SCALAR_FUNC(func)                    \
  template <typename Type, int N, int M, int Options, int Q, int P> \
  struct scalar_##func##_op<Array<Type, N, M, Options, Q, P>,       \
                            Array<Type, N, M, Options, Q, P> > {    \
    typedef Array<Type, N, M, Options, Q, P> T;                     \
    EIGEN_EMPTY_STRUCT_CTOR(scalar_##func##_op)                     \
                                                                    \
    EIGEN_STRONG_INLINE_DEVICE_FUNC                                 \
    T operator() (const T& a, const T& b) const                     \
      { return a.func(b); }                                         \
  };

#define /**/ SPECIALIZE_UNARY_SCALAR_FUNC(func)                     \
  template <typename Type, int N, int M, int Options, int Q, int P> \
  struct scalar_##func##_op<Array<Type, N, M, Options, Q, P> > {    \
    typedef Array<Type, N, M, Options, Q, P> T;                     \
    EIGEN_EMPTY_STRUCT_CTOR(scalar_##func##_op)                     \
                                                                    \
    EIGEN_STRONG_INLINE_DEVICE_FUNC                                 \
    T operator() (const T& x) const                                 \
      { return x.func(); }                                          \
  };

template<typename Tp, int N, int M, int Options, int Q, int P>
struct scalar_constant_op<Array<Tp, N, M, Options, Q, P> > {
  typedef Array<Tp, N, M, Options, Q, P> Scalar;

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  scalar_constant_op(const scalar_constant_op& other)
    : m_other(other.m_other) {}

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

OVERDEFINE_CMP_OPERATOR(UNORD, !(a<=b || b<=a));
OVERDEFINE_CMP_OPERATOR(NEQ, (a != b));
OVERDEFINE_CMP_OPERATOR(EQ, (a == b));
OVERDEFINE_CMP_OPERATOR(LE, (a <= b));
OVERDEFINE_CMP_OPERATOR(LT, (a < b));
OVERDEFINE_CMP_OPERATOR(GE, (a >= b));
OVERDEFINE_CMP_OPERATOR(GT, (a > b));

SPECIALIZE_UNARY_SCALAR_FUNC(round)

SPECIALIZE_BINARY_SCALAR_FUNC(pow)
SPECIALIZE_BINARY_SCALAR_FUNC(min)
SPECIALIZE_BINARY_SCALAR_FUNC(max)

// TODO(ygitman): conj_product
// TODO(ygitman): hypot

#undef /***/ SPECIALIZE_BINARY_SCALAR_FUNC
#undef /***/ SPECIALIZE_UNARY_SCALAR_FUNC
#undef /***/ OVERDEFINE_CMP_OPERATOR
#undef /***/ BOOL_ARRAY
#undef /***/ LHS_ARRAY
#undef /***/ RHS_ARRAY
