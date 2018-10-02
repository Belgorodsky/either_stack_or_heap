#include <new>
#include <memory>
#include <cstdlib>

struct StackOnly 
{
	void* operator new (std::size_t size) = delete;
	void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) noexcept = delete;
	void* operator new (std::size_t size, void* ptr) noexcept = delete;

	int val;
};

struct HeapOnly
{
	static std::unique_ptr<HeapOnly> create()
	{
		return std::unique_ptr<HeapOnly>(new (std::nothrow)HeapOnly);
	}

	int val;

	private: 
		HeapOnly() = default;
};

int main()
{
	StackOnly stack_only;
//	auto error1 = new StackOnly;

	// hack for allocate StackOnly on the heap
	StackOnly *ptr = static_cast<StackOnly*>(std::malloc(sizeof(StackOnly)));
	// but still cannot call constructor
//	auto error2 = new (ptr) StackOnly();
	ptr->~StackOnly();
	std::free(ptr);

	auto heap_only = HeapOnly::create();
//	HeapOnly error3;
}

