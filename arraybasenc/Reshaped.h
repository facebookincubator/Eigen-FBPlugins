/* Copyright (c) Facebook, Inc. and its affiliates. */

const Reshaped<const Derived, SizeAtCompileTime, 1> reshaped2d() const
  { return Base::reshaped(); }

Reshaped<Derived, SizeAtCompileTime, 1> reshaped2d()
  { return Base::reshaped(); }

 protected:
  void reshaped() const {}

 public:
