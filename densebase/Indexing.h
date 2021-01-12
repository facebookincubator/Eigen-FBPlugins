/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename T> auto operator[] (const T& idx) const
  -> typename internal::enable_if<!internal::is_convertible<T, Index>::value && SizeAtCompileTime == RowsAtCompileTime && ColsAtCompileTime == 1,
                                  decltype(derived()(idx, Eigen::all))>::type { return derived()(idx, Eigen::all); }

template <typename T> auto operator[] (const T& idx) const
  -> typename internal::enable_if<!internal::is_convertible<T, Index>::value && SizeAtCompileTime == ColsAtCompileTime && RowsAtCompileTime == 1,
                                  decltype(derived()(Eigen::all, idx))>::type { return derived()(Eigen::all, idx); }

template <typename T> auto operator[] (const T& idx) /***/
  -> typename internal::enable_if<!internal::is_convertible<T, Index>::value && SizeAtCompileTime == RowsAtCompileTime && ColsAtCompileTime == 1,
                                  decltype(derived()(idx, Eigen::all))>::type { return derived()(idx, Eigen::all); }

template <typename T> auto operator[] (const T& idx) /***/
  -> typename internal::enable_if<!internal::is_convertible<T, Index>::value && SizeAtCompileTime == ColsAtCompileTime && RowsAtCompileTime == 1,
                                  decltype(derived()(Eigen::all, idx))>::type { return derived()(Eigen::all, idx); }

#if /***/ EIGEN_VERSION_AT_LEAST(3, 3, 9)

template <typename T> auto operator()(const T& idx, const char (&)[1]) const
  -> typename internal::enable_if<!internal::is_same<T, char[1]>::value, decltype(derived()(idx, Eigen::all))>::type
  { return derived()(idx, Eigen::all); }

template <typename T> auto operator()(const char (&)[1], const T& idx) const
  -> typename internal::enable_if<!internal::is_same<T, char[1]>::value, decltype(derived()(Eigen::all, idx))>::type
  { return derived()(Eigen::all, idx); }

template <typename T> auto operator()(const T& idx, const char (&)[1]) /***/
  -> typename internal::enable_if<!internal::is_same<T, char[1]>::value, decltype(derived()(idx, Eigen::all))>::type
  { return derived()(idx, Eigen::all); }

template <typename T> auto operator()(const char (&)[1], const T& idx) /***/
  -> typename internal::enable_if<!internal::is_same<T, char[1]>::value, decltype(derived()(Eigen::all, idx))>::type
  { return derived()(Eigen::all, idx); }

#endif // EIGEN_VERSION_AT_LEAST(3, 3, 9)
