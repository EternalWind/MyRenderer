#include "SpectralData.h"

SpectralData::SpectralData(const float* data, unsigned sample_interval, unsigned start_wave_length, unsigned end_wave_length)
	: m_StartWaveLength(start_wave_length),
	  m_EndWaveLength(end_wave_length),
	  m_SampleInterval(sample_interval),
	  m_DataCount((end_wave_length - start_wave_length) / sample_interval)
{
	size_t buffer_size = sizeof(float) * m_DataCount;
	float* buffer = (float*)malloc(buffer_size);
	memcpy(buffer, data, buffer_size);

	m_Data.reset(buffer);
}

SpectralData::~SpectralData(void)
{
}
