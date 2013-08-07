#include "SpectralData.h"

#include "Exception.h"

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

float SpectralData::DataAt(unsigned index) const
{
	if (index >= m_DataCount)
		throw Exception("The given index is out-of-range.");

	return m_Data.get()[index];
}

unsigned SpectralData::StartWaveLength() const
{
	return m_StartWaveLength;
}

unsigned SpectralData::EndWaveLength() const
{
	return m_EndWaveLength;
}

unsigned SpectralData::SampleInterval() const
{
	return m_SampleInterval;
}

unsigned SpectralData::DataCount() const
{
	return m_DataCount;
}

SpectralData::~SpectralData(void)
{
}
