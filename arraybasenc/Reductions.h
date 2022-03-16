/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC auto mean() const
  { return derived().sum() / (derived().size() * derived().channels()); }

template<typename BinaryFunc> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto redux(const BinaryFunc& fn) const
  { return derived().channelwise().redux(fn).redux(fn); }

#define DEFINE_REDUX_FN(fn)                          \
  EIGEN_STRONG_INLINE_DEVICE_FUNC auto fn() const    \
    { return derived().channelwise().fn().fn(); }

// TODO(ygitman): override visit?

DEFINE_REDUX_FN(maxCoeff)
DEFINE_REDUX_FN(minCoeff)
DEFINE_REDUX_FN(prod)
DEFINE_REDUX_FN(sum)
DEFINE_REDUX_FN(all)
DEFINE_REDUX_FN(any)

#undef DEFINE_REDUX_FN
