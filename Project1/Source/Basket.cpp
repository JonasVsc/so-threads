#include "Basket.h"

void Basket::add_item()
{
    if (items < capacity)
    {
        ++items;
    }
}

void Basket::remove_item()
{
    if (items > 0)
    {
        --items;
    }
}