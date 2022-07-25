/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:
  template <int D> struct segmentHelper;

  template <> struct segmentHelper<Horizontal> {
    template <int Size, typename Tp>
    static EIGEN_STRONG_INLINE_DEVICE_FUNC auto apply(Tp&& expr, Index start, Index size = Size) {
      return std::forward<Tp>(expr).template middleCols<Size>(start, size);
    }
  };

  template <> struct segmentHelper<Vertical> {
    template <int Size, typename Tp>
    static EIGEN_STRONG_INLINE_DEVICE_FUNC auto apply(Tp&& expr, Index start, Index size = Size) {
      return std::forward<Tp>(expr).template middleRows<Size>(start, size);
    }
  };

 public:
