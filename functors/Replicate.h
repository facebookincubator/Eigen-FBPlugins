/* Copyright (c) Facebook, Inc. and its affiliates. */

template<typename MatrixType, int ReplicateFactor>
struct traits<ChannelwiseReplicate<ReplicateFactor, MatrixType> > : traits<MatrixType> {
  enum { MaxRowsAtCompileTime = MatrixType::MaxRowsAtCompileTime };
  enum { MaxColsAtCompileTime = MatrixType::MaxColsAtCompileTime };
  enum { Flags = (unsigned int)MatrixType::Flags & RowMajorBit };
  enum { RowsAtCompileTime = MatrixType::RowsAtCompileTime };
  enum { ColsAtCompileTime = MatrixType::ColsAtCompileTime };

  typedef typename traits<MatrixType>::StorageKind StorageKind;
  typedef typename traits<MatrixType>::XprKind XprKind;

  typedef wrap_scalar<typename traits<MatrixType>::Scalar> WrapScalar;
  typedef typename WrapScalar::ChannelType ChannelType;

  enum { N = WrapScalar::NumChannels*ReplicateFactor };
  typedef typename internal::conditional<N != 1, Array<ChannelType, N, 1>, ChannelType>::type Scalar;
};

}  // namespace internal

template<int ReplicateFactor, typename MatrixType> struct ChannelwiseReplicate
  : internal::dense_xpr_base<ChannelwiseReplicate<ReplicateFactor, MatrixType> >::type, private internal::no_assignment_operator {
    typedef typename internal::dense_xpr_base<ChannelwiseReplicate>::type Base;
    EIGEN_DEFINE_PUBLIC_INTERFACE(ChannelwiseReplicate)

    EIGEN_STRONG_INLINE_DEVICE_FUNC const MatrixType& nestedExpression() const
      { return m_matrix; }

    EIGEN_STRONG_INLINE_DEVICE_FUNC ChannelwiseReplicate(const MatrixType& x)
      : m_matrix(x) {}

    EIGEN_STRONG_INLINE_DEVICE_FUNC Index rows() const
      { return m_matrix.rows(); }

    EIGEN_STRONG_INLINE_DEVICE_FUNC Index cols() const
      { return m_matrix.cols(); }

  protected:
    typename MatrixType::Nested m_matrix;
};

namespace internal {

template<int ReplicateFactor, typename MatrixType>
struct evaluator<ChannelwiseReplicate<ReplicateFactor, MatrixType> >
  : evaluator_base<ChannelwiseReplicate<ReplicateFactor, MatrixType> >
{
  typedef ChannelwiseReplicate<ReplicateFactor, MatrixType> XprType;
  enum { CoeffReadCost = evaluator<MatrixType>::CoeffReadCost * ReplicateFactor };
  enum { Alignment = evaluator<MatrixType>::Alignment };
  enum { Flags = (unsigned int)evaluator<MatrixType>::Flags };

  EIGEN_STRONG_INLINE_DEVICE_FUNC explicit evaluator(const XprType& x)
    : m_matrixImpl(x.nestedExpression())
    { EIGEN_INTERNAL_CHECK_COST_VALUE(CoeffReadCost); }

  typedef typename XprType::CoeffReturnType CoeffReturnType;

  template <int K, typename Tp, int N>
  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE static auto replicate(const Array<Tp, N, 1>& x)
    { return x.template replicate<K, 1>().eval(); }

  template <int K, typename Tp>
  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE static auto replicate(const Tp& x)
    { return Array<Tp, K, 1>::Constant(x).eval(); }

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE CoeffReturnType coeff(Index row, Index col) const
    { return replicate<ReplicateFactor>(m_matrixImpl.coeff(row, col)); }

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE CoeffReturnType coeff(Index index) const
    { return replicate<ReplicateFactor>(m_matrixImpl.coeff(index)); }

protected:
  evaluator<MatrixType> m_matrixImpl;
};
