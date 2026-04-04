#pragma once
#include <Canvas.h>

enum class ChildStatus : uint8_t
{
	Playing,
	WaitingForBall,
	WaitingForSpace,
	Resting
};


struct Child
{
	void create(const char* name, bool has_ball, float tb, float td);

	Child() = default;

	Child(const Child&) = delete;
	Child& operator=(const Child&) = delete;

	~Child();

	const char* get_name() { return m_name.c_str(); }
	float* get_Tb() { return &m_Tb; }
	float* get_Td() { return &m_Td; }
	bool* get_ball() { return &m_has_ball; }

private:

	static int s_id;

	int m_id{};
	std::string m_name{};
	float m_Tb{}, m_Td{};
	bool m_has_ball{};

	SDL_Thread* m_thread{};
	ChildStatus m_status{};
};
