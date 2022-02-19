/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC
operator std::conditional_t<SizeAtCompileTime == 1 && !internal::is_product_expr<Derived>::value, Scalar, internal::NoneType<Scalar>>() const
  { return derived().coeff(0); }
