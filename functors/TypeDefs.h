/* Copyright (c) Facebook, Inc. and its affiliates. */

}  // namespace internal

#define DEFINE_ARRAY_XX_ND_TYPE(Type, N, suffix)                                         \
  typedef Matrix<Array<Type, N, 1>, Dynamic, Dynamic, RowMajor> MatrixNM ## N ## suffix; \
  typedef Array<Array<Type, N, 1>, Dynamic, Dynamic, RowMajor> ArrayNM ## N ## suffix;

#define DEFINE_ARRAY_XX_BASIC_TYPE(Type, suffix)                            \
  typedef Matrix<Type, Dynamic, Dynamic, RowMajor> MatrixNM1 ## suffix;     \
  typedef Matrix<Type, Dynamic, Dynamic, RowMajor> MatrixNM ## suffix;      \
  typedef Array<Type, Dynamic, Dynamic, RowMajor> ArrayNM1 ## suffix;       \
  typedef Array<Type, Dynamic, Dynamic, RowMajor> ArrayNM ## suffix;

#define DEFINE_ARRAY_XX_ALL_ND_AND_BASIC_TYPES(Type, suffix) \
    DEFINE_ARRAY_XX_BASIC_TYPE(Type, suffix)                 \
    DEFINE_ARRAY_XX_ND_TYPE(Type, 4, suffix)                 \
    DEFINE_ARRAY_XX_ND_TYPE(Type, 3, suffix)                 \
    DEFINE_ARRAY_XX_ND_TYPE(Type, 2, suffix)

DEFINE_ARRAY_XX_ALL_ND_AND_BASIC_TYPES(unsigned char, u)
DEFINE_ARRAY_XX_ALL_ND_AND_BASIC_TYPES(double, d)
DEFINE_ARRAY_XX_ALL_ND_AND_BASIC_TYPES(float, f)
DEFINE_ARRAY_XX_ALL_ND_AND_BASIC_TYPES(short, s)
DEFINE_ARRAY_XX_ALL_ND_AND_BASIC_TYPES(int, i)

#undef DEFINE_ARRAY_XX_ALL_ND_AND_BASIC_TYPES
#undef DEFINE_ARRAY_XX_BASIC_TYPE
#undef DEFINE_ARRAY_XX_ND_TYPE

typedef Array<unsigned char, 4, 1, 0, 4, 1> Array4u;
typedef Array<unsigned char, 3, 1, 0, 3, 1> Array3u;
typedef Array<unsigned char, 2, 1, 0, 2, 1> Array2u;

namespace /***/ internal {
