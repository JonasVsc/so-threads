#include "CanvasTime.h"

namespace canvas
{
	void Time::init()
	{
		s_last_ticks = SDL_GetTicksNS();
		s_delta_time = 0.0f;
	}

	void Time::tick()
	{
		Uint64 current_ticks = SDL_GetTicksNS();
		// Diferença em nanossegundos convertida para segundos (float)
		s_delta_time = static_cast<float>(current_ticks - s_last_ticks) / 1'000'000'000.0f;
		s_last_ticks = current_ticks;
	}

} // namespace canvas