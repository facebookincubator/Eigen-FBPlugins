/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename T> concept IsFixedSizeExpression = (traits<T>::RowsAtCompileTime != Dynamic && traits<T>::ColsAtCompileTime != Dynamic);
template <typename T> concept IsVectorExpression = (traits<T>::RowsAtCompileTime == 1 || traits<T>::ColsAtCompileTime == 1);
template <typename T> concept IsFixedSizeVectorExpression = (IsFixedSizeExpression<T> && IsVectorExpression<T>);
template <typename T> concept IsRowMajorExpression = bool(traits<T>::Flags & RowMajorBit);
template <typename T> concept IsLValueExpression = bool(traits<T>::Flags & LvalueBit);
