#ifndef MANAGER_INTERFACE_H
#define MANAGER_INTERFACE_H

#include <list>

namespace manager
{
	/// <summary>
	/// An interface, which gives opportunity to use different
	///  MemoryManager implementations (in this project there is only one implementation)
	/// </summary>
	class ManagerInterface
	{
	public:
		typedef char byte;

		struct MemoryBlockData
		{
			byte* offset_pointer;
			int byte_size;

			MemoryBlockData() : offset_pointer(nullptr), byte_size(0)
			{
			}

			bool operator==(const MemoryBlockData& second) const
			{
				return (offset_pointer == second.offset_pointer && byte_size == second.byte_size);
			}
		};

	public:
		virtual std::list<MemoryBlockData*> allocate(size_t size_in_bytes, size_t type_size) = 0;
		virtual void free(std::list<MemoryBlockData*>) = 0;
	};
}

#endif