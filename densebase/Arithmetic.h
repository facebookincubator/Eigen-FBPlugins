/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:
  enum { Is1x1AndNotProduct = (SizeAtCompileTime == 1 && !internal::is_product_expr<Derived>::value) };
  struct NONE { /*private class to disable implicit conversion to Scalar*/ };
  typedef internal::conditional<Is1x1AndNotProduct, Scalar, NONE> SType;

 public:
  EIGEN_STRONG_INLINE_DEVICE_FUNC operator typename SType::type() const { return derived().coeff(0); }
