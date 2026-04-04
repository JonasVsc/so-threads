#include "Child.h"

int Child::s_id{};

static int SDLCALL child_fn(void* data)
{
	Child* child_data = static_cast<Child*>(data);
	while (true)
	{
		// timer Tb, Td.
		// brincar / decansar
		// status
	}
}

void Child::create(const char* name, bool has_ball, float tb, float td)
{
	m_id = s_id++;

	m_name = name;
	m_has_ball = has_ball;
	m_Tb = tb;
	m_Td = td;

	m_thread = SDL_CreateThread(child_fn, "ThreadChild", this);
}

Child::~Child()
{
	if (m_thread)
	{
		SDL_WaitThread(m_thread, nullptr);
	}
}