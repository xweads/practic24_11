#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Planar.hpp"

struct Vector: Planar{
  virtual int x() const = 0;
  virtual int y() const = 0;
  virtual int abs_sqr() const = 0;
  virtual ~Vector() = default;
};

#endif
