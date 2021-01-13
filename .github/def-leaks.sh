#!/bin/bash

diff -q                                                                                                   \
  <(grep -r --exclude-dir=test --exclude=Macros.h --regexp '#\s*define [ /\*]*\K[^ /(]*' -Po . | sort -u) \
  <(grep -r --exclude-dir=test --exclude=Macros.h --regexp  '#\s*undef [ /\*]*\K[^ /]*'  -Po . | sort   )
