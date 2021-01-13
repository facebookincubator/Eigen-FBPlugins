/* Copyright (c) Facebook, Inc. and its affiliates. */

#if /**/ EIGEN_VERSION_AT_LEAST(3, 3, 9)

} // namespace internal

template <Index Value=Dynamic>                           \
struct Subsample {                                       \
  inline Index value() const { return m_value.value(); } \
  internal::variable_if_dynamic<Index, Value> m_value;   \
  Subsample(int value = Value) : m_value(value) {}       \
};

#define DEFINE_PADEXPR(fn)                         \
  template <Index A=Dynamic, Index B=Dynamic>      \
  struct fn {                                      \
    inline Index a() const { return m_a.value(); } \
    inline Index b() const { return m_b.value(); } \
    internal::variable_if_dynamic<Index, A> m_a;   \
    internal::variable_if_dynamic<Index, B> m_b;   \
    fn(int a = A, int b = B) : m_a(a), m_b(b) {}   \
  };

DEFINE_PADEXPR(CropPads)

#undef DEFINE_PADEXPR

template <Index A=Dynamic, Index B=Dynamic>
CropPads<A, B> cropPads(int a = A, int b = B)
  { return CropPads<A, B>(a, b); }

template <Index Value=Dynamic>
Subsample<Value> subsample(int value = Value)
  { return Subsample<Value>(value); }

namespace /***/ internal {

template <int XprSize, Index A, Index B>
struct CropPadsExpr {
  CropPadsExpr(Index size = XprSize, Index a = A, Index b = B)
      : m_size(size), m_a(a), m_b(b) {}

  Index padsize() const { return m_a.value() + m_b.value(); }
  Index operator[](Index i) const { return i + m_a.value(); }
  Index size() const { return m_size.value() - padsize(); }
  Index first() const { return m_a.value(); }

  enum { ADynamic = (XprSize == Dynamic || A == Dynamic) };
  enum { BDynamic = (XprSize == Dynamic || B == Dynamic) };

  enum { Ap = (!ADynamic ? A : 0), Bp = (!BDynamic ? B : 0) };
  enum { AnyDynamic = ADynamic || BDynamic };
  enum { NewSize = XprSize - Ap - Bp };

  enum { SizeAtCompileTime = AnyDynamic ? Dynamic : NewSize };

  variable_if_dynamic<Index, XprSize> m_size;
  variable_if_dynamic<Index, A> m_a;
  variable_if_dynamic<Index, B> m_b;
};

template <int XprSize, Index Value>
struct SubsampleExpr {
  enum { IsDynamic = ((XprSize == Dynamic) || (Value == Dynamic)) };

  Index size() const { return (m_size.value() + m_value.value() - 1) / m_value.value(); }
  enum { SizeAtCompileTime = IsDynamic ? Dynamic : (XprSize + Value - 1) / Value };

  Index operator[](Index i) const { return i * m_value.value(); }
  Index first() const { return 0; }

  SubsampleExpr(Index size = XprSize, Index value = Value)
      : m_size(size), m_value(value) {}

  variable_if_dynamic<Index, XprSize> m_size;
  variable_if_dynamic<Index, Value> m_value;
};

// TODO(ygitman): it seems that cost functors aren't supported right now

#define DEFINE_PADEXPR_INDEXING_INTERFACE(fn)                     \
  template <int XprSize, Index A, Index B>                        \
  struct get_compile_time_incr<fn##PadsExpr<XprSize, A, B>, void> \
    { enum { value = 1 }; };                                      \
                                                                  \
  template <int XprSize, Index A, Index B>                        \
  struct IndexedViewCompatibleType<fn##Pads<A, B>, XprSize, void> \
    { typedef fn##PadsExpr<XprSize, A, B> type; };                \
                                                                  \
  template <typename XprSizeType, Index A, Index B>               \
  inline fn##PadsExpr<get_fixed_value<XprSizeType>::value, A, B>  \
  makeIndexedViewCompatible(const fn##Pads<A, B>& pads, XprSizeType size, SpecializedType /******/)  \
    { return fn##PadsExpr<get_fixed_value<XprSizeType>::value, A, B>(size, pads.a(), pads.b()); }

template <int XprSize, Index Value>
struct get_compile_time_incr<SubsampleExpr<XprSize, Value>, void>
  { enum { value = (Value == Dynamic) ? UndefinedIncr : Value }; };

template <int XprSize, Index Value>
struct IndexedViewCompatibleType<Subsample<Value>, XprSize, void>
  { typedef SubsampleExpr<XprSize, Value> type; };

template <typename XprSizeType, Index Value>
inline SubsampleExpr<get_fixed_value<XprSizeType>::value, Value>
makeIndexedViewCompatible(const Subsample<Value>& expr, XprSizeType size, SpecializedType /******/)
  { return SubsampleExpr<get_fixed_value<XprSizeType>::value, Value>(size, expr.value()); }

DEFINE_PADEXPR_INDEXING_INTERFACE(Crop)

#undef DEFINE_PADEXPR_INDEXING_INTERFACE

#endif // EIGEN_VERSION_AT_LEAST(3, 3, 9)
