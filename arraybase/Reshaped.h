/* Copyright (c) Facebook, Inc. and its affiliates. */

const Reshaped<const Derived, SizeAtCompileTime, 1> reshaped2d() const
  { return this->reshaped(); }

Reshaped<Derived, SizeAtCompileTime, 1> reshaped2d()
  { return this->reshaped(); }
