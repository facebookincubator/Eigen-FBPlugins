/* Copyright (c) Facebook, Inc. and its affiliates. */

template <int p> EIGEN_STRONG_INLINE_DEVICE_FUNC
typename NumTraits<ChannelType>::Real lpNorm() const
EIGEN_REQUIRES(p >= 0 || p == Infinity) {
  if (p > 2 && p != Infinity) {
    return numext::pow(derived().abs().pow(p).sum(),
                       ChannelType(1.0 / p));
  } else if (p == Infinity) {
    return derived().abs().maxCoeff();
  } else if (p == 1) {
    return derived().abs().sum();
  } else if (p == 2) {
    return derived().norm();
  } else {
    return 0;
  }
}

#define DEFINE_NORMALIZED_FUNCS(norm_func)        \
  EIGEN_STRONG_INLINE_DEVICE_FUNC                 \
  void norm_func##alize() {                       \
    auto q = derived().norm_func();               \
    if (q) { derived() /= q; }                    \
  }                                               \
                                                  \
  EIGEN_STRONG_INLINE_DEVICE_FUNC                 \
  auto norm_func##alized() const {                \
    auto A = derived().nested_eval<2>();          \
    auto q = A.norm_func();                       \
                                                  \
    if (q != 0) {                                 \
      return (A / q).eval();                      \
    } else {                                      \
      return A.eval();                            \
    }                                             \
  }

DEFINE_NORMALIZED_FUNCS(stableNorm)
DEFINE_NORMALIZED_FUNCS(norm)

#undef DEFINE_NORMALIZED_FUNCS

EIGEN_STRONG_INLINE_DEVICE_FUNC
auto norm() const { return numext::sqrt(derived().squaredNorm()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
auto squaredNorm() const { return derived().square().sum(); }

EIGEN_STRONG_INLINE_DEVICE_FUNC
auto stableNorm() const {
  typedef typename NumTraits<ChannelType>::Real Type;
  auto A = derived().nested_eval<2>();
  Type maxCoeff = A.abs().maxCoeff();
  if (maxCoeff != 0)
    return maxCoeff * (A / maxCoeff).norm();
  return Type(0);
}

// TODO(ygitman): implement homogeneous
// TODO(ygitman): implement hnormalized
// TODO(ygitman): implement hypotNorm
// TODO(ygitman): implement blueNorm
// TODO(ygitman): zero checks?
