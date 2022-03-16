/* Copyright (c) Facebook, Inc. and its affiliates. */

#define DEFINE_OP(op, cost)                                                                                                 \
  template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC                                                          \
  const auto op(const ArrayBaseNC<OtherDerived>& arg) const {                                                               \
    const auto& fn = [](const auto& x, const auto& y) EIGEN_LAMBDA_INLINE { return internal::ops::op(x, y); };              \
    return derived().binaryExpr(arg.derived(), internal::make_functor<cost>(fn));                                           \
  }

#define DEFINE_OPERATOR(op, cost)                                                                                           \
  template <typename OtherDerived>                                                                                          \
  EIGEN_STRONG_INLINE_DEVICE_FUNC const auto op(const ArrayBaseNC<OtherDerived>& arg) const {                               \
    const auto& fn = [](const auto& x, const auto& y) EIGEN_LAMBDA_INLINE { return x.op(y); };                              \
    return derived().binaryExpr(arg.derived(), internal::make_functor<cost>(fn));                                           \
  }

DEFINE_OPERATOR(operator ==, NumTraits<Scalar>::AddCost)
DEFINE_OPERATOR(operator !=, NumTraits<Scalar>::AddCost)
DEFINE_OPERATOR(operator <=, NumTraits<Scalar>::AddCost)
DEFINE_OPERATOR(operator >=, NumTraits<Scalar>::AddCost)
DEFINE_OPERATOR(operator <, NumTraits<Scalar>::AddCost)
DEFINE_OPERATOR(operator >, NumTraits<Scalar>::AddCost)

DEFINE_OPERATOR(operator +, NumTraits<Scalar>::AddCost)
DEFINE_OPERATOR(operator -, NumTraits<Scalar>::AddCost)
DEFINE_OPERATOR(operator *, NumTraits<Scalar>::MulCost)
DEFINE_OPERATOR(operator /, NumTraits<Scalar>::MulCost)
DEFINE_OPERATOR(operator &, NumTraits<Scalar>::MulCost)
DEFINE_OPERATOR(operator |, NumTraits<Scalar>::MulCost)
DEFINE_OPERATOR(operator ^, NumTraits<Scalar>::MulCost)

DEFINE_OP(pow, 5 * NumTraits<Scalar>::MulCost)

DEFINE_OP(min, NumTraits<Scalar>::AddCost)
DEFINE_OP(max, NumTraits<Scalar>::AddCost)

#undef DEFINE_OPERATOR
#undef DEFINE_OP
