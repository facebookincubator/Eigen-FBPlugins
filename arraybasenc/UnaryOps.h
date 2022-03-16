/* Copyright (c) Facebook, Inc. and its affiliates. */

#define DEFINE_OPERATOR(op, cost)                       \
  EIGEN_STRONG_INLINE_DEVICE_FUNC const auto op() const \
    { return derived().unaryExpr(internal::make_functor<cost>([](const auto& x) EIGEN_LAMBDA_INLINE { return x.op(); })); }

DEFINE_OPERATOR(operator -, NumTraits<Scalar>::AddCost)

#undef DEFINE_OPERATOR
