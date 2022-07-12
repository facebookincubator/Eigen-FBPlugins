/* Copyright (c) Facebook, Inc. and its affiliates. */

template <int value, typename Func>
struct LambdaFunctor : std::remove_const_t<Func> {
  template <int Evaluate=1, typename ...Args> EIGEN_STRONG_INLINE_DEVICE_FUNC auto operator()(const Args& ...args) const
    { return internal::ops::evaluate<Evaluate>(this->Func::operator()(args...)); }

  LambdaFunctor(const Func& fn) : Func(fn) {}
};

template <int v, int cnd, typename Func> struct ChannelwiseFunctor : std::remove_const_t<Func>
  { ChannelwiseFunctor(const Func& fn) : Func(fn) {} };

template <int v1, int v2, typename ReturnType, typename Func>
struct ReduxLambdaFunctor : std::remove_const_t<Func> {
  template<int Size> struct Cost { static constexpr bool value = (Size - 1) * v1 + v2; };
  ReduxLambdaFunctor(const Func& fn) : Func(fn) {}
  static constexpr bool Vectorizable = false;
  typedef ReturnType result_type;
  typedef void BinaryOp;
};

template <int v1, int v2, typename T, typename Func>
EIGEN_STRONG_INLINE_DEVICE_FUNC const auto make_redux_functor(const Func& func)
  { return ReduxLambdaFunctor<v1, v2, T, Func>(func); }

template <int Cost, typename Func>
EIGEN_STRONG_INLINE_DEVICE_FUNC const auto make_functor(const Func& func)
  { return LambdaFunctor<Cost, Func>(func); }

template <int v, int cnd, typename Func> EIGEN_STRONG_INLINE_DEVICE_FUNC
const auto make_channelwise_functor(const Func& func)
  { return ChannelwiseFunctor<v, cnd, Func>(func); }

template <int v, typename Fn> struct functor_traits<LambdaFunctor<v, Fn>>
  { enum { Cost = v, PacketAccess = 0 }; };

template<int v, typename Fn, typename Tp>
struct traits<CwiseUnaryOp<ChannelwiseFunctor<v, 1, Fn>, Tp>>
  : traits<CwiseUnaryOp<ChannelwiseFunctor<v, 0, Fn>, Tp>>
  { typedef ArrayXprNC XprKind; };

template <int v, int cnd, typename Fn>
struct functor_traits<ChannelwiseFunctor<v, cnd, Fn>>
  { enum { Cost = v, PacketAccess = 0 }; };
