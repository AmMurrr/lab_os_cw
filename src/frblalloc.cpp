#include "frblalloc.hpp"
#include <iostream>
#include <cinttypes>

using namespace std;

frbl::frbl()
{
	//initialize method
	mem_page_ptr = (uint32_t*)malloc(mem_page_size);

	if (mem_page_ptr == nullptr) {
		throw runtime_error("Error: Cannot allocate a memory page");
	}

	first_block_ptr = (Block*)mem_page_ptr;
	first_block_ptr->next_block_ptr = nullptr;
	first_block_ptr->availible_block_size = mem_page_size;

}
frbl::~frbl()
{
	if (mem_page_ptr != nullptr) {
		::free(mem_page_ptr);
	}
}

void* frbl::fmalloc(const size_t size)
{
	// cout << first_block_ptr->availible_block_size << endl;
	if (size == 0) {
		return nullptr;
	}
	//user cant request allocation of size less than size of Block struct
	const size_t req_size = max(size, sizeof(Block));
	size_t fit_min = 1e8;
		Block* block_ptr = first_block_ptr;

	while(block_ptr != nullptr) {
		//find more perfect fit of availible memory
		if (block_ptr->availible_block_size >= req_size + sizeof(Block)) {
			if (block_ptr->availible_block_size - (req_size + sizeof(Block)) <= fit_min) { 
				fit_min = block_ptr->availible_block_size - (req_size + sizeof(Block));

			}
		}

		block_ptr = block_ptr->next_block_ptr;

	}


	//error if there are no fits
	if (fit_min == 1e8) {
		throw runtime_error("Error: Can't allocate requested memory");
	}
	block_ptr = first_block_ptr;
	while(block_ptr != nullptr) {

		//take this space in block
		if (block_ptr->availible_block_size - (req_size + sizeof(Block)) == fit_min) {
			uint8_t* take_block_space_ptr = (uint8_t*)block_ptr + block_ptr->availible_block_size - req_size; 
			block_ptr->availible_block_size = block_ptr->availible_block_size - req_size;
			return take_block_space_ptr;
		}
		block_ptr = block_ptr->next_block_ptr;
	}
	throw runtime_error("Error: Can't allocate requested memory");
}


void frbl::ffree(const void* ptr, const size_t size)
{
	if (ptr == nullptr) {
		return;
	}

	const size_t freed_space = max(size, sizeof(Block));

	Block* freed_block_ptr = (Block*)ptr;
	freed_block_ptr->next_block_ptr = nullptr;
	freed_block_ptr->availible_block_size = freed_space;

	Block* block_ptr = first_block_ptr;
	Block** previous_ptr_ptr = &block_ptr;

	while(block_ptr != nullptr) {

		if (ptr < block_ptr) {

			freed_block_ptr->next_block_ptr = block_ptr;

			break;
		}
		previous_ptr_ptr = &block_ptr->next_block_ptr;
		block_ptr = block_ptr->next_block_ptr;

	}
	*previous_ptr_ptr = freed_block_ptr;


}

