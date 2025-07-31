#pragma once

enum class enumMino : int
{
	none = 0,
	Z = 1,
	S = 2,
	J = 3,
	L = 4,
	I = 5,
	O = 6,
	T = 7,
	jammer = 8,
	wall = 9
};

enum class enumDeleteLine : int
{
	zero = 0,
	oneline = 1,
	twoline = 2,
	threeline = 3,
	tetris = 4,
	tspine_single = 5,
	tspine_double = 6,
	tspine_triple = 7
};

enum class enumGameMode : int 
{
	endless = 0,
	sprint = 1,
	ultra = 2,
	marathon = 3
};
