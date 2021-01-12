/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Tp, int N=Dynamic, int M=Dynamic>
/**************************************************/
struct CV_Traits {
  enum { LayoutFlag = ((N == 1 || M == 1) ? ColMajor : RowMajor) };
  enum { DepthId = (cv::traits::Depth<Tp>::value) };
  enum { TypeId = (cv::traits::Type<Tp>::value) };
  enum { NumDims = (TypeId >> CV_CN_SHIFT) + 1 };

  template <int Id> struct ElemType {};

  template <> struct ElemType<CV_16U>
    { typedef unsigned short Tx; };

  template <> struct ElemType<CV_16S>
    { typedef signed short Tx; };

  template <> struct ElemType<CV_8U>
    { typedef unsigned char Tx; };

  template <> struct ElemType<CV_8S>
    { typedef signed char Tx; };

  template <> struct ElemType<CV_32S>
    { typedef signed int Tx; };

  template <> struct ElemType<CV_64F>
    { typedef double Tx; };

  template <> struct ElemType<CV_32F>
    { typedef float Tx; };

  typedef typename ElemType<DepthId>::Tx ChannelType;
  typedef Array<ChannelType, NumDims, 1> NDScalar;

  typedef typename conditional<(NumDims == 1),
      ChannelType, NDScalar>::type Scalar;

  typedef Map<Array<Scalar, N, M, LayoutFlag> > MapT;
};

}  // namespace internal

template <typename Type, int N, int M> static
typename internal::CV_Traits<Type, N, M>::MapT
MakeMap(const cv::Matx<Type, N, M>& arg)
  { typedef typename internal::CV_Traits<Type, N, M>::MapT MapT;
    return MapT((typename MapT::Scalar*) arg.val); }

template <typename Tpx> static
typename internal::CV_Traits<Tpx>::MapT
MakeMap(const cv::Mat_<Tpx>& arg) {
  typedef typename internal::CV_Traits<Tpx>::MapT MapT;
  int N = arg.rows, M = arg.cols;
  return MapT((typename MapT::Scalar*) arg.data, N, M);
}

namespace /***/ internal {

class OpenCVInputArrayHold : public cv::_InputArray {
  cv::Mat obj;

#ifndef /**/ EIGEN_NO_DEBUG
  int rows_;
  int cols_;
#endif    // EIGEN_NO_DEBUG

 public:
  OpenCVInputArrayHold(int rows, int cols, int type, const void* data)
    : cv::_InputArray(obj),  obj(rows, cols, type, const_cast<void*>(data)) {

#ifndef /**/ EIGEN_NO_DEBUG
    rows_ = rows;
    cols_ = cols;
#endif    // EIGEN_NO_DEBUG
    }

  template <typename Derived>
  OpenCVInputArrayHold(int rows, int cols, int type, const ArrayBase<Derived>& expr)
    : cv::_InputArray(obj),  obj(rows, cols, type) {

    typename Derived::Scalar* data = (typename Derived::Scalar*) obj.data;
    Map<typename Derived::PlainObject>(data, rows, cols) = expr;

#ifndef /**/ EIGEN_NO_DEBUG
    rows_ = rows;
    cols_ = cols;
#endif    // EIGEN_NO_DEBUG
    }

  ~OpenCVInputArrayHold() {
#ifndef /**/ EIGEN_NO_DEBUG
    eigen_assert(rows_ == obj.rows && cols_ == obj.cols);
#endif    // EIGEN_NO_DEBUG
  }
};

class OpenCVOutputArrayHold : public cv::_OutputArray {
  cv::Mat obj;

#ifndef /**/ EIGEN_NO_DEBUG
  int rows_;
  int cols_;
#endif    // EIGEN_NO_DEBUG

 public:
  OpenCVOutputArrayHold(int rows, int cols, int type, void* data)
    : cv::_OutputArray(obj), obj(rows, cols, type, const_cast<void*>(data)) {

#ifndef /**/ EIGEN_NO_DEBUG
    rows_ = rows;
    cols_ = cols;
#endif    // EIGEN_NO_DEBUG
  }

  // OpenCV unfortunately doesn't provide a way
  // to ensure that matrix is non-resizable
  ~OpenCVOutputArrayHold() {
#ifndef /**/ EIGEN_NO_DEBUG
    eigen_assert(rows_ == obj.rows && cols_ == obj.cols);
#endif    // EIGEN_NO_DEBUG
  }
};
