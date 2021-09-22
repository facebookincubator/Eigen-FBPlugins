/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename T> auto operator[] (const T& idx) const
  -> typename internal::enable_if<!internal::is_convertible<T, Index>::value && SizeAtCompileTime == RowsAtCompileTime && ColsAtCompileTime == 1,
                                  decltype(this->derived()(idx, Eigen::indexing::all))>::type
  { return this->derived()(idx, Eigen::indexing::all); }

template <typename T> auto operator[] (const T& idx) const
  -> typename internal::enable_if<!internal::is_convertible<T, Index>::value && SizeAtCompileTime == ColsAtCompileTime && RowsAtCompileTime == 1,
                                  decltype(this->derived()(Eigen::indexing::all, idx))>::type
  { return this->derived()(Eigen::indexing::all, idx); }

template <typename T> auto operator[] (const T& idx) /***/
  -> typename internal::enable_if<!internal::is_convertible<T, Index>::value && SizeAtCompileTime == RowsAtCompileTime && ColsAtCompileTime == 1,
                                  decltype(this->derived()(idx, Eigen::indexing::all))>::type
  { return this->derived()(idx, Eigen::indexing::all); }

template <typename T> auto operator[] (const T& idx) /***/
  -> typename internal::enable_if<!internal::is_convertible<T, Index>::value && SizeAtCompileTime == ColsAtCompileTime && RowsAtCompileTime == 1,
                                  decltype(this->derived()(Eigen::indexing::all, idx))>::type
  { return this->derived()(Eigen::indexing::all, idx); }

#if /***/ EIGEN_VERSION_AT_LEAST(3, 3, 9)

template <typename T> auto operator()(const T& idx, const char (&)[1]) const
  -> typename internal::enable_if<!internal::is_same<T, char[1]>::value, decltype(this->derived()(idx, Eigen::indexing::all))>::type
  { return this->derived()(idx, Eigen::indexing::all); }

template <typename T> auto operator()(const char (&)[1], const T& idx) const
  -> typename internal::enable_if<!internal::is_same<T, char[1]>::value, decltype(this->derived()(Eigen::indexing::all, idx))>::type
  { return this->derived()(Eigen::indexing::all, idx); }

template <typename T> auto operator()(const T& idx, const char (&)[1]) /***/
  -> typename internal::enable_if<!internal::is_same<T, char[1]>::value, decltype(this->derived()(idx, Eigen::indexing::all))>::type
  { return this->derived()(idx, Eigen::indexing::all); }

template <typename T> auto operator()(const char (&)[1], const T& idx) /***/
  -> typename internal::enable_if<!internal::is_same<T, char[1]>::value, decltype(this->derived()(Eigen::indexing::all, idx))>::type
  { return this->derived()(Eigen::indexing::all, idx); }

#endif // EIGEN_VERSION_AT_LEAST(3, 3, 9)
