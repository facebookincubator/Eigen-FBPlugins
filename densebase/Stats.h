/* Copyright (c) Facebook, Inc. and its affiliates. */

EIGEN_STRONG_INLINE_DEVICE_FUNC
Scalar median() const {
  auto A = derived().reshaped().eval();
  Index p = A.size() / 2;

  // TODO(ygitman): remove extra copy?

  std::nth_element(A.data(), A.data() + p, A.data() + A.size());
  return A.size()&1 ? A[p] : (A[p] + A.head(p).maxCoeff()) / 2;
}

EIGEN_STRONG_INLINE_DEVICE_FUNC
Scalar middleElement() const {
  auto vals = derived().reshaped().eval();
  Scalar* p = vals.data();
  Index N = vals.size();

  // TODO(ygitman): remove extra copy?

  std::nth_element(p, p + (N / 2), p + N);
  return vals[(N - 1) / 2];
}

EIGEN_STRONG_INLINE_DEVICE_FUNC
Scalar quantile(float x) const {
  auto vals = derived().reshaped().eval();
  int q_index = x * vals.size() - x + 0.5;
  eigen_assert(0 <= x && x <= 1.0);
  Scalar* p = vals.data();
  Index N = vals.size();

  // TODO(ygitman): remove extra copy?

  std::nth_element(p, p + q_index, p + N);
  return vals[q_index];
}

