/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC ChannelType mean() const
  { return derived().sum() / (derived().size() * derived().channels()); }

template<typename BinaryFunc> EIGEN_STRONG_INLINE_DEVICE_FUNC
ChannelType redux(const BinaryFunc& fn) const
  { return derived().as2d().redux(fn); }

EIGEN_STRONG_INLINE_DEVICE_FUNC bool all() const
  { return derived().as2d().all(); }

EIGEN_STRONG_INLINE_DEVICE_FUNC bool any() const
  { return derived().as2d().any(); }

#define /**/ DEFINE_REDUX_FN(ReturnType, fn)                          \
  EIGEN_STRONG_INLINE_DEVICE_FUNC ReturnType fn() const               \
    { return derived().as2d().fn(); }

// TODO(ygitman): override visit?

DEFINE_REDUX_FN(ChannelType, maxCoeff)
DEFINE_REDUX_FN(ChannelType, minCoeff)
DEFINE_REDUX_FN(ChannelType, prod)
DEFINE_REDUX_FN(ChannelType, sum)

#undef /***/ DEFINE_REDUX_FN
