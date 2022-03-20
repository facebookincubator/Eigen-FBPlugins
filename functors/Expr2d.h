/* Copyright (c) Facebook, Inc. and its affiliates. */

}  // namespace internal

template <typename T, bool v> struct Expr2d<T, false, v> {
  EIGEN_STRONG_INLINE_DEVICE_FUNC
  static auto make(std::conditional_t<internal::traits<T>::Flags & LvalueBit, T, const T>& arg)
    { return arg; }

  static constexpr bool value = true;
};

template <typename ExprType>
struct Expr2d<const ExprType, true, false> : Expr2d<ExprType, true, false>
  { static constexpr bool value = Expr2d<ExprType, true, false>::value; };

#ifdef __cpp_nontype_template_parameter_auto
#  define DECLARE_OTHER_ARGS , auto... OtherArgs
#  define DECLARE_OTHER_ARGS_NAMELESS , auto...
#  define EXPAND_OTHER_ARGS , OtherArgs...
#else
#  define DECLARE_OTHER_ARGS , int... OtherArgs
#  define DECLARE_OTHER_ARGS_NAMELESS , int...
#  define EXPAND_OTHER_ARGS , OtherArgs...
#endif

#define GET_CONSTANTS(T)                                                                   \
  static constexpr bool IsRowMajor = bool((int) internal::traits<T>::Flags & RowMajorBit); \
  static constexpr bool IsLvalue = bool((int) internal::traits<T>::Flags & LvalueBit);     \
                                                                                           \
  static constexpr int S = internal::traits<T>::OuterStrideAtCompileTime;                  \
  static constexpr int P = internal::traits<T>::MaxRowsAtCompileTime;                      \
  static constexpr int Q = internal::traits<T>::MaxColsAtCompileTime;                      \
  static constexpr int N = internal::traits<T>::RowsAtCompileTime;                         \
  static constexpr int M = internal::traits<T>::ColsAtCompileTime;                         \
  static constexpr int Alignment = internal::traits<T>::Alignment;                         \
  static constexpr int OuterDim = (IsRowMajor ? M : N);                                    \
                                                                                           \
  typedef typename internal::traits<T>::Scalar Scalar;                                     \
                                                                                           \
  EIGEN_IMPORT_CHANNELTYPE(Scalar);                                                        \
  EIGEN_IMPORT_NUMCHANNELS(Scalar);                                                        \
                                                                                           \
  static constexpr int N2 = ((N == Dynamic) ? Dynamic : IsRowMajor ? N : N * NumChannels); \
  static constexpr int M2 = ((M == Dynamic) ? Dynamic : IsRowMajor ? M * NumChannels : M); \
  static constexpr int P2 = ((P == Dynamic) ? Dynamic : IsRowMajor ? P : P * NumChannels); \
  static constexpr int Q2 = ((Q == Dynamic) ? Dynamic : IsRowMajor ? Q * NumChannels : Q); \
  static constexpr bool NoOuterStride = bool((S != Dynamic) && (S == OuterDim));           \
  static constexpr int S2 = (S == Dynamic ? Dynamic : (S * NumChannels));                  \
  static constexpr int Flags2 = (IsRowMajor ? RowMajorBit : 0);                            \
                                                                                           \
  typedef Array<ChannelType, N2, M2, Flags2, P2, Q2> PlainObj2;

template <typename T>
struct Expr2d<T, true, true> {
  GET_CONSTANTS(T)

  static constexpr int value = (internal::traits<T>::InnerStrideAtCompileTime == 1);

  template <typename EnableIf=void, std::enable_if_t<std::is_same<EnableIf, void>::value && value, int> = 0>
  EIGEN_STRONG_INLINE_DEVICE_FUNC static auto make(std::conditional_t<IsLvalue, T, const T>& arg) {
    typedef std::conditional_t<NoOuterStride, Stride<0, 0>, Stride<S2, 0>> StrideType;
    typedef std::conditional_t<IsLvalue, PlainObj2, const PlainObj2> PlainObjectType;

    typedef Map<PlainObjectType, Alignment, StrideType> X;
    typedef std::conditional_t<IsLvalue, X, const X> type;

    if (NoOuterStride) {
      return type((ChannelType*) arg.data(), IsRowMajor ? arg.rows() : arg.rows() * NumChannels, IsRowMajor ? arg.cols() * NumChannels : arg.cols());
    } else {
      return type((ChannelType*) arg.data(), IsRowMajor ? arg.rows() : arg.rows() * NumChannels, IsRowMajor ? arg.cols() * NumChannels : arg.cols(),
                  std::conditional_t<NoOuterStride, Stride<0, 0>, Stride<S2, 0>>(arg.outerStride() * NumChannels, 0));
    }
  }
};

template <typename Functor, typename T1, typename T2, typename T3, int cost>
struct Expr2d<CwiseTernaryOp<internal::LambdaFunctor<cost, Functor>, T1, T2, T3>, true, false> {
  typedef CwiseTernaryOp<internal::LambdaFunctor<cost, Functor>, T1, T2, T3> ArgType;
  static constexpr bool arg1_has_expr2d = Expr2d<const T1>::value;
  static constexpr bool arg2_has_expr2d = Expr2d<const T2>::value;
  static constexpr bool arg3_has_expr2d = Expr2d<const T3>::value;
  EIGEN_IMPORT_NUMCHANNELS(typename internal::traits<T1>::Scalar);

  static constexpr bool value = arg1_has_expr2d && arg2_has_expr2d && arg3_has_expr2d;

  template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
  static const auto make(const std::enable_if_t<std::is_same<EnableIf, void>::value && value, ArgType>& v)
    { return v.functor().template operator()<0>(Expr2d<const T1>::make(v.arg1()), Expr2d<const T2>::make(v.arg2()), Expr2d<const T3>::make(v.arg3())); }
};

template <typename Functor, typename LhsXprType, typename RhsXprType, int cost>
struct Expr2d<CwiseBinaryOp<internal::LambdaFunctor<cost, Functor>, LhsXprType, RhsXprType>, true, false> {
  typedef CwiseBinaryOp<internal::LambdaFunctor<cost, Functor>, LhsXprType, RhsXprType> ArgType;
  EIGEN_IMPORT_NUMCHANNELS(typename internal::traits<LhsXprType>::Scalar);
  static constexpr bool lhs_has_expr2d = Expr2d<const LhsXprType>::value;
  static constexpr bool rhs_has_expr2d = Expr2d<const RhsXprType>::value;
  static constexpr bool value = lhs_has_expr2d && rhs_has_expr2d;

  template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
  static const auto make(const std::enable_if_t<std::is_same<EnableIf, void>::value && value, ArgType>& v)
    { return v.functor().template operator()<0>(Expr2d<const LhsXprType>::make(v.lhs()), Expr2d<const RhsXprType>::make(v.rhs())); }
};

template <typename Functor, typename XprType, int cost>
struct Expr2d<CwiseUnaryOp<internal::LambdaFunctor<cost, Functor>, XprType>, true, false> {
  typedef CwiseUnaryOp<internal::LambdaFunctor<cost, Functor>, XprType> ArgType;
  static constexpr bool value = Expr2d<const XprType>::value;
  typedef typename internal::traits<XprType>::Scalar Scalar;
  EIGEN_IMPORT_NUMCHANNELS(Scalar);

  template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
  static const auto make(const std::enable_if_t<std::is_same<EnableIf, void>::value && value, ArgType>& v)
    { return v.functor().template operator()<0>(Expr2d<const XprType>::make(v.nestedExpression())); }
};

template <template<typename, typename DECLARE_OTHER_ARGS_NAMELESS> class Functor,
          typename LhsXprType, typename RhsXprType, typename T1, typename T2 DECLARE_OTHER_ARGS>
struct Expr2d<CwiseBinaryOp<Functor<T1, T2 EXPAND_OTHER_ARGS>, LhsXprType, RhsXprType>, true, false> {
  typedef typename internal::wrap_scalar<typename internal::traits<LhsXprType>::Scalar>::ChannelType X1;
  typedef typename internal::wrap_scalar<typename internal::traits<RhsXprType>::Scalar>::ChannelType X2;
  typedef CwiseBinaryOp<Functor<T1, T2 EXPAND_OTHER_ARGS>, LhsXprType, RhsXprType> ArgType;
  static constexpr bool lhs_has_expr2d = Expr2d<const LhsXprType>::value;
  static constexpr bool rhs_has_expr2d = Expr2d<const RhsXprType>::value;
  static constexpr bool value = lhs_has_expr2d && rhs_has_expr2d;

  template <typename Tp1, typename Tp2> EIGEN_STRONG_INLINE_DEVICE_FUNC static const auto makeHelper(const Tp1& arg1, const Tp2& arg2)
    { return CwiseBinaryOp<Functor<X1, X2 EXPAND_OTHER_ARGS>, const Tp1, const Tp2>(arg1, arg2); }

  template <typename EnableIf=void, std::enable_if_t<std::is_same<EnableIf, void>::value && value, int> = 0>
  EIGEN_STRONG_INLINE_DEVICE_FUNC static const auto make(const ArgType& v)
    { return makeHelper(Expr2d<const LhsXprType>::make(v.lhs()), Expr2d<const RhsXprType>::make(v.rhs())); }
};

template <template<typename DECLARE_OTHER_ARGS_NAMELESS> class Functor, typename XprType DECLARE_OTHER_ARGS>
struct Expr2d<CwiseUnaryOp<Functor<typename internal::traits<XprType>::Scalar EXPAND_OTHER_ARGS>, XprType>, true, false> {
  typedef CwiseUnaryOp<Functor<typename internal::traits<XprType>::Scalar EXPAND_OTHER_ARGS>, XprType> ArgType;
  EIGEN_IMPORT_CHANNELTYPE(typename internal::traits<XprType>::Scalar);
  static constexpr bool value = Expr2d<const XprType>::value;

  template <typename Tp> EIGEN_STRONG_INLINE_DEVICE_FUNC static const auto makeHelper(const Tp& arg)
    { return CwiseUnaryOp<Functor<ChannelType EXPAND_OTHER_ARGS>, const Tp>(arg); }

  template <typename EnableIf=void, std::enable_if_t<std::is_same<EnableIf, void>::value && value, int> = 0>
  EIGEN_STRONG_INLINE_DEVICE_FUNC static const auto make(const ArgType& arg)
    { return makeHelper(Expr2d<const XprType>::make(arg.nestedExpression())); }
};

template <template <typename> class Func, typename PlainObjectType, typename ScalarType>
struct Expr2d<CwiseNullaryOp<Func<ScalarType>, PlainObjectType>, true, false> {
  typedef CwiseNullaryOp<Func<ScalarType>, PlainObjectType> ArgType;
  static constexpr bool value = true;
  GET_CONSTANTS(PlainObjectType)

  EIGEN_STRONG_INLINE_DEVICE_FUNC static const auto make(const ArgType& arg) {
    const Index rows = arg.rows() * (IsRowMajor ? 1 : NumChannels);
    const Index cols = arg.cols() * (IsRowMajor ? NumChannels : 1);
    return CwiseNullaryOp<Func<ChannelType>, PlainObj2>(rows, cols, arg.functor());
  }
};

template <typename XprType, int N, int M, int Order>
struct Expr2d<Reshaped<XprType, N, M, Order>, true, false> {
  static constexpr bool IsRowMajor = (internal::traits<XprType>::Flags & RowMajorBit);

  static constexpr Index getRows(Index v)
    { return (N != 1 && (!IsRowMajor || M == 1) ? v * NumChannels : v); }

  static constexpr Index getCols(Index v)
    { return (M != 1 && (IsRowMajor || N == 1) ? v * NumChannels : v); }

  static constexpr bool value = Expr2d<const XprType>::value;
  typedef typename internal::traits<XprType>::Scalar Scalar;
  EIGEN_IMPORT_NUMCHANNELS(Scalar);

  static constexpr int V1 = N == Dynamic ? Dynamic : getRows(N);
  static constexpr int V2 = M == Dynamic ? Dynamic : getCols(M);

  typedef Reshaped<XprType, N, M, Order> ArgType;

  template <typename Tp> EIGEN_STRONG_INLINE_DEVICE_FUNC static const auto makeHelper(const Tp& v, Index rows, Index cols)
    { return Reshaped<const Tp, V1, V2, Order>(v, rows, cols); }

  template <typename EnableIf=void, std::enable_if_t<std::is_same<EnableIf, void>::value && value, int> = 0>
  EIGEN_STRONG_INLINE_DEVICE_FUNC static const auto make(const ArgType& v)
    { return makeHelper(Expr2d<const XprType>::make(v.nestedExpression()), getRows(v.rows()), getCols(v.cols())); }
};

template <typename XprType, int BlockRows, int BlockCols, bool InnerPanel>
struct Expr2d<Block<XprType, BlockRows, BlockCols, InnerPanel>, true, false> {
  typedef Block<XprType, BlockRows, BlockCols, InnerPanel> ArgType;
  static constexpr bool value = Expr2d<const XprType>::value;
  GET_CONSTANTS(XprType)

  static constexpr Index getRows(Index v)
    { return (N != 1 && (!IsRowMajor || M == 1) ? v * NumChannels : v); }

  static constexpr Index getCols(Index v)
    { return (M != 1 && (IsRowMajor || N == 1) ? v * NumChannels : v); }

  static constexpr int BlockRows2d = (BlockRows == Dynamic ? Dynamic : getRows(BlockRows));
  static constexpr int BlockCols2d = (BlockCols == Dynamic ? Dynamic : getCols(BlockCols));

  template <typename Tp> EIGEN_STRONG_INLINE_DEVICE_FUNC
  static const auto makeHelper(const Tp& v, int startRow, int startCol, int rows, int cols)
    { return Block<const Tp, BlockRows2d, BlockCols2d, InnerPanel>(v, startRow, startCol, rows, cols); }

  template <typename EnableIf=void, std::enable_if_t<std::is_same<EnableIf, void>::value && value, int> = 0>
  EIGEN_STRONG_INLINE_DEVICE_FUNC static const auto make(const ArgType& v)
    { return makeHelper(Expr2d<const XprType>::make(v.nestedExpression()),
                        getRows(v.startRow()), getCols(v.startCol()),
                        getRows(v.rows()), getCols(v.cols())); }
};

template <typename T, class ReduxFunctor>
struct Expr2d<PartialReduxExpr<T, ReduxFunctor, internal::traits<T>::Flags & RowMajorBit ? Vertical : Horizontal>, true, false> {
  typedef PartialReduxExpr<T, ReduxFunctor, internal::traits<T>::Flags & RowMajorBit ? Vertical : Horizontal> ArgType;
  static constexpr bool value = Expr2d<const T>::value;

  template <typename EnableIf=void> EIGEN_STRONG_INLINE_DEVICE_FUNC
  static const auto make(const std::enable_if_t<std::is_same<EnableIf, void>::value && value, ArgType>& arg)
    { return arg.functor()(Expr2d<const T>::make(arg.nestedExpression()).alongOuterDim()); }
};

// Expressions below aren't possible to do in 2D world without some very fancy indexing

template <typename XprType, typename Functor>
struct Expr2d<PartialReduxExpr<XprType, Functor, internal::traits<XprType>::Flags & RowMajorBit ? Horizontal : Vertical>, true, false>
  { static constexpr bool value = false; };

template <typename XprType, typename Func, int v, int cnd>
struct Expr2d<CwiseUnaryOp<internal::ChannelwiseFunctor<v, cnd, Func>, XprType>, true, false>
  { static constexpr bool value = false; };

template <typename XprType, typename IndexingExpr1, typename IndexingExpr2>
struct Expr2d<IndexedView<XprType, IndexingExpr1, IndexingExpr2>, true, false>
  { static constexpr bool value = false; };

// TODO(ygitman): other expressions (reverse, transpose, ...)?

namespace internal {

#undef DECLARE_OTHER_ARGS_NAMELESS
#undef DECLARE_OTHER_ARGS
#undef EXPAND_OTHER_ARGS
#undef GET_CONSTANTS
