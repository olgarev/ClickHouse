#pragma once
#include <Common/Visitor.h>
#include <Core/TypeListNumber.h>

namespace DB::GatherUtils
{
#pragma GCC visibility push(hidden)

template <typename T>
struct NumericArraySource;

struct GenericArraySource;

template <typename ArraySource>
struct NullableArraySource;

template <typename Base>
struct ConstSource;

using NumericArraySources = typename TypeListMap<NumericArraySource, TypeListNumbersAndUInt128>::Type;
using BasicArraySources = typename AppendToTypeList<GenericArraySource, NumericArraySources>::Type;
using NullableArraySources = typename TypeListMap<NullableArraySource, BasicArraySources>::Type;
using BasicAndNullableArraySources = typename TypeListConcat<BasicArraySources, NullableArraySources>::Type;
using ConstArraySources = typename TypeListMap<ConstSource, BasicAndNullableArraySources>::Type;
using TypeListArraySources = typename TypeListConcat<BasicAndNullableArraySources, ConstArraySources>::Type;

using ArraySourceVisitor = typename ApplyTypeListForClass<Visitor, TypeListArraySources>::Type;

template <typename Derived>
using ArraySourceVisitorImpl = VisitorImpl<Derived, ArraySourceVisitor>;

#pragma GCC visibility pop
}
