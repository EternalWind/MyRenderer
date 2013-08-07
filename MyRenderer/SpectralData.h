#pragma once
#include <memory>

using namespace std;

class SpectralData
{
public:
	SpectralData(const float* data, unsigned sample_interval, unsigned start_wave_length, unsigned end_wave_length);

	inline float DataAt(unsigned index) const;

	inline unsigned StartWaveLength() const;

	inline unsigned EndWaveLength() const;

	inline unsigned SampleInterval() const;

	inline unsigned DataCount() const;

	~SpectralData(void);

private:
	shared_ptr<float> m_Data;
	unsigned m_StartWaveLength;
	unsigned m_EndWaveLength;
	unsigned m_SampleInterval;
	unsigned m_DataCount;
};

