/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC const ChannelwiseOp<const Derived> channelwise() const
  { return ChannelwiseOp<const Derived>(derived()); }

EIGEN_STRONG_INLINE_DEVICE_FUNC ChannelwiseOp<Derived> channelwise()
  { return ChannelwiseOp<Derived>(derived()); }
