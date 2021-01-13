/* Copyright (c) Facebook, Inc. and its affiliates. */

}  // namespace internal

template<typename T> typename internal::enable_if<T::RowsAtCompileTime != Dynamic && T::ColsAtCompileTime == 1, std::ostream&>::type
  operator <<(std::ostream& os, const ArrayBase<T>& m) { std::ostringstream ss; ss.copyfmt(os); ss.width(0); ss << '['<< m.transpose() <<']'; return (os << ss.str()); }

namespace /***/ internal {
