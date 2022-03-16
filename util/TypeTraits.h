/* Copyright (c) Facebook, Inc. and its affiliates. */

template <typename Derived> struct is_product_expr {
    template<typename T> struct test { enum { value = 0 }; };

    template <typename L, typename R, int xyz>
    struct test<Product<L, R, xyz> > { enum { value = 1 }; };

    enum { value = (test<Derived>::value == 1) };
};

template <typename Type> struct type_wrapper;
template <typename Type> struct type_wrapper<void (*)(Type)>
  { typedef Type type; };

template <typename Tp> struct NoneType {};

template <typename> struct make_int
  { typedef int type; };

template <typename T> using ultimate_ref_selector =
    std::conditional<is_lvalue<T>::value, typename ref_selector<T>::non_const_type, typename ref_selector<T>::type>;
