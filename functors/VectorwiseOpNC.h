/* Copyright (c) Facebook, Inc. and its affiliates. */

#define IsVecAlongDirection \
  (D == Horizontal && Tp::RowsAtCompileTime == 1) || (D == Vertical && Tp::ColsAtCompileTime == 1)

template <int D, typename Tp, typename Func, bool = IsVecAlongDirection> struct pReduxHelper;

template <int D, typename Tp, typename Func>
struct pReduxHelper<D, Tp, Func, 0> {
  static EIGEN_STRONG_INLINE_DEVICE_FUNC auto apply(const Tp& arg, const Func& fn)
    { return PartialReduxExpr<const Tp, Func, D>(arg, fn); }
};

template <int D, typename Tp, typename Func>
struct pReduxHelper<D, Tp, Func, 1> {
  static EIGEN_STRONG_INLINE_DEVICE_FUNC auto apply(const Tp& arg, const Func& fn)
    { return fn(arg); }
};

template <typename Tp, bool value = std::is_base_of<DenseBase<Tp>, Tp>::value>
struct ApplyCellwise;

template <int D, typename Tp, typename Func>
EIGEN_STRONG_INLINE_DEVICE_FUNC auto pRedux(const Tp& arg, const Func& fn)
  { return pReduxHelper<D, Tp, Func>::apply(arg, fn); }

template <typename Tp>
EIGEN_STRONG_INLINE_DEVICE_FUNC auto apply_cellwise(const Tp& arg)
  { return ApplyCellwise<Tp>(arg).get(); }

template <typename Tp> struct ApplyCellwise<Tp, 1> {
  EIGEN_STRONG_INLINE_DEVICE_FUNC
  auto get() const { return m_arg.cellwise(); }
  EIGEN_STRONG_INLINE_DEVICE_FUNC
  ApplyCellwise(const Tp& arg) : m_arg(arg) {}
  const Tp& m_arg;
};

template <typename Tp> struct ApplyCellwise<Tp, 0> {
  EIGEN_STRONG_INLINE_DEVICE_FUNC
  ApplyCellwise(const Tp& arg) : m_arg(arg) {}
  EIGEN_STRONG_INLINE_DEVICE_FUNC
  auto get() const { return m_arg; }
  const Tp& m_arg;
};

}  // namespace internal

#if !EIGEN_VERSION_AT_LEAST(3, 4, 9)
template <typename XprTp, int Direction>
struct VectorwiseOpProxy : VectorwiseOp<XprTp, Direction> {
# define VECTORWISE_OP VectorwiseOpProxy<ExpressionType, D>
  using VectorwiseOp<XprTp, Direction>::VectorwiseOp;
# include "../EigenVectorwiseopPlugin.h"
};
#else
# define VECTORWISE_OP VectorwiseOp<ExpressionType, D>
#endif

template<typename ExpressionType, int D>
struct VectorwiseOpNC : VECTORWISE_OP {
#define DEFINE_OP(op, v1, v2)                                                                                     \
  EIGEN_STRONG_INLINE_DEVICE_FUNC auto op() const {                                                               \
    const auto& fn = [](const auto& slice) EIGEN_LAMBDA_INLINE { return internal::apply_cellwise(slice).op(); };  \
    typedef decltype(fn(std::declval<ExpressionType>().template sliceAlong<D>(std::declval<Index>()))) T;         \
    return internal::pRedux<D>(this->_expression(), internal::make_redux_functor<v1, v2, T>(fn));           \
  }

  typedef typename ExpressionType::Scalar Scalar;

  DEFINE_OP(maxCoeff, NumTraits<Scalar>::AddCost, 0)
  DEFINE_OP(minCoeff, NumTraits<Scalar>::AddCost, 0)
  DEFINE_OP(count, NumTraits<Scalar>::AddCost, 0)
  DEFINE_OP(prod, NumTraits<Scalar>::MulCost, 0)
  DEFINE_OP(sum, NumTraits<Scalar>::AddCost, 0)
  DEFINE_OP(all, NumTraits<Scalar>::AddCost, 0)
  DEFINE_OP(any, NumTraits<Scalar>::AddCost, 0)

  typedef VECTORWISE_OP Base;
  using Base::Base;
};

namespace internal {

#undef IsVecAlongDirection
#undef VECTORWISE_OP
#undef DEFINE_OP
