/* Copyright (c) Facebook, Inc. and its affiliates. */

template<typename ConditionType, typename ThenArrayType, typename ElseArrayType>
struct traits<SelectNC<ConditionType, ThenArrayType, ElseArrayType> > : traits<ThenArrayType> {
  enum { Flags = (unsigned int)ThenArrayType::Flags & ElseArrayType::Flags & RowMajorBit };
  enum { MaxRowsAtCompileTime = ConditionType::MaxRowsAtCompileTime };
  enum { MaxColsAtCompileTime = ConditionType::MaxColsAtCompileTime };
  enum { RowsAtCompileTime = ConditionType::RowsAtCompileTime };
  enum { ColsAtCompileTime = ConditionType::ColsAtCompileTime };

  typedef typename traits<ThenArrayType>::XprKind XprKind;
  typedef typename traits<ThenArrayType>::Scalar Scalar;
  typedef Dense StorageKind;
};

}  // namespace internal

template<typename ConditionType, typename ThenArrayType, typename ElseArrayType> struct SelectNC
  : internal::dense_xpr_base<SelectNC<ConditionType, ThenArrayType, ElseArrayType> >::type, private internal::no_assignment_operator {
    EIGEN_STRONG_INLINE_DEVICE_FUNC SelectNC(const ConditionType& a_conditionArray, const ThenArrayType& a_thenArray, const ElseArrayType& a_elseArray)
      : m_condition(a_conditionArray), m_then(a_thenArray), m_else(a_elseArray)
    {
      eigen_assert(m_condition.rows() == m_then.rows() && m_condition.rows() == m_else.rows());
      eigen_assert(m_condition.cols() == m_then.cols() && m_condition.cols() == m_else.cols());
    }

    EIGEN_STRONG_INLINE_DEVICE_FUNC const ConditionType& conditionMatrix() const { return m_condition; }
    EIGEN_STRONG_INLINE_DEVICE_FUNC const ThenArrayType& thenMatrix() const { return m_then; }
    EIGEN_STRONG_INLINE_DEVICE_FUNC const ElseArrayType& elseMatrix() const { return m_else; }

    typedef typename internal::dense_xpr_base<SelectNC>::type Base;
    EIGEN_DEFINE_PUBLIC_INTERFACE(SelectNC)

    EIGEN_STRONG_INLINE_DEVICE_FUNC Index rows() const
      { return m_condition.rows(); }

    EIGEN_STRONG_INLINE_DEVICE_FUNC Index cols() const
      { return m_condition.cols(); }

  protected:
    typename ConditionType::Nested m_condition;
    typename ThenArrayType::Nested m_then;
    typename ElseArrayType::Nested m_else;
};

namespace internal {

template<typename ConditionType, typename ThenArrayType, typename ElseArrayType>
struct evaluator<SelectNC<ConditionType, ThenArrayType, ElseArrayType> >
  : evaluator_base<SelectNC<ConditionType, ThenArrayType, ElseArrayType> >
{
  typedef SelectNC<ConditionType, ThenArrayType, ElseArrayType> XprType;
  enum { CoeffReadCost = evaluator<ConditionType>::CoeffReadCost + EIGEN_PLUGINS_PLAIN_ENUM_MAX(evaluator<ThenArrayType>::CoeffReadCost, evaluator<ElseArrayType>::CoeffReadCost) };
  enum { Alignment = EIGEN_PLUGINS_PLAIN_ENUM_MIN(evaluator<ThenArrayType>::Alignment, evaluator<ElseArrayType>::Alignment) };
  enum { Flags = (unsigned int)evaluator<ThenArrayType>::Flags & evaluator<ElseArrayType>::Flags & HereditaryBits };

  EIGEN_STRONG_INLINE_DEVICE_FUNC explicit evaluator(const XprType& select)
    : m_conditionImpl(select.conditionMatrix()), m_thenImpl(select.thenMatrix()), m_elseImpl(select.elseMatrix())
    { EIGEN_INTERNAL_CHECK_COST_VALUE(CoeffReadCost); }

  typedef typename XprType::CoeffReturnType CoeffReturnType;

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE CoeffReturnType coeff(Index row, Index col) const
    { return m_conditionImpl.coeff(row, col).select(m_thenImpl.coeff(row, col), m_elseImpl.coeff(row, col)); }

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE CoeffReturnType coeff(Index index) const
    { return m_conditionImpl.coeff(index).select(m_thenImpl.coeff(index), m_elseImpl.coeff(index)); }

protected:
  evaluator<ConditionType> m_conditionImpl;
  evaluator<ThenArrayType> m_thenImpl;
  evaluator<ElseArrayType> m_elseImpl;
};
