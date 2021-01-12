/* Copyright (c) Facebook, Inc. and its affiliates. */

}  // namespace internal

#define /**/ MAKE_FN_ARG_TP(Type) \
  typename internal::conditional<internal::is_lvalue<Type>::value, Type, const Type>::type&

#define /**/ DECLARE_MAKE_FN(T) EIGEN_STRONG_INLINE_DEVICE_FUNC \
  static typename internal::ultimate_ref_selector<type>::type make(MAKE_FN_ARG_TP(T) arg)

template <typename T, bool v> struct Expr2d<T, false, v>
  { typedef T type; DECLARE_MAKE_FN(T) { return arg; } protected: Expr2d() {} };

template <typename ExprType>
struct Expr2d<const ExprType, true, false> : Expr2d<ExprType, true, false>
  { typedef const typename Expr2d<ExprType, true, false>::type type; };

#define /**/ GET_CONSTANTS(T)                                       \
  enum { IsRowMajor = (internal::traits<T>::Flags & RowMajorBit) }; \
                                                                    \
  enum { P = internal::traits<T>::MaxRowsAtCompileTime };           \
  enum { Q = internal::traits<T>::MaxColsAtCompileTime };           \
  enum { N = internal::traits<T>::RowsAtCompileTime };              \
  enum { M = internal::traits<T>::ColsAtCompileTime };              \
                                                                    \
  enum { Alignment = internal::traits<T>::Alignment };              \
                                                                    \
  typedef typename internal::traits<T>::Scalar Scalar;              \
                                                                    \
  EIGEN_IMPORT_CHANNELTYPE(Scalar);                                 \
  EIGEN_IMPORT_NUMCHANNELS(Scalar);                                 \
                                                                    \
  enum { N2 = (N == Dynamic ? Dynamic : ((int) IsRowMajor ? (int) N : (int) N * NumChannels)) }; \
  enum { M2 = (M == Dynamic ? Dynamic : ((int) IsRowMajor ? (int) M * NumChannels : (int) M)) }; \
  enum { P2 = (P == Dynamic ? Dynamic : ((int) IsRowMajor ? (int) P : (int) P * NumChannels)) }; \
  enum { Q2 = (Q == Dynamic ? Dynamic : ((int) IsRowMajor ? (int) Q * NumChannels : (int) Q)) };

template <typename T>
struct Expr2d<T, true, true> {
  GET_CONSTANTS(T)

  enum { S = internal::traits<T>::OuterStrideAtCompileTime };

  enum { S2 = (S == Dynamic ? Dynamic : (int) (S * NumChannels)) };
  enum { NoOuterStride = (((int)S != Dynamic) && ((int)S == (IsRowMajor ? (int)M : (int)N))) };

  typedef Array<ChannelType, N2, M2, IsRowMajor ? RowMajorBit : 0, P2, Q2> InternalType;

  typedef typename internal::conditional<NoOuterStride, Stride<0, 0>, Stride<S2, 0> >::type StrideType;
  typedef Map<typename internal::conditional<internal::is_lvalue<T>::value, InternalType, const InternalType>::type,
              Alignment, StrideType> non_const_type;

  typedef typename internal::conditional<internal::traits<T>::InnerStrideAtCompileTime == 1,
      typename internal::conditional<internal::is_lvalue<T>::value, non_const_type, const non_const_type>::type,
      void>::type type;

  DECLARE_MAKE_FN(T) {
    if (NoOuterStride) {
      // TODO(ygitman): do I really need this branch?
      return type((ChannelType*) arg.data(),
                IsRowMajor ? arg.rows() : arg.rows() * NumChannels,
                IsRowMajor ? arg.cols() * NumChannels : arg.cols());
    } else {
      return type((ChannelType*) arg.data(),
                IsRowMajor ? arg.rows() : arg.rows() * NumChannels,
                IsRowMajor ? arg.cols() * NumChannels : arg.cols(),
                StrideType(arg.outerStride() * NumChannels, 0));
    }
  }

 protected:
  Expr2d() {}
};

template <typename PlainObjectType, typename ScalarType>
struct Expr2d<CwiseNullaryOp<internal::scalar_random_op<ScalarType>, PlainObjectType>, true, false> {
  typedef CwiseNullaryOp<internal::scalar_random_op<ScalarType>, PlainObjectType> T;

  GET_CONSTANTS(PlainObjectType)

  typedef CwiseNullaryOp<internal::scalar_random_op<ChannelType>, Array<ChannelType, N2, M2, 0, P2, Q2> > type;

  static const type make(const T& arg)
    { return type(IsRowMajor ? arg.rows() : NumChannels * arg.rows(), IsRowMajor ? NumChannels * arg.cols() : arg.cols()); }
};

template <typename PlainObjectType, typename ScalarType>
struct Expr2d<CwiseNullaryOp<internal::scalar_constant_op<ScalarType>, PlainObjectType>, true, false> {
  typedef CwiseNullaryOp<internal::scalar_constant_op<ScalarType>, PlainObjectType> T;

  GET_CONSTANTS(PlainObjectType)

  typedef CwiseNullaryOp<internal::scalar_constant_op<ChannelType>, Array<ChannelType, N2, M2, 0, P2, Q2> > type;

  static const type make(const T& arg)
    { return type(IsRowMajor ? arg.rows() : NumChannels * arg.rows(), IsRowMajor ? NumChannels * arg.cols() : arg.cols(),
                  internal::scalar_constant_op<ChannelType>(arg.functor().m_other)); }
};

template <template<typename> class Functor, typename XprType>
struct Expr2d<CwiseUnaryOp<Functor<typename internal::traits<XprType>::Scalar>, XprType>, true, false> {
  typedef typename internal::traits<XprType>::Scalar Scalar;

  EIGEN_IMPORT_CHANNELTYPE(Scalar);

  typedef CwiseUnaryOp<Functor<Scalar>, XprType> ArgType;
  typedef typename Expr2d<const XprType>::type XprType2d;

  typedef typename internal::conditional<
      internal::is_void<XprType2d>::value, void,
      CwiseUnaryOp<Functor<ChannelType>, const XprType2d> >::type type;

  static const type make(const ArgType& arg) {
    return type(Expr2d<const XprType>::make(arg.nestedExpression()));
  }
};

template <typename XprType, typename OldScalar, typename NewScalar>
struct Expr2d<CwiseUnaryOp<internal::scalar_cast_op<OldScalar, NewScalar>, XprType>, true, false> {
  typedef typename internal::wrap_scalar<OldScalar>::ChannelType OldChannelType;
  typedef typename internal::wrap_scalar<NewScalar>::ChannelType NewChannelType;

  typedef CwiseUnaryOp<internal::scalar_cast_op<OldScalar, NewScalar>, XprType> ArgType;
  typedef typename Expr2d<const XprType>::type XprType2d;

  typedef typename internal::conditional<
      internal::is_void<XprType2d>::value, void,
      CwiseUnaryOp<internal::scalar_cast_op<OldChannelType, NewChannelType>, const XprType2d> >::type type;

  static const type make(const ArgType& arg) {
    return type(Expr2d<const XprType>::make(arg.nestedExpression()));
  }
};

template <template<typename, typename> class Functor, typename LhsXprType, typename RhsXprType>
struct Expr2d<CwiseBinaryOp<Functor<typename internal::traits<LhsXprType>::Scalar,
                                    typename internal::traits<RhsXprType>::Scalar>, LhsXprType, RhsXprType>, true, false> {
  typedef typename internal::traits<LhsXprType>::Scalar LhsScalar;
  typedef typename internal::traits<RhsXprType>::Scalar RhsScalar;

  typedef typename internal::wrap_scalar<LhsScalar>::ChannelType LhsChannelType;
  typedef typename internal::wrap_scalar<RhsScalar>::ChannelType RhsChannelType;

  typedef CwiseBinaryOp<Functor<LhsScalar, RhsScalar>, LhsXprType, RhsXprType> ArgType;

  typedef typename Expr2d<const LhsXprType>::type LhsXprType2d;
  typedef typename Expr2d<const RhsXprType>::type RhsXprType2d;

  typedef typename internal::conditional<
      internal::is_void<LhsXprType2d>::value || internal::is_void<RhsXprType2d>::value, void,
      CwiseBinaryOp<Functor<LhsChannelType, RhsChannelType>, const LhsXprType2d, const RhsXprType2d> >::type type;

  static const type make(const ArgType& arg) {
    // This seems to skip compilation in the void case, interesting.
    return type(Expr2d<const LhsXprType>::make(arg.lhs()), Expr2d<const RhsXprType>::make(arg.rhs()));
  }
};

// min, max
template <template<typename, typename, int> class Functor, typename LhsXprType, typename RhsXprType, int IntArg>
struct Expr2d<CwiseBinaryOp<Functor<typename internal::traits<LhsXprType>::Scalar,
                                    typename internal::traits<RhsXprType>::Scalar, IntArg>, LhsXprType, RhsXprType>, true, false> {
  typedef typename internal::traits<LhsXprType>::Scalar LhsScalar;
  typedef typename internal::traits<RhsXprType>::Scalar RhsScalar;

  typedef typename internal::wrap_scalar<LhsScalar>::ChannelType LhsChannelType;
  typedef typename internal::wrap_scalar<RhsScalar>::ChannelType RhsChannelType;

  typedef CwiseBinaryOp<Functor<LhsScalar, RhsScalar, IntArg>, LhsXprType, RhsXprType> ArgType;

  typedef typename Expr2d<const LhsXprType>::type LhsXprType2d;
  typedef typename Expr2d<const RhsXprType>::type RhsXprType2d;

  typedef typename internal::conditional<
      internal::is_void<LhsXprType2d>::value || internal::is_void<RhsXprType2d>::value, void,
      CwiseBinaryOp<Functor<LhsChannelType, RhsChannelType, IntArg>, const LhsXprType2d, const RhsXprType2d> >::type type;

  static const type make(const ArgType& arg) {
    // This seems to skip compilation in the void case, interesting.
    return type(Expr2d<const LhsXprType>::make(arg.lhs()), Expr2d<const RhsXprType>::make(arg.rhs()));
  }
};


#define DEFINE_BOOLEAN_EXPR2D(op)                                                                                          \
  template <typename LhsXprType, typename RhsXprType>                                                                      \
  struct Expr2d<CwiseBinaryOp<internal::scalar_boolean_##op##_op_nc<typename internal::traits<LhsXprType>::Scalar>, LhsXprType, RhsXprType>, true, false> {   \
    typedef typename Expr2d<const LhsXprType>::type LhsXprType2d;                                                          \
    typedef typename Expr2d<const RhsXprType>::type RhsXprType2d;                                                          \
    typedef typename internal::traits<LhsXprType>::Scalar LhsScalar;                                                       \
    typedef typename internal::wrap_scalar<LhsScalar>::ChannelType LhsChannelType;                                         \
                                                                                                                           \
    typedef CwiseBinaryOp<internal::scalar_boolean_##op##_op_nc<LhsScalar>, LhsXprType, RhsXprType> ArgType;               \
                                                                                                                           \
    typedef typename internal::conditional<                                                                                \
        internal::is_void<LhsXprType2d>::value || internal::is_void<RhsXprType2d>::value, void,                            \
        CwiseBinaryOp<internal::scalar_boolean_##op##_op, const LhsXprType2d, const RhsXprType2d> >::type type;            \
                                                                                                                           \
    static const type make(const ArgType& arg) {                                                                           \
      /* This seems to skip compilation in the void case, interesting. */                                                  \
      return type(Expr2d<const LhsXprType>::make(arg.lhs()), Expr2d<const RhsXprType>::make(arg.rhs()));                   \
    }                                                                                                                      \
  };

#define DEFINE_BITWISE_EXPR2D(op)                                                                                          \
  template <typename LhsXprType, typename RhsXprType>                                                                      \
  struct Expr2d<CwiseBinaryOp<internal::scalar_bitwise_##op##_op<typename internal::traits<LhsXprType>::Scalar>, LhsXprType, RhsXprType>, true, false> {   \
    typedef typename Expr2d<const LhsXprType>::type LhsXprType2d;                                                          \
    typedef typename Expr2d<const RhsXprType>::type RhsXprType2d;                                                          \
    typedef typename internal::traits<LhsXprType>::Scalar LhsScalar;                                                       \
    typedef typename internal::wrap_scalar<LhsScalar>::ChannelType LhsChannelType;                                         \
                                                                                                                           \
    typedef CwiseBinaryOp<internal::scalar_bitwise_##op##_op<LhsScalar>, LhsXprType, RhsXprType> ArgType;                  \
                                                                                                                           \
    typedef typename internal::conditional<                                                                                \
        internal::is_void<LhsXprType2d>::value || internal::is_void<RhsXprType2d>::value, void,                            \
        CwiseBinaryOp<internal::scalar_bitwise_##op##_op<LhsChannelType>, const LhsXprType2d, const RhsXprType2d> >::type type; \
                                                                                                                           \
    static const type make(const ArgType& arg) {                                                                           \
      /* This seems to skip compilation in the void case, interesting. */                                                  \
      return type(Expr2d<const LhsXprType>::make(arg.lhs()), Expr2d<const RhsXprType>::make(arg.rhs()));                   \
    }                                                                                                                      \
  };

template <typename LhsXprType, typename RhsXprType, internal::ComparisonName CmpType>
struct Expr2d<CwiseBinaryOp<internal::scalar_cmp_op<typename internal::traits<LhsXprType>::Scalar,
                                                    typename internal::traits<RhsXprType>::Scalar, CmpType>, LhsXprType, RhsXprType>, true, false> {
  typedef typename Expr2d<const LhsXprType>::type LhsXprType2d;
  typedef typename Expr2d<const RhsXprType>::type RhsXprType2d;

  typedef typename internal::wrap_scalar<typename internal::traits<LhsXprType>::Scalar>::ChannelType LhsChannelType;
  typedef typename internal::wrap_scalar<typename internal::traits<RhsXprType>::Scalar>::ChannelType RhsChannelType;

  typedef CwiseBinaryOp<internal::scalar_cmp_op<typename internal::traits<LhsXprType>::Scalar,
                                                typename internal::traits<RhsXprType>::Scalar, CmpType>, LhsXprType, RhsXprType> ArgType;

  typedef typename internal::conditional<
      internal::is_void<LhsXprType2d>::value || internal::is_void<RhsXprType2d>::value, void,
      CwiseBinaryOp<internal::scalar_cmp_op<LhsChannelType, RhsChannelType, CmpType>, const LhsXprType2d, const RhsXprType2d> >::type type;

  static const type make(const ArgType& arg) {
    /* This seems to skip compilation in the void case, interesting. */
    typedef typename internal::remove_all<decltype(arg.lhs())>::type LHS_T;
    typedef typename internal::remove_all<decltype(arg.rhs())>::type RHS_T;
    static_assert(LHS_T::SizeAtCompileTime == RHS_T::SizeAtCompileTime || LHS_T::SizeAtCompileTime == -1 || RHS_T::SizeAtCompileTime == -1);
    static_assert(LHS_T::RowsAtCompileTime == RHS_T::RowsAtCompileTime || LHS_T::RowsAtCompileTime == -1 || RHS_T::RowsAtCompileTime == -1);
    static_assert(LHS_T::ColsAtCompileTime == RHS_T::ColsAtCompileTime || LHS_T::ColsAtCompileTime == -1 || RHS_T::ColsAtCompileTime == -1);
    return type(Expr2d<const LhsXprType>::make(arg.lhs()), Expr2d<const RhsXprType>::make(arg.rhs()));
  }
};

DEFINE_BOOLEAN_EXPR2D(and)
DEFINE_BOOLEAN_EXPR2D(or)

DEFINE_BITWISE_EXPR2D(xor)
DEFINE_BITWISE_EXPR2D(and)
DEFINE_BITWISE_EXPR2D(or)

template <typename XprType, int N, int M, int Order>
struct Expr2d<Reshaped<XprType, N, M, Order>, true, false> {
  typedef typename Expr2d<const XprType>::type XprType2d;

  typedef typename internal::traits<XprType>::Scalar Scalar;
  typedef typename internal::wrap_scalar<Scalar>::ChannelType ChannelType;

  typedef Reshaped<XprType, N, M, Order> ArgType;

  enum { NumChannels = internal::wrap_scalar<Scalar>::SizeAtCompileTime };
  enum { IsRowMajor = internal::traits<XprType>::Flags & RowMajorBit };

  typedef typename internal::conditional<
      internal::is_void<XprType2d>::value, void,
      Reshaped<XprType2d,
        N == Dynamic ? Dynamic : (N != 1 && (!IsRowMajor || M == 1) ? N * NumChannels : N),
        M == Dynamic ? Dynamic : (M != 1 && (IsRowMajor || N == 1) ? M * NumChannels : M),
        Order> >::type type;

  static const type make(const ArgType& arg) {
    /* This seems to skip compilation in the void case, interesting. */
    return type(Expr2d<const XprType>::make(arg.nestedExpression()),
                N != 1 && (!IsRowMajor || M == 1) ? arg.rows() * NumChannels : arg.rows(),
                M != 1 && (IsRowMajor || N == 1) ? arg.cols() * NumChannels : arg.cols());
  }
};

template <typename XprType, template<typename, typename> class Functor, typename ResultType>
struct Expr2d<PartialReduxExpr<XprType, Functor<typename internal::traits<XprType>::Scalar, ResultType>,
    internal::traits<XprType>::Flags & RowMajorBit ? Vertical : Horizontal>, true, false> {
  typedef typename Expr2d<const XprType>::type XprType2d;

  typedef typename internal::traits<XprType>::Scalar Scalar;
  typedef typename internal::wrap_scalar<Scalar>::ChannelType InputChannelType;
  typedef typename internal::wrap_scalar<ResultType>::ChannelType ResultChannelType;

  enum { Direction = internal::traits<XprType>::Flags & RowMajorBit ? Vertical : Horizontal };

  typedef PartialReduxExpr<XprType, Functor<Scalar, ResultType>, Direction> ArgType;

  typedef typename internal::conditional<
      internal::is_void<XprType2d>::value, void,
      PartialReduxExpr<const XprType2d, Functor<InputChannelType, ResultChannelType>, Direction> >::type type;

  static const type make(const ArgType& arg) {
    /* This seems to skip compilation in the void case, interesting. */
    return type(Expr2d<const XprType>::make(arg.nestedExpression()));
  }
};

template <typename XprType, template<typename, typename> class Functor, typename ResultType>
struct Expr2d<PartialReduxExpr<XprType, Functor<typename internal::traits<XprType>::Scalar, ResultType>,
    internal::traits<XprType>::Flags & RowMajorBit ? Horizontal : Vertical>, true, false> {
  enum { Direction = internal::traits<XprType>::Flags & RowMajorBit ? Vertical : Horizontal };
  typedef PartialReduxExpr<XprType, Functor<typename internal::traits<XprType>::Scalar, ResultType>, Direction> ArgType;
  typedef void type; static void make(const ArgType&) {}
};

template <typename ConditionXprType, typename ThenXprType, typename ElseXprType>
struct Expr2d<SelectNC<ConditionXprType, ThenXprType, ElseXprType>, true, false> {
  typedef typename Expr2d<const ConditionXprType>::type ConditionXprType2d;
  typedef typename Expr2d<const ThenXprType>::type ThenXprType2d;
  typedef typename Expr2d<const ElseXprType>::type ElseXprType2d;

  typedef SelectNC<ConditionXprType, ThenXprType, ElseXprType> ArgType;

  typedef typename internal::conditional<
      internal::is_void<ConditionXprType2d>::value || internal::is_void<ThenXprType2d>::value || internal::is_void<ElseXprType2d>::value, void,
      Select<const ConditionXprType2d, const ThenXprType2d, const ElseXprType2d> >::type type;

  static const type make(const ArgType& arg) {
    /* This seems to skip compilation in the void case, interesting. */
    return type(Expr2d<const ConditionXprType>::make(arg.conditionMatrix()),
                Expr2d<const ThenXprType>::make(arg.thenMatrix()),
                Expr2d<const ElseXprType>::make(arg.elseMatrix()));
  }
};

template <typename XprType, typename IndexingExpr1, typename IndexingExpr2>
struct Expr2d<IndexedView<XprType, IndexingExpr1, IndexingExpr2>, true, false> {
  typedef IndexedView<XprType, IndexingExpr1, IndexingExpr2> ArgType;
  typedef void type; static void make(const ArgType&) {}
};

template <typename XprType, int BlockRows, int BlockCols, bool InnerPanel>
struct Expr2d<Block<XprType, BlockRows, BlockCols, InnerPanel>, true, false> {
  typedef typename Expr2d<const XprType>::type XprType2d;
  typedef Block<XprType, BlockRows, BlockCols, InnerPanel> ArgType;

  typedef typename internal::traits<XprType>::Scalar Scalar;
  enum { NumChannels = internal::wrap_scalar<Scalar>::SizeAtCompileTime };
  enum { IsRowMajor = internal::traits<XprType>::Flags & RowMajorBit };
  enum { N = internal::traits<XprType>::RowsAtCompileTime };
  enum { M = internal::traits<XprType>::ColsAtCompileTime };

  enum { BlockRows2d = (BlockRows == Dynamic ? Dynamic : (N != 1 && (IsRowMajor || M == 1) ? BlockRows * NumChannels : BlockRows))};
  enum { BlockCols2d = (BlockCols == Dynamic ? Dynamic : (M != 1 && (!IsRowMajor || N == 1) ? BlockCols * NumChannels : BlockCols))};

  typedef typename internal::conditional<
      internal::is_void<XprType2d>::value, void,
      Block<const XprType2d, BlockRows2d, BlockCols2d, InnerPanel> >::type type;

  static const type make(const ArgType& arg) {
    /* This seems to skip compilation in the void case, interesting. */
    return type(Expr2d<const XprType>::make(arg.nestedExpression()),
                (N != 1 && (IsRowMajor || M == 1)) ? arg.startRow() * NumChannels : arg.startRow(),
                (M != 1 && (!IsRowMajor || N == 1)) ? arg.startCol() * NumChannels : arg.startCol(),
                (N != 1 && (IsRowMajor || M == 1)) ? arg.rows() * NumChannels : arg.rows(),
                (M != 1 && (!IsRowMajor || N == 1)) ? arg.cols() * NumChannels : arg.cols());
  }
};

// TODO(ygitman): other expressions (reverse, transpose, ...)?

namespace internal {

#undef /***/ DEFINE_BOOLEAN_EXPR2D
#undef /***/ DEFINE_BITWISE_EXPR2D
#undef /***/ DECLARE_MAKE_FN
#undef /***/ MAKE_FN_ARG_TP
#undef /***/ GET_CONSTANTS
