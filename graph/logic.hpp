/*
 * logic.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LOGIC_H
#define LOGIC_H


namespace base {

struct NullType {};

template <int value>
struct IntType {
  enum { Value = value };
};

typedef IntType<true> True;
typedef IntType<false> False;

template <typename Cond, typename If, typename Else>
struct IfThenElse;

template <typename If, typename Else>
struct IfThenElse<True, If, Else> {
  typedef If Result;
};

template <typename If, typename Else>
struct IfThenElse<False, If, Else> {
  typedef Else Result;
};

template <typename H, typename T>
struct TypeList {
  typedef H Head;
  typedef T Tail;
};

template <typename TypeList, template <typename> class Proc>
struct Map;

template <template <typename> class Proc>
struct Map<NullType, Proc> {
  typedef NullType type;
};

template <typename TypeList, typename Meta,
         template <typename, typename> class Proc>
struct Fold;

template <typename Meta, template <typename, typename> class Proc>
struct Fold<NullType, Meta, Proc> {
  typedef Meta type;
};

template <int val>
struct StaticPrint {
  operator char() {
    return val + 0xff;
  }
};

#define __print(tag, ...) char print_value_##tag \
  = StaticPrint<__VA_ARGS__>()

template <typename D, typename T>
struct IsDerivedFrom {
  typedef char yes[1];
  typedef char no[2];

  static yes& test(T*);
  static no& test(...);

  static D* self();
  using Result = IntType<sizeof(test(self())) == sizeof(yes)>;
};


template <typename TA, typename TB>
struct IsSameType : False {};

template <typename T>
struct IsSameType<T, T> : True {};


template <typename KeyT, typename ValT>
struct Meta {
  typedef KeyT Key;
  typedef ValT Val;
};

template <typename Key, typename List>
struct IfExistInSet;

template <typename Key>
struct IfExistInSet<Key, NullType> {
  using Result = False;
};

template <typename Key, typename Val, typename Tail>
struct IfExistInSet<Key, TypeList<Meta<Key, Val>, Tail>> {
  using Result = True;
};

template <typename Key, typename Val, typename Head, typename Tail>
struct IfExistInSet<Key, TypeList<Meta<Head, Val>, Tail>> {
  using Result = typename IfExistInSet<Key, Tail>::Result;
};

template <typename meta, typename List>
struct Append {
 using Result = TypeList<meta, List>;
};

template <typename Key, typename Val, typename List>
struct Append<Meta<Key, Val>, List> {
  using Result = typename IfThenElse<
    typename IfExistInSet<Key, List>::Result,
             List,
             TypeList<Meta<Key, Val>, List>
               >::Result ;
};

template <typename Key, typename List>
struct Find;

template <typename Key>
struct Find<Key, NullType> {
  using Result = NullType;
};

template <typename Key, typename Val, typename Tail>
struct Find<Key, TypeList<Meta<Key, Val>, Tail>> {
  using Result = Val;
};

template <typename Key, typename Val, typename Head, typename Tail>
struct Find<Key, TypeList<Meta<Head, Val>, Tail>> {
  using Result = typename Find<Key, Tail>::Result;
};

template <typename Key, typename Val, typename List>
struct SetKV;

template <typename Key, typename Val, typename Val2, typename Tail>
struct SetKV<Key, Val, TypeList<Meta<Key, Val2>, Tail>> {
  using Result = TypeList<Meta<Key, Val>, Tail>;
};

template <typename Key, typename Val, typename Head, typename Tail> 
struct SetKV<Key, Val, TypeList<Head, Tail>> {
  using Result = TypeList<Head, typename SetKV<Key, Val, Tail>::Result>;
};

template <typename Key, typename Val>
struct SetKV<Key, Val, NullType> {
  using Result = NullType;
};

template <typename Key, typename List>
struct Delete;

template <typename Key, typename Val, typename List>
struct Delete<Key, TypeList<Meta<Key, Val>, List>> {
  using Result = List;
};

template <typename Key, typename Head, typename Tail>
struct Delete<Key, TypeList<Head, Tail>> {
  using Result = TypeList<Head, typename Delete<Key, Tail>::Result>;
};

template <typename Key>
struct Delete<Key, NullType> {
  using Result = NullType;
};


#ifdef META_TEST

class A {};
class B : public A {};

//char a = StaticPrint<IsDerivedFrom<A, B>::Result>();
// __print(_A_is_drived_from_B, IsDerivedFrom<A, B>::Result);
// char a = IsDerivedFrom<A, B>::Result + 0xff;
static_assert(IsSameType<typename IsDerivedFrom<B, A>::Result, True>::Value, "");
static_assert(IsSameType<typename IsDerivedFrom<A, B>::Result, False>::Value, "");
static_assert(IsSameType<typename IsDerivedFrom<A, A>::Result, True>::Value, "");
static_assert(IsSameType<A, A>::Value == true, "");
static_assert(IsSameType<A, B>::Value == false, "");
static_assert(!IfExistInSet<IntType<1>, NullType>::Result::Value, "");
static_assert(IfExistInSet<IntType<1>, TypeList<Meta<IntType<1>, NullType>, NullType>>::Result::Value, "");

typedef
typename Append<
      Meta<IntType<1>, IntType<5>>,
      typename
        Append<Meta<IntType<2>, IntType<44>>,
        NullType>::Result
      >::Result my_set;

static_assert(Find<IntType<2>, my_set>::Result::Value == 44, "");
static_assert(Find<IntType<1>, my_set>::Result::Value == 5, "");

typedef typename SetKV<IntType<1>, IntType<22>, my_set>::Result my_set2;

static_assert(Find<IntType<1>, my_set2>::Result::Value == 22, "");

typedef typename Delete<IntType<1>, my_set2>::Result my_set3;

static_assert(Find<IntType<2>, my_set3>::Result::Value == 44, "");
static_assert(Find<IntType<1>, my_set3>::Result::Value == 22, "");


// static_assert(IsDerivedFrom<A, B>::Result, "");
// __print(_B_is_drived_from_A, IsDerivedFrom<B, A>::Result::Value);
// static_assert(typename IsDerivedFrom<B, A>::Result::Value == 0, "");
// __print(_A_is_drived_from_A, IsDerivedFrom<A, A>::Result::Value);
// static_assert(typename IsDerivedFrom<A, A>::Result::Value, "");

#endif

}

#endif /* !LOGIC_H */
