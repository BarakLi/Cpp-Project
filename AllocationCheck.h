#ifndef ALLOCATIONCHECK_H
#define ALLOCATIONCHECK_H
#pragma warning(disable: 4996)
#include <memory>
#include <iostream>
using namespace std;

typedef struct MemAllocation
{
	uint32_t totalAllocated = 0;
	uint32_t totalFreed = 0;
	uint32_t CurrentUsage() { return totalAllocated - totalFreed; }
};

static MemAllocation memAlloc;

void* operator new(size_t size)
{
	memAlloc.totalAllocated += size;
	return malloc(size);

}

void operator delete(void* memory, size_t size)
{
	memAlloc.totalFreed += size;
	free(memory);

}

#endif