/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename EnableIf=void>
EIGEN_STRONG_INLINE_DEVICE_FUNC EIGEN_ENABLE_IFF_NC(Array)& operator =(const ChannelType& value)
  { Base::setConstant(value); return *this; }
