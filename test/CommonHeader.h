/* Copyright (c) Facebook, Inc. and its affiliates. */

#include <Eigen/Geometry>
#include <gtest/gtest.h>
#include <type_traits>
#include <Eigen/Core>
#include <cstdlib>
#include <cstdint>

using Eigen::ColMajor;
using Eigen::RowMajor;
using Eigen::Dynamic;
using Eigen::Array;
using Eigen::Index;

template <typename T1, typename T2> static
bool isApproxEq(const Eigen::ArrayBase<T1>& A, const Eigen::ArrayBase<T2>& B)
  { return A.derived().isApprox(B.derived()); }

static bool isApproxEq(double A, double B) { return std::abs(A - B) < 1e-2; }

static bool isApproxEq(float A, float B) { return std::abs(A - B) < 1e-2f; }

template <typename Tp> struct wrapper { enum { ND = 1 }; typedef Tp type; };

template <typename Tp, int N>
struct wrapper<Array<Tp, N, 1>> { enum { ND = N }; typedef Tp type; };

static bool isApproxEq(int64_t A, int64_t B) { return (A == B); }
static bool isApproxEq(int32_t A, int32_t B) { return (A == B); }
static bool isApproxEq(int16_t A, int16_t B) { return (A == B); }
static bool isApproxEq(uint8_t A, uint8_t B) { return (A == B); }

#define EXPECT_APPROX(A, B) EXPECT_TRUE(isApproxEq(A, B))

#define INIT_TEST(Name, ...)                               \
  template <class> struct Types_##Name : testing::Test {}; \
  using Types_##Name##_T=testing::Types<__VA_ARGS__>;      \
  TYPED_TEST_SUITE(Types_##Name, Types_##Name##_T);        \
                                                           \
  TYPED_TEST(Types_##Name, Name) {                         \
    typedef typename TypeParam::Scalar Scalar;             \
    typedef typename wrapper<Scalar>::type Tp;             \
    constexpr int ND = wrapper<Scalar>::ND;                \
    TypeParam A = TypeParam::Random(4, 7);                 \
    if (std::is_integral<Tp>::value)                       \
      { A -= A / 16 * 16; }                                \
                                                           \
    const auto& v = A.reshaped2d();                        \

#ifndef TYPED_TEST_SUITE
#  define TYPED_TEST_SUITE TYPED_TEST_CASE
#endif

// for {2D, 3D}:
// for {RowMajor, ColMajor}:
// for {Long, Short, Float}:

#define Types_2D_L_RowMajor                                  \
    Array</***/ int64_t, /****/ Dynamic, Dynamic, RowMajor>, \
    Array</***/ int32_t, /****/ Dynamic, Dynamic, RowMajor>, \
    Array</***/ int64_t, /****/ Dynamic, Dynamic, RowMajor>, \
    Array</***/ int32_t, /****/ /***/ 4, /***/ 7, RowMajor>

#define Types_2D_S_RowMajor                                  \
    Array</***/ int16_t, /****/ Dynamic, Dynamic, RowMajor>, \
    Array</***/ uint8_t, /****/ Dynamic, Dynamic, RowMajor>, \
    Array</***/ int16_t, /****/ /***/ 4, /***/ 7, RowMajor>, \
    Array</***/ uint8_t, /****/ /***/ 4, /***/ 7, RowMajor>

#define Types_2D_F_RowMajor                                  \
    Array</***/ double, /*****/ Dynamic, Dynamic, RowMajor>, \
    Array</***/ float, /******/ Dynamic, Dynamic, RowMajor>, \
    Array</***/ double, /*****/ /***/ 4, /***/ 7, RowMajor>, \
    Array</***/ float, /******/ /***/ 4, /***/ 7, RowMajor>

#define Types_2D_I_RowMajor \
    Types_2D_L_RowMajor, Types_2D_S_RowMajor

#define Types_2D_RowMajor \
    Types_2D_I_RowMajor, Types_2D_F_RowMajor

#define Types_2D_L_ColMajor                                  \
    Array</***/ int64_t, /****/ Dynamic, Dynamic, ColMajor>, \
    Array</***/ int32_t, /****/ Dynamic, Dynamic, ColMajor>, \
    Array</***/ int64_t, /****/ /***/ 4, /***/ 7, ColMajor>, \
    Array</***/ int32_t, /****/ /***/ 4, /***/ 7, ColMajor>

#define Types_2D_S_ColMajor                                  \
    Array</***/ int16_t, /****/ Dynamic, Dynamic, ColMajor>, \
    Array</***/ uint8_t, /****/ Dynamic, Dynamic, ColMajor>, \
    Array</***/ int16_t, /****/ /***/ 4, /***/ 7, ColMajor>, \
    Array</***/ uint8_t, /****/ /***/ 4, /***/ 7, ColMajor>

#define Types_2D_F_ColMajor                                  \
    Array</***/ double, /*****/ Dynamic, Dynamic, ColMajor>, \
    Array</***/ float, /******/ Dynamic, Dynamic, ColMajor>, \
    Array</***/ double, /*****/ /***/ 4, /***/ 7, ColMajor>, \
    Array</***/ float, /******/ /***/ 4, /***/ 7, ColMajor>

#define Types_2D_I_ColMajor \
    Types_2D_L_ColMajor, Types_2D_S_ColMajor

#define Types_2D_ColMajor \
    Types_2D_I_ColMajor, Types_2D_F_ColMajor

#define Types_3D_L_RowMajor                                  \
    Array<Array<int64_t, 4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<int32_t, 4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<int64_t, 4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<int32_t, 4, 1>, /***/ 4, /***/ 7, RowMajor>

#define Types_3D_S_RowMajor                                  \
    Array<Array<int16_t, 4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<uint8_t, 4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<int16_t, 4, 1>, /***/ 4, /***/ 7, RowMajor>, \
    Array<Array<uint8_t, 4, 1>, /***/ 4, /***/ 7, RowMajor>

#define Types_3D_F_RowMajor                                  \
    Array<Array<double,  4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<float,   4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<double,  4, 1>, /***/ 4, /***/ 7, RowMajor>, \
    Array<Array<float,   4, 1>, /***/ 4, /***/ 7, RowMajor>

#define Types_3D_I_RowMajor \
    Types_3D_L_RowMajor, Types_3D_S_RowMajor

#define Types_3D_RowMajor \
    Types_3D_I_RowMajor, Types_3D_F_RowMajor

#define Types_3D_L_ColMajor                                  \
    Array<Array<int64_t, 4, 1>, Dynamic, Dynamic, ColMajor>, \
    Array<Array<int32_t, 4, 1>, Dynamic, Dynamic, ColMajor>, \
    Array<Array<int64_t, 4, 1>, /***/ 4, /***/ 7, ColMajor>, \
    Array<Array<int32_t, 4, 1>, /***/ 4, /***/ 7, ColMajor>

#define Types_3D_S_ColMajor                                  \
    Array<Array<int16_t, 4, 1>, Dynamic, Dynamic, ColMajor>, \
    Array<Array<uint8_t, 4, 1>, Dynamic, Dynamic, ColMajor>, \
    Array<Array<int16_t, 4, 1>, /***/ 4, /***/ 7, ColMajor>, \
    Array<Array<uint8_t, 4, 1>, /***/ 4, /***/ 7, ColMajor>

#define Types_3D_F_ColMajor                                  \
    Array<Array<double,  4, 1>, Dynamic, Dynamic, ColMajor>, \
    Array<Array<float,   4, 1>, Dynamic, Dynamic, ColMajor>, \
    Array<Array<double,  4, 1>, /***/ 4, /***/ 7, ColMajor>, \
    Array<Array<float,   4, 1>, /***/ 4, /***/ 7, ColMajor>

#define Types_3D_I_ColMajor \
    Types_3D_L_ColMajor, Types_3D_S_ColMajor

#define Types_3D_ColMajor \
    Types_3D_I_ColMajor, Types_3D_F_ColMajor

// F32 types
#define Types_2D_F32_ColMajor                                \
    Array</***/ float /******/, Dynamic, Dynamic, ColMajor>, \
    Array</***/ float /******/, /***/ 4, /***/ 7, ColMajor>

#define Types_2D_F32_RowMajor                                \
    Array</***/ float /******/, Dynamic, Dynamic, RowMajor>, \
    Array</***/ float /******/, /***/ 4, /***/ 7, RowMajor>

#define Types_2D_F32_AnyMajor \
    Types_2D_F32_ColMajor, Types_2D_F32_RowMajor

#define Types_3D_F32_ColMajor                                \
    Array<Array<float,   4, 1>, Dynamic, Dynamic, ColMajor>, \
    Array<Array<float,   4, 1>, /***/ 4, /***/ 7, ColMajor>

#define Types_3D_F32_RowMajor                                \
    Array<Array<float,   4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<float,   4, 1>, /***/ 4, /***/ 7, RowMajor>

#define Types_3D_F32_AnyMajor \
    Types_3D_F32_ColMajor, Types_3D_F32_RowMajor

#define Types_F32_ColMajor \
    Types_2D_F32_ColMajor, Types_3D_F32_ColMajor

#define Types_F32_RowMajor \
    Types_2D_F32_RowMajor, Types_3D_F32_RowMajor

#define Types_F32_AnyMajor \
    Types_F32_ColMajor, Types_F32_RowMajor

// I32 types
#define Types_2D_I32_ColMajor                             \
    Array</****/ int /****/, Dynamic, Dynamic, ColMajor>, \
    Array</****/ int /****/, /***/ 4, /***/ 7, ColMajor>  \

#define Types_2D_I32_RowMajor                             \
    Array</****/ int /****/, Dynamic, Dynamic, RowMajor>, \
    Array</****/ int /****/, /***/ 4, /***/ 7, RowMajor>

#define Types_2D_I32_AnyMajor \
    Types_2D_I32_ColMajor, Types_2D_I32_RowMajor

#define Types_3D_I32_ColMajor                             \
    Array<Array<int,  4, 1>, Dynamic, Dynamic, ColMajor>, \
    Array<Array<int,  4, 1>, /***/ 4, /***/ 7, ColMajor>  \

#define Types_3D_I32_RowMajor                             \
    Array<Array<int,  4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<int,  4, 1>, /***/ 4, /***/ 7, RowMajor>

#define Types_3D_I32_AnyMajor \
    Types_3D_I32_ColMajor, Types_3D_I32_RowMajor

#define Types_I32_ColMajor \
    Types_2D_I32_ColMajor, Types_3D_I32_ColMajor

#define Types_I32_RowMajor \
    Types_2D_I32_RowMajor, Types_3D_I32_RowMajor

#define Types_I32_AnyMajor \
    Types_I32_ColMajor, Types_I32_RowMajor

// We need special test suite for OpenCV

#define Types_2D_X_OpenCV                                    \
    Array</***/ int32_t, /****/ Dynamic, Dynamic, RowMajor>, \
    Array</***/ double, /*****/ Dynamic, Dynamic, RowMajor>, \
    Array</***/ float, /******/ Dynamic, Dynamic, RowMajor>

#define Types_3D_X_OpenCV                                    \
    Array<Array<int32_t, 4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<double,  4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<float,   4, 1>, Dynamic, Dynamic, RowMajor>

#define Types_2D_S_OpenCV                                    \
    Array</***/ int16_t, /****/ Dynamic, Dynamic, RowMajor>, \
    Array</***/ uint8_t, /****/ Dynamic, Dynamic, RowMajor>

#define Types_3D_S_OpenCV                                    \
    Array<Array<int16_t, 4, 1>, Dynamic, Dynamic, RowMajor>, \
    Array<Array<int8_t,  4, 1>, Dynamic, Dynamic, RowMajor>

#define Types_X_OpenCV \
    Types_2D_X_OpenCV, Types_3D_X_OpenCV

#define Types_S_OpenCV \
    Types_2D_S_OpenCV, Types_3D_S_OpenCV

// Some atypical aggregation groups

#define Types_3D_F_AnyMajor \
    Types_3D_F_ColMajor, Types_3D_F_RowMajor

#define Types_F_RowMajor \
    Types_3D_F_RowMajor, Types_2D_F_RowMajor

#define Types_F_ColMajor \
    Types_3D_F_ColMajor, Types_2D_F_ColMajor

// Higher-level aggregated test suites

// *, {RowMajor | ColMajor}, *
#define Types_ColMajor \
    Types_2D_ColMajor, Types_3D_ColMajor

#define Types_RowMajor \
    Types_2D_RowMajor, Types_3D_RowMajor

// {2D | 3D}, *, *
#define Types_2D_AnyMajor \
    Types_2D_ColMajor, Types_2D_RowMajor

#define Types_3D_AnyMajor \
    Types_3D_ColMajor, Types_3D_RowMajor

// *, *, *
#define All_Test_Types \
    Types_2D_AnyMajor, Types_3D_AnyMajor

// *, *, Float
#define Types_F_AnyMajor \
    Types_2D_F_RowMajor, \
    Types_3D_F_RowMajor, \
    Types_2D_F_ColMajor, \
    Types_3D_F_ColMajor

// *, *, Long
#define Types_L_AnyMajor \
    Types_2D_L_RowMajor, \
    Types_3D_L_RowMajor, \
    Types_2D_L_ColMajor, \
    Types_3D_L_ColMajor

// *, *, Short
#define Types_S_AnyMajor \
    Types_2D_S_RowMajor, \
    Types_3D_S_RowMajor, \
    Types_2D_S_ColMajor, \
    Types_3D_S_ColMajor

// *, *, Int
#define Types_I_AnyMajor \
    Types_2D_I_RowMajor, \
    Types_3D_I_RowMajor, \
    Types_2D_I_ColMajor, \
    Types_3D_I_ColMajor
