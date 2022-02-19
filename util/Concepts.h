/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename T> concept IsVectorExpression = (traits<T>::RowsAtCompileTime == 1 || traits<T>::ColsAtCompileTime == 1);
template <typename T> concept IsLValueExpression = bool(traits<T>::Flags & LvalueBit);
