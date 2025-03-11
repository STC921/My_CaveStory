#ifndef SPRITE_STATE_H
#define SPRITE_STATE_H

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#define ENUM_FOREACH(var, enum_name) \
	for (int var = FIRST_##enum_name; var < LAST_##enum_name; ++var)

enum HorizontalFacing{
	FIRST_HORIZONTAL_FACING,
	LEFT = FIRST_HORIZONTAL_FACING,
	RIGHT,
	LAST_HORIZONTAL_FACING,
};
enum VerticalFacing{
	FIRST_VERTICAL_FACING,
	UP = FIRST_VERTICAL_FACING,
	DOWN,
	HORIZONTAL,
	LAST_VERTICAL_FACING,
};
enum TrapFacing{
	FIRST_FACING,
	U = FIRST_FACING,
	D,
	L,
	R,
	LAST_FACING
};

#endif