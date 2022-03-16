/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Tp, bool value = std::is_base_of<DenseBase<Tp>, Tp>::value>
struct ApplyCellwise;

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
    return partialReduxHelper(this->_expression(), internal::make_redux_functor<v1, v2, T>(fn));                  \
  }

  template <typename Tp, typename Func>
  EIGEN_STRONG_INLINE_DEVICE_FUNC auto partialReduxHelper(const Tp& arg, const Func& fn) const
    { return PartialReduxExpr<const Tp, Func, D>(arg, fn); }

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

#undef VECTORWISE_OP
#undef DEFINE_OP
};

namespace internal {
