#include <Canvas.h>
#include <array>

// Sync Objects

constexpr uint32_t buffer_size{ 100u };

SDL_Mutex* mtx{ nullptr };
SDL_Semaphore* empty{ nullptr };
SDL_Semaphore* full{ nullptr };

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

	static bool is_full() { return m_count == buffer_size; }
	static bool is_empty() { return m_count == 0; }

private:

	inline static std::array<Item, buffer_size> m_items{};
	inline static uint32_t m_count{};
};


static int SDLCALL producer(void* data)
{
	static uint32_t id = 0;

	while (true)
	{
		Item item{ std::format("AwesomeItem{}", id++) };

		SDL_WaitSemaphore(empty);

		{
			SDL_LockMutex(mtx);
			canvas::log("Inserting: {}", item.name);
			ItemManager::insert_item(item);
			SDL_UnlockMutex(mtx);
		}

		SDL_SignalSemaphore(full);
	}

	return 0;
}

static int SDLCALL consumer(void* data)
{
	while (true)
	{
		SDL_WaitSemaphore(full);
		Item item;

		{
			SDL_LockMutex(mtx);
			item = ItemManager::remove_item();
			SDL_UnlockMutex(mtx);
		}

		SDL_SignalSemaphore(empty);
		ItemManager::consume_item(item);
	}

	return 0;
}

int main()
{
	mtx = SDL_CreateMutex();
	full = SDL_CreateSemaphore(0u);
	empty = SDL_CreateSemaphore(buffer_size);

	if (!mtx || !full || !empty)
	{
		canvas::log("Failed to create sync objects");
		return 1;
	}


	SDL_Thread* t1{ nullptr };
	SDL_Thread* t2{ nullptr };

	t1 = SDL_CreateThread(producer, "ProducerThread", nullptr);
	t2 = SDL_CreateThread(consumer, "ConsumerThread", nullptr);


	if (!t1 || !t2)
	{
		canvas::log("Failed to create thread");
		return 1;
	}


	int ret{};
	SDL_WaitThread(t1, &ret);
	canvas::log("Thread T1 encerrado com status {}", ret);

	SDL_WaitThread(t2, &ret);
	canvas::log("Thread T2 encerrado com status {}", ret);


	return 0;
}