/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Tpx, int N>
struct MakeMapImpl {
  static auto run(const torch::Tensor& arg) {
    enum { v = internal::is_same<Tpx, void>::value };
    typedef EIGEN_ENABLE_IF(!v, OuterStride<>) DeferredStrideType;
    using A = Array<Array<Tpx, N, 1>, Dynamic, Dynamic, RowMajor>;
    // TODO(ygitman): check if any alignment is guaranteed
    using M = Map<const A, Unaligned, OuterStride<>>;
    auto x = at::squeeze(arg);

    eigen_assert(x.stride(1) == 1 && x.stride(2) == 1);
    eigen_assert(x.sizes().size() == 3);
    eigen_assert(x.size(2) == N);

    auto stride = DeferredStrideType(x.stride(0) / N);
    auto* data = (Array<Tpx, N, 1>*) x.data<Tpx>();
    int H = x.size(0), W = x.size(1);
    return M(data, H, W, stride);
  }
};

template <typename Tpx>
struct MakeMapImpl<Tpx, 1> {
  static auto run(const torch::Tensor& arg) {
    enum { v = internal::is_same<Tpx, void>::value };
    typedef EIGEN_ENABLE_IF(!v, OuterStride<>) DeferredStrideType;
    using A = Array<Tpx, Dynamic, Dynamic, RowMajor>;
    // TODO(ygitman): check if any alignment is guaranteed
    using M = Map<const A, Unaligned, OuterStride<>>;
    auto x = at::squeeze(arg);

    eigen_assert(x.sizes().size() == 2 && x.stride(1) == 1);
    auto stride = DeferredStrideType(x.stride(0));
    int H = x.size(0), W = x.size(1);
    auto* data = x.data<Tpx>();

    return M(data, H, W, stride);
  }
};

}  // namespace internal

template <typename Tpx, int N> static
auto MakeMap(const torch::Tensor& arg) {
  return internal::MakeMapImpl<Tpx, N>::run(arg);
}

template <typename Tpx> static
auto MakeMap(const torch::Tensor& arg) {
  return internal::MakeMapImpl<Tpx, 1>::run(arg);
}

namespace /***/ internal {
