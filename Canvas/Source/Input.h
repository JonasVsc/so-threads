#pragma once
#include "KeyCode.h"
#include <bitset>

namespace canvas
{
	class Input
	{
	public:

		inline static void update()
		{
			s_prev_keys = s_keys;
		}

		inline static bool is_key_pressed(KeyCode key)
		{
			return s_keys.test((size_t)key) && !s_prev_keys.test((size_t)key);
		}

		inline static bool is_key_down(KeyCode key)
		{
			return s_keys.test((size_t)key);
		}

		inline static bool is_key_released(KeyCode key)
		{
			return !s_keys.test((size_t)key) && s_prev_keys.test((size_t)key);
		}

		inline static void set_key(KeyCode key, bool down)
		{
			s_keys.set((size_t)key, down);
		}

	private:

		inline static std::bitset<(size_t)KeyCode::Count> s_keys;
		inline static std::bitset<(size_t)KeyCode::Count> s_prev_keys;

	}; // class Input

	

} // namespace canvas