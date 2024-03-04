#pragma once
#define SIZE_MEM 1048576
#include <iostream>
#include <cinttypes>

using namespace std;

class frbl
{
private:
	struct Block
	{
		Block* next_block_ptr;
		size_t availible_block_size;
	};

	const size_t mem_page_size = SIZE_MEM;
	uint32_t* mem_page_ptr;
	Block* first_block_ptr;

public:
	frbl();
	virtual ~frbl();
	void* fmalloc(const size_t size);
	void ffree(const void* ptr, const size_t size);


};