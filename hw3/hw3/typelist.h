#pragma once

struct NullType {};

template <typename ...>
struct TypeList;

template <typename H, typename ...T>
struct TypeList<H, T...>
{
	using Head = H;
	using Tail = TypeList<T...>;
};

template <typename ...>
struct TypeList
{
	using Head = NullType;
	using Tail = NullType;
};

using EmptyList = TypeList<>;