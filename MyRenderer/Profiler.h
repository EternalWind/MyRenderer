#pragma once

#include <atomic>

#include "Defs.h"

using namespace std;

struct Profiler
{
	MAKE_STATIC(Profiler)

public:
	static atomic<float> renderTimePerFrame;
	static atomic_ullong numTriangles;
	static atomic_ullong numPrimaryRaysPerFrame;
	static atomic_ullong numRayTestsPerFrame;
	static atomic_ullong numIntersectionPerFrame;
};
