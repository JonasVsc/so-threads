#pragma once
#include <SDL3/SDL.h>

namespace canvas
{
	class Time
	{
	public:

		static void init();

		static void tick();

		static float delta_time() { return s_delta_time; }

	private:

		static inline Uint64 s_last_ticks{ 0 };
		static inline float s_delta_time{ 0.0f };

	}; // class Time

} // namespace canvas