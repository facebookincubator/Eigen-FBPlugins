/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:

  template <typename Arg2, typename Arg3, typename Func> const auto ternaryExprHelper(const Arg2& arg2, const Arg3& arg3, const Func& func) const
    { return CwiseTernaryOp<Func, const Derived, const Arg2, const Arg3>(derived(), arg2, arg3, func); }

 public:
