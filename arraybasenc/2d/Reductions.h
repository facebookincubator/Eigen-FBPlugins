/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC auto mean() const
  { return derived().sum() / (derived().size() * derived().channels()); }

template<typename BinaryFunc> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto redux(const BinaryFunc& fn) const
  { return derived().as2d().redux(fn); }

#define DEFINE_REDUX_FN(fn)                       \
  EIGEN_STRONG_INLINE_DEVICE_FUNC auto fn() const \
    { return derived().as2d().fn(); }

EIGEN_STRONG_INLINE_DEVICE_FUNC auto all() const
  { return derived().as2d().all(); }

EIGEN_STRONG_INLINE_DEVICE_FUNC auto any() const
  { return derived().as2d().any(); }

// TODO(ygitman): override visit?

DEFINE_REDUX_FN(maxCoeff)
DEFINE_REDUX_FN(minCoeff)
DEFINE_REDUX_FN(prod)
DEFINE_REDUX_FN(sum)

#undef DEFINE_REDUX_FN
