#pragma once
#include <memory>

#include "Exception.h"

using namespace std;

class SpectralData
{
public:
	SpectralData(const float* data, unsigned sample_interval, unsigned start_wave_length, unsigned end_wave_length);

	float DataAt(unsigned index) const;

	unsigned StartWaveLength() const;

	unsigned EndWaveLength() const;

	unsigned SampleInterval() const;

	unsigned DataCount() const;

	~SpectralData(void);

private:
	unique_ptr<float[]> m_Data;
	unsigned m_StartWaveLength;
	unsigned m_EndWaveLength;
	unsigned m_SampleInterval;
	unsigned m_DataCount;
};

// Implementation for inline methods.

inline float SpectralData::DataAt(unsigned index) const
{
	if (index >= m_DataCount)
		throw Exception("The given index is out-of-range.");

	return m_Data.get()[index];
}

inline unsigned SpectralData::StartWaveLength() const
{
	return m_StartWaveLength;
}

inline unsigned SpectralData::EndWaveLength() const
{
	return m_EndWaveLength;
}

inline unsigned SpectralData::SampleInterval() const
{
	return m_SampleInterval;
}

inline unsigned SpectralData::DataCount() const
{
	return m_DataCount;
}
