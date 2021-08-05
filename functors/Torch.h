}  // namespace internal

// TODO(ygitman): check if any alignment is guaranteed
// TODO(ygitman): support multi-dimensional arrays

template <typename Tpx> static
auto MakeMap(const torch::Tensor& arg) {
  enum { v = internal::is_same<Tpx, void>::value };
  typedef EIGEN_ENABLE_IF(!v, OuterStride<>) DeferredStrideType;
  using A = Array<Tpx, Dynamic, Dynamic, RowMajor>;
  using M = Map<A, Unaligned, OuterStride<>>;
  auto x = at::squeeze(arg);

  eigen_assert(x.sizes().size() == 2 && x.stride(1) == 1);
  auto stride = DeferredStrideType(x.stride(0));
  int H = x.size(0), W = x.size(1);

  return M(x.data<Tpx>(), H, W, stride);
}

namespace /***/ internal {
