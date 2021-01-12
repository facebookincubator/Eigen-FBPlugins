/* Copyright (c) Facebook, Inc. and its affiliates. */

const WithFormat<Derived> format(int precision, int flags,
                                 const std::string& csep,
                                 const std::string& rsep,
                                 const std::string& rpre,
                                 const std::string& rsuf,
                                 const std::string& mpre,
                                 const std::string& msuf) const
  { return derived().format(IOFormat(precision, flags, csep, rsep, rpre, rsuf, mpre, msuf)); }
