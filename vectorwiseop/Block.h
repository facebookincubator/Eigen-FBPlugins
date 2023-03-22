/* Copyright (c) Facebook, Inc. and its affiliates. */

template <int Size = Dynamic>
auto segment(Index start, std::enable_if_t<(Size > 0 || Size == Dynamic) && Direction == Horizontal, Index> size = Size) const
  { return this->_expression().template middleCols<Size>(start, size); }

template <int Size = Dynamic>
auto segment(Index start, std::enable_if_t<(Size > 0 || Size == Dynamic) && Direction == Horizontal, Index> size = Size)
  { return this->_expression().template middleCols<Size>(start, size); }

template <int Size = Dynamic>
auto segment(Index start, std::enable_if_t<(Size > 0 || Size == Dynamic) && Direction == Vertical, Index> size = Size) const
  { return this->_expression().template middleRows<Size>(start, size); }

template <int Size = Dynamic>
auto segment(Index start, std::enable_if_t<(Size > 0 || Size == Dynamic) && Direction == Vertical, Index> size = Size)
  { return this->_expression().template middleRows<Size>(start, size); }


template <int Size = Dynamic> auto tail(Index size = Size) const
  { return segment<Size>(Direction == Horizontal ? this->_expression().cols() - size : this->_expression().rows() - size, size); }

template <int Size = Dynamic> auto tail(Index size = Size)
  { return segment<Size>(Direction == Horizontal ? this->_expression().cols() - size : this->_expression().rows() - size, size); }

template <int Size = Dynamic> auto head(Index size = Size) const
  { return segment<Size>(0, size); }

template <int Size = Dynamic> auto head(Index size = Size)
  { return segment<Size>(0, size); }
