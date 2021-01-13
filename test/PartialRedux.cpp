// Copyright (c) Facebook, Inc. and its affiliates.

#include "CommonHeader.h"  // Common definitions

#if !defined(__clang__)
INIT_TEST(PARTIAL_REDUX, Types_F32_AnyMajor)
#else
INIT_TEST(PARTIAL_REDUX, All_Test_Types)
#endif
  typedef Eigen::Map<Eigen::Array<Tp, Dynamic, Dynamic>> InType;
  typedef Eigen::Map<Eigen::Array<Scalar, Dynamic, 1>> OutputTp;
  Index x = A.outerSize(), y = A.innerSize();
  Tp* data = reinterpret_cast<Tp*>(A.data());
  InType M(data, A.channels() * y, x);

#define TEST_PARTIAL_REDUX(func)                         \
  { auto result = M.rowwise().func().eval();             \
    Scalar* rdata = (Scalar*) result.data();             \
    EXPECT_APPROX(A.alongOuterDim().func().reshaped2d(), \
                  OutputTp(rdata, y)); }

  // TODO(ygitman): alongInnerDim?

 // TEST_PARTIAL_REDUX(template lpNorm<1>)
 // TEST_PARTIAL_REDUX(template lpNorm<2>)
 // TEST_PARTIAL_REDUX(template lpNorm<3>)
 // TEST_PARTIAL_REDUX(squaredNorm)
 TEST_PARTIAL_REDUX(maxCoeff)
 TEST_PARTIAL_REDUX(minCoeff)
 // TEST_PARTIAL_REDUX(norm)
 // TEST_PARTIAL_REDUX(mean)
 TEST_PARTIAL_REDUX(prod)
 TEST_PARTIAL_REDUX(sum)

#undef TEST_PARTIAL_REDUX
}
