/* Copyright (c) Facebook, Inc. and its affiliates. */

}  // namespace internal

#define DEFINE_FUNC(op)                                                                                                 \
  template <typename Tp, typename XprType, EIGEN_ENABLE_IF_PROMOTABLE(typename XprType::ChannelType, Tp)>               \
  EIGEN_STRONG_INLINE_DEVICE_FUNC auto op(const Tp& y, const Eigen::ArrayBaseNC<XprType>& x)                            \
    { return XprType::Constant(x.rows(), x.cols(),                                                                      \
                               static_cast<typename XprType::ChannelType>(y)).op(x.derived()); }

DEFINE_FUNC(pow)

#undef DEFINE_FUNC

namespace internal {
