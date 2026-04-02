#pragma once
#include <string>
#include <cstdint>
#include <memory>

class ItemDefinition;

enum class ItemType : uint8_t
{
	Tool,
	Consumable
};

struct ItemText
{
	std::string name;
	std::string description;
};

struct ItemData
{
	std::string ID;

	ItemType type;

	ItemText text;

	std::weak_ptr<ItemDefinition> base;

};