/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:
  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar middleElementImpl() {
    const auto& vals = static_cast<Derived*>(this)->reshaped();
    Scalar* p = static_cast<Derived*>(this)->data();
    Index N = static_cast<Derived*>(this)->size();
    std::nth_element(p, p + (N / 2), p + N);
    return vals[(N - 1) / 2];
  }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar quantileImpl(float x) {
    const auto& vals = static_cast<Derived*>(this)->reshaped();
    Scalar* p = static_cast<Derived*>(this)->data();
    Index N = static_cast<Derived*>(this)->size();
    int q_index = x * vals.size() - x + 0.5;
    eigen_assert(0 <= x && x <= 1.0);

    std::nth_element(p, p + q_index, p + N);
    return vals[q_index];
  }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar medianImpl() {
    const auto& A = static_cast<Derived*>(this)->reshaped();
    Index size = static_cast<Derived*>(this)->size();
    auto* ptr = static_cast<Derived*>(this)->data();
    Index p = A.size() / 2;

    std::nth_element(ptr, ptr + p, ptr + size);

    if (size % 2 == 0)
      return (A[p] + A.head(p).maxCoeff()) / 2;
    else
      return A[p];
  }

 public:
  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar middleElement() const && {
    return const_cast<PlainObjectBase*>(this)->middleElementImpl();
  }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar quantile(float x) const && {
    return const_cast<PlainObjectBase*>(this)->quantileImpl(x);
  }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar median() const && {
    return const_cast<PlainObjectBase*>(this)->medianImpl();
  }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar middleElement() && { return middleElementImpl(); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar quantile(float x) && { return quantileImpl(x); }

  EIGEN_STRONG_INLINE_DEVICE_FUNC
  Scalar median() && { return medianImpl(); }
