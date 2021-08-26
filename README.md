[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://opensource.org/licenses/MPL-2.0)
![unit tests status](https://github.com/facebookincubator/Eigen-FBPlugins/workflows/unit-tests/badge.svg)
![lint status](https://github.com/facebookincubator/Eigen-FBPlugins/workflows/lint/badge.svg)

# Eigen-FBPlugins
This is collection of plugins extending [Eigen](https://eigen.tuxfamily.org/dox/index.html) arrays/matrices with main focus on using them for computer vision. In particular, this project should provide support for multichannel arrays like `Eigen::Array<Eigen::Array3f, Eigen::Dynamic, Eigen::Dynamic>`, which is missing in vanilla Eigen, and seamless integration between Eigen types and [OpenCV](https://opencv.org/) functions.

## Motivation
There is no standard matrix library like Numpy in the world of C++. [Eigen](https://eigen.tuxfamily.org/dox/index.html) is a quite common choice if your use-case belong to 2D world (so, no tensors). Advantages of using Eigen are superiour perfomance, compile-type checks and support for both small and large matrices with the same concise API.

In the domain of computer vision we usually work with “2+1D” arrays (two major dimensions and channels which are usually a few and known at compile time); this use-case is not a priority for Eigen community and probably will not be in any near future, so we are setting up this collection of plugins meant to provide priority support for vision use-case.


## How to use
Include `Eigen/Core` and pass the following options to compiler.

```
  -DEIGEN_SPARSEMATRIXBASE_PLUGIN=\"<Path to the project root>/EigenSparsematrixbasePlugin.h\"
  -DEIGEN_PLAINOBJECTBASE_PLUGIN=\"<Path to the project root>/EigenPlainobjectbasePlugin.h\"
  -DEIGEN_SPARSEMATRIX_PLUGIN=\"<Path to the project root>/EigenSparsematrixPlugin.h\"
  -DEIGEN_SPARSEVECTOR_PLUGIN=\"<Path to the project root>/EigenSparsevectorPlugin.h\"
  -DEIGEN_MATRIXBASE_PLUGIN=\"<Path to the project root>/EigenMatrixbasePlugin.h\"
  -DEIGEN_ARRAYBASE_PLUGIN=\"<Path to the project root>/EigenArraybasePlugin.h\"
  -DEIGEN_DENSEBASE_PLUGIN=\"<Path to the project root>/EigenDensebasePlugin.h\"
  -DEIGEN_FUNCTORS_PLUGIN=\"<Path to the project root>/EigenFunctorsPlugin.h\"
  -DEIGEN_MAPBASE_PLUGIN=\"<Path to the project root>/EigenMapbasePlugin.h\"
  -DEIGEN_MATRIX_PLUGIN=\"<Path to the project root>/EigenMatrixPlugin.h\"
  -DEIGEN_ARRAY_PLUGIN=\"<Path to the project root>/EigenArrayPlugin.h\"
```

Check [Configuration](#configuration) for other flags.

## Examples
Let us consider some basic vision-inspired example outlining pixelwise operations and reductions.

```c++
template <int ksize, typename Derived>
auto compute_dx_grad_magn(const Eigen::ArrayBase<Derived>& A) {
  // ArrayBase<Derived> can capture both single and multichannel arrays,
  // and you need to use derived() later

  // ArrayBaseNC<Derived> would only capture multichannel arrays,
  // and no need to use derived() then

  // This is lazy expression, so no actual assembly code is generated here
  const auto& A32f = A.derived().template cast<float>();

  if constexpr(ksize == 1) {
    // cropPads isn't available in vanila Eigen; These are also lazy expressions
    const auto& x1 = A32f(Eigen::cropPads<1, 0>(), Eigen::all);
    const auto& x2 = A32f(Eigen::cropPads<0, 1>(), Eigen::all);

    // Finally all operations are combined in the single vectorized loop
    // Return value optimization should eliminate the copy

    // channelwise() isn't available in vanila Eigen;
    // cellwise().norm() would do reduction over rows and cols
    // and just norm() would do full reduction
    return (x2 - x1).channelwise().norm();
  } else {
    Eigen::ArrayNM1f dx;

    // You can use A32f.cvMat() to convert proper Eigen array
    // (allocated dynamically and row-major) into OpenCV Mat,
    // but it is not required if you just want to pass it into OpenCV function.

    // You would need to compile code with -DEIGEN_WITH_OPENCV
    cv::Sobel(A32f, dx, -1, 1, 0, ksize);
    return dx.channelwise().norm();
  }
}

int main() {
  // Eigen::Array<Eigen::Array<uchar 3, 1>,
  //              Eigen::Dynamic,
  //              Eigen::Dynamic,
  //              Eigen::RowMajor>
  Eigen::ArrayNM3u A = decltype(A)::Random(1080, 1920);

  // This will result in a single floating point number,
  // use cellwise().sum() to preserve channels
  std::cerr << compute_dx_grad_magn<1>(A / 2 + 0.5).sum();
  std::cerr << compute_dx_grad_magn<3>(A / 2 + 0.5).sum();

  // Same code works for normal single-channel arrays

  // Eigen::Array<uint8_t, Eigen::Dynamic, Eigen::Dynamic,
  //              Eigen::RowMajor>
  Eigen::ArrayNM1u B = decltype(B)::Random(1080, 1920);
  std::cerr << compute_dx_grad_magn<1>(A / 2 + 0.5).sum();
  std::cerr << compute_dx_grad_magn<3>(A / 2 + 0.5).sum();
}
```

Now let us try to do something more interesting. Let us implement box filter. Same as in the example above we want our function to support any Eigen array expression either single channel or multichannel, and we want it to be efficient.

```c++
template <Eigen::DirectionType Direction,
          int KS = Eigen::Dynamic,
          typename Derived = void>
auto box_filter(const Eigen::ArrayBase<Derived>& src,
                int ksize = KS) {
  typedef typename Derived::Scalar InputScalar;

  // Let's require input type to be at least 2 bytes wide,
  // so that we could safely accumulate input values
  static_assert(sizeof(InputScalar) >= 2);

  // We need to evaluate image in case it is an expression.
  // We can use nested_eval<2>(). In this case Eigen would check benefits
  // of evaluating and do it only if beneficial.
  auto evaled_src = src.derived().template nested_eval<2>();

  constexpr int target_dim = (Direction == Eigen::Horizontal) ? 1 : 0;
  const int target_dim_size =
      (Direction == Eigen::Horizontal) ? src.cols() : src.rows();
  const int other_dim_size =
      (Direction == Eigen::Horizontal) ? src.rows() : src.cols();

  // Here we will do box filtering only in the interior where it is defined.
  // To get fancy border interpolations, someone can pass corresponding
  // Eigen's lazy expression using custom indexing
  // (https://eigen.tuxfamily.org/dox-devel/group__TutorialSlicingIndexing.html)
  // or redesign the function to accept template interpolating functor.

  typedef typename std::remove_const<decltype(src(
      Eigen::cropPads<0, target_dim == 0 ? KS : 0>(0, ksize),
      Eigen::cropPads<0, target_dim == 1 ? KS : 0>(0, ksize)
    ).eval())>::type OutputType;

  OutputType dst(
    target_dim == 0 ? src.rows() - ksize + 1: src.rows(),
    target_dim == 1 ? src.cols() - ksize + 1: src.cols()
  );

  // Note that filtering along dimension opposite to image layout
  // can be vectorized using SIMD instruction. This isn't done here.

  for (int i = 0; i < other_dim_size; ++i) {
    // Lazy expressions, so no assembly is generated yet
    auto output_slice = dst.derived().template sliceAlong<target_dim>(i);
    auto input_slice = evaled_src.template sliceAlong<target_dim>(i);

    // cellwise().sum() will sum up pixels but keep channels dimension
    auto s = input_slice.template head<KS>(ksize).cellwise().sum();

    for (int j = ksize; j < target_dim_size; ++j) {
      auto diff = input_slice[j - ksize] + input_slice[j];
      output_slice[j - ksize] = s / ksize;
      s -= diff;
    }

    output_slice[target_dim_size - ksize] = s / ksize;
  }

  return dst;
}

template <int KS = Eigen::Dynamic, typename InputDerived = void>
auto box_filter2d(const Eigen::ArrayBase<InputDerived>& src,
                  int ksize = KS) {
  if (src.isRowMajor()) {
    auto T = box_filter<Eigen::Horizontal, KS>(src, ksize);
    std::cerr << "---------------" << std::endl;
    return box_filter<Eigen::Vertical, KS>(T, ksize);
  } else {
    auto T = box_filter<Eigen::Vertical, KS>(src, ksize);
    return box_filter<Eigen::Horizontal, KS>(T, ksize);
  }
}
```

## Design notes
As we need to modify base expression classes, we are using [Eigen Plugins](http://eigen.tuxfamily.org/dox-3.2/TopicCustomizingEigen.html) to hook into Eigen classes and `EIGEN_FUNCTORS_PLUGIN` to inject code non belonging to any class. Speaking specifically about multichannel expression we inject and inherit from additional class in the class hierarchy. Unlike the Eigen itself this project is C++14 and not C++03 complaint.

### Efficiency
This project is designed with focus on efficiency. Speaking specifically about multichannel arrays, just at the time of expression evaluation it is replaced with corresponding single-channel code if possible enabling vectorization and all other perfomance optimizations available in vanilla Eigen. If you want to ensure that your code is properly vectorized use `-DEIGEN_FAIL_ON_EXPR2D` during compilation and check for any compile errors.

### Things to be aware
As this project is all about metaprogramming, it might increase compilation time and cause confusing compile-error messages. Unlike Eigen itself ensuring short compilation times is not a priority for us.

### Configurations and reexposing Eigen plugins
If you want to use this project and still plug-in your own code, you can use `-DEIGEN_<PLUGIN_NAME>_EXTRA_PLUGIN` instead of `-DEIGEN_<PLUGIN_NAME>_PLUGIN`.

Use `-DEIGEN_WITH_TORCH` and `-DEIGEN_WITH_OPENCV -DOPENCV_TRAITS_ENABLE_DEPRECATED` to enable integration with PyTorch and OpenCV respectively.

Use `-DEIGEN_DISABLE_MULTICHANNEL_ARRAYS` if you don't need multichannel arrays.

Use `-DEIGEN_EXTRA_SAFETY` to make Eigen fail compilation on operations likely subject to overflow or precision loss, e.g. summing up array of uint8_t or computing norm of integer array.

## License
This project is licensed under Mozilla Public License 2.0, as found in the [LICENSE](LICENSE) file.
