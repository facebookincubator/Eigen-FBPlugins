/* Copyright (c) Facebook, Inc. and its affiliates. */

#include "./Block-helper.h"

template <int Size = Dynamic> auto segment(Index start, Index size = Size) const
  { return segmentHelper<Direction>::template apply<Size>(this->_expression(), start, size); }

template <int Size = Dynamic> auto segment(Index start, Index size = Size)
  { return segmentHelper<Direction>::template apply<Size>(this->_expression(), start, size); }

template <int Size = Dynamic> auto tail(Index size = Size) const
  { return segment<Size>(Direction == Horizontal ? this->_expression().cols() - size
                         : this->_expression().rows() - size, size); }

template <int Size = Dynamic> auto tail(Index size = Size)
  { return segment<Size>(Direction == Horizontal ? this->_expression().cols() - size
                         : this->_expression().rows() - size, size); }

template <int Size = Dynamic> auto head(Index size = Size) const
  { return segment<Size>(0, size); }

template <int Size = Dynamic> auto head(Index size = Size)
  { return segment<Size>(0, size); }
