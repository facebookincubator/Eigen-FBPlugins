/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:
  template <typename Tp> struct torch_datatraits;

  template <> struct torch_datatraits<double>
    { static inline torch::Dtype func() { return torch::kF64; } };

  template <> struct torch_datatraits<float>
    { static inline torch::Dtype func() { return torch::kF32; } };

  template <> struct torch_datatraits<int64_t>
    { static inline torch::Dtype func() { return torch::kI64; } };

  template <> struct torch_datatraits<int32_t>
    { static inline torch::Dtype func() { return torch::kI32; } };

  template <> struct torch_datatraits<int16_t>
    { static inline torch::Dtype func() { return torch::kI16; } };

  template <> struct torch_datatraits<uint8_t>
    { static inline torch::Dtype func() { return torch:: kU8; } };

  template <> struct torch_datatraits<int8_t>
    { static inline torch::Dtype func() { return torch:: kI8; } };

 public:
  EIGEN_STRONG_INLINE torch::Tensor torchTensor4D()
  EIGEN_REQUIRES(internal::IsRowMajorExpression<Derived>) {
    ChannelType* dptr = reinterpret_cast<ChannelType*>(data());
    torch::Dtype T = torch_datatraits<ChannelType>::func();
    const int N = rows(), M = cols();

    if (NumChannels != 1)
      return torch::from_blob(dptr, {1, N, M, NumChannels}, T);

    if (NumChannels == 1)
      return torch::from_blob(dptr, {1, NumChannels, N, M}, T);
  }
