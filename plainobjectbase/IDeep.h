/* Copyright (c) Facebook, Inc. and its affiliates. */

 private:
  template <typename Type> struct ideep_datatraits {
    static inline ideep::tensor::desc::data_type func()
      { return ideep::tensor::desc::data_type::undef; }
  };

  template <> struct ideep_datatraits<float> {
    static inline ideep::tensor::desc::data_type func()
      { return ideep::tensor::desc::data_type::f32; }
  };

  template <> struct ideep_datatraits<int> {
    static inline ideep::tensor::desc::data_type func()
      { return ideep::tensor::desc::data_type::s32; }
  };

  template <> struct ideep_datatraits<unsigned char> {
    static inline ideep::tensor::desc::data_type func()
      { return ideep::tensor::desc::data_type::u8; }
  };

  template <> struct ideep_datatraits<char> {
    static inline ideep::tensor::desc::data_type func()
      { return ideep::tensor::desc::data_type::s8; }
  };

 public:
  EIGEN_STRONG_INLINE ideep::tensor ideepTensor4D() {
    ideep::format_tag nhwc_fmttag = ideep::format_tag::nhwc;
    ideep::format_tag nchw_fmttag = ideep::format_tag::nchw;
    typedef ideep::tensor::desc::data_type data_type;
    int nrows = rows(), ncols = cols();

    if (NumChannels != 1) {
      ideep::tensor::desc::dims dims{1, nrows, ncols, NumChannels};
      data_type type = ideep_datatraits<ChannelType>::func();
      ideep::tensor::desc dtdesc(dims, type, nhwc_fmttag);
      return ideep::tensor(dtdesc, (ChannelType*) data());
    }

    if (NumChannels == 1) {
      ideep::tensor::desc::dims dims{1, NumChannels, nrows, ncols};
      data_type type = ideep_datatraits<ChannelType>::func();
      ideep::tensor::desc dtdesc(dims, type, nchw_fmttag);
      return ideep::tensor(dtdesc, (ChannelType*) data());
    }
  }
