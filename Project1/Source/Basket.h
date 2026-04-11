#pragma once

class Basket
{
public:

    constexpr static int capacity = 10;

    void add_item();
    void remove_item();

    bool full() const { return items >= capacity; }
    bool empty() const { return items <= 0; }

private:

    int items{ 0 };

}; // class Basket