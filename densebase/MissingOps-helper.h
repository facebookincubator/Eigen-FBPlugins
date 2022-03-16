/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:

  template <typename Tp> EIGEN_STRONG_INLINE_DEVICE_FUNC auto minCoeffHelper(Tp* xy) const
    EIGEN_REQUIRES(requires (Tp* xy) { &xy->x(); &xy->y(); }) { return derived().minCoeff(&xy->y(), &xy->x()); }

  template <typename Tp> EIGEN_STRONG_INLINE_DEVICE_FUNC auto maxCoeffHelper(Tp* xy) const
    EIGEN_REQUIRES(requires (Tp* xy) { &xy->x(); &xy->y(); }) { return derived().maxCoeff(&xy->y(), &xy->x()); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC auto minCoeffHelper(Index* idx) const
    { return derived().minCoeff(idx); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC auto maxCoeffHelper(Index* idx) const
    { return derived().maxCoeff(idx); }

 public:
