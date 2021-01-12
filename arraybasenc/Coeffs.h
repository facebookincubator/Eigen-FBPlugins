/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC ChannelType& operator()(Index row, Index col, Index channel)
  { eigen_assert(0 <= row && row < derived().rows());
    eigen_assert(0 <= col && col < derived().cols());
    eigen_assert(channel <= derived().channels());
    return coeffRef(row, col, channel); }

EIGEN_STRONG_INLINE_DEVICE_FUNC ChannelType& coeffRef(Index row, Index col, Index channel)
  { return *((ChannelType*) &derived().coeffRef(row, col) + channel); }

using DenseCoeffsBase<Derived, internal::accessors_level<Derived>::value>::coeffRef;
using DenseBase<Derived>::operator();
