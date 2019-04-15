#ifndef MANAGER_H
#define MANAGER_H

#include "ManagerInterface.h"
#include "AllocationExeption.h"
#include <fstream>
#include <cstring>
#include <list>
#include <vector>
#include <iostream>

namespace manager
{
	/// <summary>
	/// Manager, is a class, which emulates work wtih memory managment, 
	/// by distributing free space from previously allocated byte* data_pool_
	/// among the requsting objects
	/// </summary>
	class Manager : public ManagerInterface
	{
	private:
		static const int MAX_DATA_SIZE_IN_BYTES;
		static const std::string disk_file_name_;

	public:
		std::list<MemoryBlockData*> allocate(size_t size_in_bytes, size_t type_size) override;
		void free(std::list<ManagerInterface::MemoryBlockData*> blocks_to_delete) override;
		void DefragmentateFreeMemory();

		Manager();
		~Manager();

	private:
		Manager(const Manager&) = delete;
		Manager& operator=(const Manager&) = delete;

		void eraseBlock(MemoryBlockData* block);

	private:
		void* data_pool_;
		std::list<MemoryBlockData*> free_memory_blocks_;
		std::list<MemoryBlockData*> allocated_memory_blocks_;
		int distributed_space_;
	};
}

#endif