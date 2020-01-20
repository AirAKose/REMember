#pragma once

#include <type_traits>
#include <cstdint>

template<typename ... Types>
struct get_last_type { using type = void; };

template<template<typename...> class Set, typename ... Types>
struct get_last_type<Set<Types...>> { using type = typename get_last_type<Types...>::type; };

template<typename First, typename ... Types>
struct get_last_type<First, Types...> { using type = typename get_last_type<Types...>::type; };

template<typename Last>
struct get_last_type<Last> { using type = Last; };

template<typename ... Types>
using get_last_type_t = typename get_last_type<Types...>::type;



template<typename ... Types>
struct get_first_type { using type = void; };

template<template<typename...> class Set, typename ... Types>
struct get_first_type<Set<Types...>> { using type = typename get_first_type<Types...>::type; };

template<typename First, typename ... Types>
struct get_first_type<First, Types...> { using type = First; };

template<typename ... Types>
using get_first_type_t = typename get_first_type<Types...>::type;



template<typename Type>
struct get_member_owner { using type = void; };

template<typename Type, typename Owner>
struct get_member_owner<Type(Owner::*)> { using type = Owner; };

template<typename Type>
using get_member_owner_t = typename get_member_owner<Type>::type;



template<typename Type>
struct get_member_type { using type = void; };

template<typename Type, typename Owner>
struct get_member_type<Type(Owner::*)> { using type = Type; };

template<typename Type>
using get_member_type_t = typename get_member_type<Type>::type;



template<auto ... Elems>
struct get_count
{
    constexpr static std::size_t value = 0;
};
template<auto Elem, auto ... Elems>
struct get_count<Elem, Elems...>
{
    constexpr static std::size_t value = 1 + get_count<Elems...>::value;
};

template<auto ... Elems>
constexpr inline auto get_count_v = get_count<Elems...>::value;