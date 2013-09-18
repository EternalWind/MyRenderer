#include "Profiler.h"

atomic<float> Profiler::renderTimePerFrame = 0.f;
atomic_ullong Profiler::numIntersectionPerFrame = { (unsigned long long)0 };
atomic_ullong Profiler::numPrimaryRaysPerFrame = { (unsigned long long)0 };
atomic_ullong Profiler::numRayTriangleTestsPerFrame = { (unsigned long long)0 };
atomic_ullong Profiler::numTriangles = { (unsigned long long)0 };
atomic_ullong Profiler::numRayVolumeTestsPerFrame = { (unsigned long long)0 };
atomic_ullong Profiler::numBoundingVolumes = { (unsigned long long)0 };