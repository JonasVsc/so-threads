#include "ChildForm.h"

char ChildForm::s_name[255]{};
float ChildForm::s_Tb{};
float ChildForm::s_Td{};
bool ChildForm::s_has_ball{};

std::unique_ptr<Child> ChildForm::create()
{
	auto child = std::make_unique<Child>();
	child->create(s_name, s_has_ball, s_Tb, s_Td);
	
	reset();
	
	return child;
}

void ChildForm::reset()
{
	memset(s_name, 0, sizeof(s_name));
	s_Tb = 0;
	s_Td = 0;
	s_has_ball = false;
}