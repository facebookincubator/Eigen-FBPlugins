#include <Eigen/Core>
#include <iostream>

int main() {
#ifdef VERSION_NC
  Eigen::Array<Eigen::Array3f, 7, 4, 1> A = decltype(A)::Random();
#else
  Eigen::Array<float, 7, 12, 1> A = decltype(A)::Random();
#endif

  EIGEN_ASM_COMMENT("begin-asm");
  float v = (2 * A + 1).colwise().sum().norm();
  EIGEN_ASM_COMMENT("end-asm");

  std::cout << v << std::endl;
  return 0;
}
