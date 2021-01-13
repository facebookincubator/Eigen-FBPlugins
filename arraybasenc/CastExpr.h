/* Copyright (c) Facebook, Inc. and its affiliates. */

private:
 template <typename T> struct ElemCast {
   typedef typename internal::wrap_scalar<Scalar>::template CastXpr<T>::Type ScalarCastType;
   typedef typename internal::remove_all<ScalarCastType>::type::EvalReturnType EvalTp;
   typedef typename internal::remove_all<EvalTp>::type Type;
 };

public:
 template <typename Tp> EIGEN_STRONG_INLINE_DEVICE_FUNC
 typename Base::template CastXpr<typename ElemCast<Tp>::Type>::Type cast() const
   { return typename Base::template CastXpr<typename ElemCast<Tp>::Type>::Type(derived()); }
