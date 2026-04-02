#include <semaphore>
#include <cstdint>
#include <thread>
#include <print>
#include <mutex>
#include <array>
#include <string_view>
#include <cassert>

// Sync Objects

static constexpr uint32_t maxItems{ 100 };

std::mutex mtx;
std::counting_semaphore full(maxItems);
std::binary_semaphore empty(0);

// Structs

struct Item
{
	std::string name{};
};

class ItemManager
{
public:
	
	static void consume_item(Item& item)
	{
		std::println("Consuming: {}", item.name);
	}

	static void insert_item(Item& item) 
	{ 
		assert(!is_full() && "failed to insert item. m_items is full");
		m_items[m_count++] = item;
	}

	static Item remove_item() 
	{
		assert(!is_empty() && "failed to remove item. m_items is empty");
		return m_items[--m_count]; 
	}

	static bool is_full() { return m_count == maxItems; }
	static bool is_empty() { return m_count == 0; }

private:

	inline static std::array<Item, maxItems> m_items{};
	inline static uint32_t m_count{};
};


static void producer()
{
	static uint32_t id = 0;

	while (true)
	{
		Item item{ std::format("AwesomeItem{}", id++) };
		full.acquire();

		{
			std::lock_guard<std::mutex> lock(mtx);
			std::println("Inserting: {}", item.name);
			ItemManager::insert_item(item);
		}

		empty.release();
	}
}

static void consumer()
{
	while (true)
	{
		empty.acquire();
		Item item;
		
		{
			std::lock_guard<std::mutex> lock(mtx);
			item = ItemManager::remove_item();
		}

		full.release();
		ItemManager::consume_item(item);
	}
}

int main()
{
	std::thread t1(producer);
	std::thread t2(consumer);

	t1.join();
	t2.join();

	return 0;
}