/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC Derived& operator +=(const ChannelType& scalar)
  { return *this += Derived::Constant(derived().rows(), derived().cols(), scalar); }

EIGEN_STRONG_INLINE_DEVICE_FUNC Derived& operator -=(const ChannelType& scalar)
  { return *this -= Derived::Constant(derived().rows(), derived().cols(), scalar); }

EIGEN_STRONG_INLINE_DEVICE_FUNC Derived& operator *=(const ChannelType& scalar)
  { return *this *= Derived::Constant(derived().rows(), derived().cols(), scalar); }

EIGEN_STRONG_INLINE_DEVICE_FUNC Derived& operator /=(const ChannelType& scalar)
  { return *this /= Derived::Constant(derived().rows(), derived().cols(), scalar); }

EIGEN_STRONG_INLINE_DEVICE_FUNC Derived& operator =(const ChannelType& value)
  { setConstant(value); return derived(); }
