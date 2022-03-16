/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto& operator +=(const ArrayBaseNCImpl2d<OtherDerived>& other)
  { derived().as2d() += other.derived().as2d(); return derived(); }

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto& operator -=(const ArrayBaseNCImpl2d<OtherDerived>& other)
  { derived().as2d() -= other.derived().as2d(); return derived(); }

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto& operator *=(const ArrayBaseNCImpl2d<OtherDerived>& other)
  { derived().as2d() *= other.derived().as2d(); return derived(); }

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto& operator /=(const ArrayBaseNCImpl2d<OtherDerived>& other)
  { derived().as2d() /= other.derived().as2d(); return derived(); }

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto& operator =(const ArrayBaseNCImpl2d<OtherDerived>& other)
  { derived().as2d() = other.derived().as2d(); return derived(); }

template <typename OtherDerived> EIGEN_STRONG_INLINE_DEVICE_FUNC
auto& operator =(const ArrayBaseNCImpl2d& other)
  { derived().as2d() = other.derived().as2d(); return derived(); }
