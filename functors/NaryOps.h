/* Copyright (c) Facebook, Inc. and its affiliates. */

#if /***/ EIGEN_HAS_CXX14
}  // namespace internal

// TODO(ygitman): Make recursion depth logarithmic as it is more efficient

template <typename Tp, typename ...Args> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto min(const ArrayBase<Tp>& arg, const ArrayBase<Args>& ...other_args) {
  return arg.min(min(other_args...));
}

template <typename Tp, typename ...Args> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto max(const ArrayBase<Tp>& arg, const ArrayBase<Args>& ...other_args) {
  return arg.max(max(other_args...));
}

template <typename Tp1, typename Tp2> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto min(const ArrayBase<Tp1>& arg1, const ArrayBase<Tp2>& arg2) {
  return arg1.derived().min(arg2.derived());
}

template <typename Tp1, typename Tp2> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto max(const ArrayBase<Tp1>& arg1, const ArrayBase<Tp2>& arg2) {
  return arg1.derived().max(arg2.derived());
}

namespace /***/ internal {
#endif // EIGEN_HAS_CXX14
