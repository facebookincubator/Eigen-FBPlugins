/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:

  template <typename Tp> EIGEN_STRONG_INLINE auto minCoeffHelper(Tp* xy) const
    { return derived().minCoeff(&xy->y(), &xy->x()); }

  template <typename Tp> EIGEN_STRONG_INLINE auto maxCoeffHelper(Tp* xy) const
    { return derived().maxCoeff(&xy->y(), &xy->x()); }

  template <> EIGEN_STRONG_INLINE auto minCoeffHelper<Index>(Index* idx) const
    { return derived().minCoeff(idx); }

  template <> EIGEN_STRONG_INLINE auto maxCoeffHelper<Index>(Index* idx) const
    { return derived().maxCoeff(idx); }

 public:
