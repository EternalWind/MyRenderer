#include <fstream>

#include "Image.h"
#include "Exception.h"
#include "Math.h"

Image::Image(unsigned width, unsigned height)
	: m_Width(width),
	  m_Height(height),
	  m_Data(nullptr)
{
	unsigned buffer_size = m_Width * m_Height * sizeof(ColorRGBA);
	ColorRGBA* buffer = (ColorRGBA*)malloc(buffer_size);

	memset(buffer, 0, buffer_size);
	m_Data.reset(buffer);
}

Image::Image(const Image& other)
	: m_Width(other.m_Width),
	  m_Height(other.m_Height)
{
	unsigned buffer_size = m_Width * m_Height * sizeof(ColorRGBA);
	ColorRGBA* buffer = (ColorRGBA*)malloc(buffer_size);
	
	memcpy(buffer, other.m_Data.get(), buffer_size);
	m_Data.reset(buffer);
}

Image::Image(string path)
{
	std::ifstream file;
	file.open(path);

	if (!file.good() || !file.is_open())
		throw Exception(string("Failed to open the given file: ") + path + string("."));

	char img_type[2];
	unsigned width = 0;
	unsigned height = 0;
	char max_val[10];

	file.getline(img_type, 10);
	file.getline((char*)&width, 10, ' ');
	file.getline((char*)&height, 10);
	file.getline(max_val, 10);

	if (strcmp(img_type, "P6") != 0)
	{
		throw Exception("The given image file is not of type \"P6\".");
	}
	if (strcmp(max_val, "255") != 0)
	{
		throw Exception("The max value in the given image is not 255.");
	}

	ColorRGBA* buffer = (ColorRGBA*)malloc(width * height * sizeof(ColorRGBA));

	for (unsigned j = 0; j < height; ++j) {
        for (unsigned i = 0; i < width; ++i) {
            unsigned char r = 0;
            unsigned char g = 0;
            unsigned char b = 0;

            file >> r >> g >> b;
			buffer[j * width + i].SetRed(r / 255.f);
			buffer[j * width + i].SetGreen(g / 255.f);
			buffer[j * width + i].SetBlue(b / 255.f);
			buffer[j * width + i].SetAlpha(1.0f);
        }
    }

	m_Width = width;
	m_Height = height;
	m_Data.reset(buffer);

    file.close();
}

Image Image::operator = (const Image& other)
{
	unsigned buffer_size = other.m_Width * other.m_Height * sizeof(ColorRGBA);
	ColorRGBA* buffer = (ColorRGBA*)malloc(buffer_size);
	
	memcpy(buffer, other.m_Data.get(), buffer_size);
	this->m_Width = other.m_Width;
	this->m_Height = other.m_Height;
	this->m_Data.reset(buffer);

	return *this;
}

void Image::SaveAsPPM(string path, bool gamma_encoding, float gamma) const
{
	std::ofstream file;
	file.open(path);

	if (!file.is_open())
		throw Exception(string("Failed to save to file: ") + path + string("."));

	ColorRGBA* pixel = m_Data.get();

	file << "P6\n" << this->m_Width << " " << this->m_Height << "\n255\n";

	for (unsigned j = 0; j < m_Height; ++j) {
        for (unsigned i = 0; i < m_Width; ++i) {
			unsigned char r = 0;
			unsigned char g = 0;
			unsigned char b = 0;

			if (gamma_encoding)
			{
				r = (unsigned char)(Math::Clamp(pow(pixel[j * m_Width + i].Red(), 1 / gamma), 1.f, 0.f) * 255 + 0.5);
				g = (unsigned char)(Math::Clamp(pow(pixel[j * m_Width + i].Green(), 1 / gamma), 1.f, 0.f) * 255 + 0.5);
				b = (unsigned char)(Math::Clamp(pow(pixel[j * m_Width + i].Blue(), 1 / gamma), 1.f, 0.f) * 255 + 0.5);
			}
			else
			{
				r = (unsigned char)(Math::Clamp(pixel[j * m_Width + i].Red(), 1.f, 0.f) * 255 + 0.5);
				g = (unsigned char)(Math::Clamp(pixel[j * m_Width + i].Green(), 1.f, 0.f) * 255 + 0.5);
				b = (unsigned char)(Math::Clamp(pixel[j * m_Width + i].Blue(), 1.f, 0.f) * 255 + 0.5);
			}

            file << r << g << b;
        }
    }

	file.close();
}

Image::~Image(void)
{
}
