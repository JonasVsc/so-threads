#pragma once
#include <Canvas.h>

#include "Child.h"


class ChildForm
{
public:

	static std::unique_ptr<Child> create();

	static char* name() { return s_name; }
	static float* Tb() { return &s_Tb; }
	static float* Td() { return &s_Td; }
	static bool* ball() { return &s_has_ball; }

	static void reset();

private:

	static bool s_has_ball;
	static char s_name[255];
	static float s_Tb;
	static float s_Td;
};