/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename T> EIGEN_STRONG_INLINE_DEVICE_FUNC auto operator[] (const T& idx) const
  -> typename std::enable_if_t<!std::is_convertible<T, Index>::value && SizeAtCompileTime == RowsAtCompileTime && ColsAtCompileTime == 1,
                                  decltype(this->derived()(idx, Eigen::indexing::all))>
  { return this->derived()(idx, Eigen::indexing::all); }

template <typename T> EIGEN_STRONG_INLINE_DEVICE_FUNC auto operator[] (const T& idx) const
  -> typename std::enable_if_t<!std::is_convertible<T, Index>::value && SizeAtCompileTime == ColsAtCompileTime && RowsAtCompileTime == 1,
                                  decltype(this->derived()(Eigen::indexing::all, idx))>
  { return this->derived()(Eigen::indexing::all, idx); }

template <typename T> EIGEN_STRONG_INLINE_DEVICE_FUNC auto operator[] (const T& idx)
  -> typename std::enable_if_t<!std::is_convertible<T, Index>::value && SizeAtCompileTime == RowsAtCompileTime && ColsAtCompileTime == 1,
                                  decltype(this->derived()(idx, Eigen::indexing::all))>
  { return this->derived()(idx, Eigen::indexing::all); }

template <typename T> EIGEN_STRONG_INLINE_DEVICE_FUNC auto operator[] (const T& idx)
  -> typename std::enable_if_t<!std::is_convertible<T, Index>::value && SizeAtCompileTime == ColsAtCompileTime && RowsAtCompileTime == 1,
                                  decltype(this->derived()(Eigen::indexing::all, idx))>
  { return this->derived()(Eigen::indexing::all, idx); }
