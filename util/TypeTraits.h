/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Derived> struct is_product_expr {
    template<typename T> struct test { enum { value = 0 }; };

    template <typename L, typename R, int xyz>
    struct test<Product<L, R, xyz> > { enum { value = 1 }; };

    enum { value = (test<Derived>::value == 1) };
};

template <typename Derived> struct is_rowwise {
    template<class> struct test { enum { value = 0 }; };

    template <typename Type>
    struct test<VectorwiseOp<Type, Horizontal> >
      { enum { value = 1 }; };

    template <typename Tp>
    struct test<VectorwiseOpExt<Tp, Horizontal> >
      { enum { value = 1 }; };

    enum { value = (test<Derived>::value == 1) };
};

template <typename Derived> struct is_colwise {
    template<class> struct test { enum { value = 0 }; };

    template <typename ExprTp>
    struct test<VectorwiseOp<ExprTp, Vertical> >
      { enum { value = 1 }; };

    template <typename Expr>
    struct test<VectorwiseOpExt<Expr, Vertical> >
      { enum { value = 1 }; };

    enum { value = (test<Derived>::value == 1) };
};

template <typename> struct make_int
  { typedef int type; };

template <typename Expr> struct ultimate_ref_selector {
  typedef typename ref_selector<Expr>::non_const_type Type1;
  typedef typename ref_selector<Expr>::type Type2;
  enum { lv = is_lvalue<Expr>::value };

  typedef typename conditional<lv, Type1, Type2>::type type;
};

template <> struct ref_selector<void>
  { typedef void non_const_type; typedef void type; };

template <typename T, template <typename> class U>
struct is_instance/********/: false_type {};

template <> struct ultimate_ref_selector<void>
  { typedef void type; };

template <typename T, template <typename> class U>
struct is_instance<U<T>, U> : true_type  {};

template <typename Derived> struct is_eigen_type
  { template <typename T> static char test(char (*)[sizeof(traits<T>)]);
    template <typename T> static long test(...);
    enum { value = (sizeof(test<Derived>(0)) == 1) }; };

template <typename Type> struct type_wrapper;
template <typename Type> struct type_wrapper<void (*)(Type)>
  { typedef Type type; };

template <typename Tp> struct NoneType {};
