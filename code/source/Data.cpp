#include "Data.hpp"
#include "bmpread.h"
#include <iostream>

namespace Halib::Data
{
	std::unique_ptr<Image> LoadImage(const char* path)
	{
		bmpread_t bmp;
		int result = bmpread(path, BMPREAD_TOP_DOWN | BMPREAD_ANY_SIZE | BMPREAD_ALPHA, &bmp);
		if(!result)
		{
			std::cerr << "COULD NOT LOAD ASSET " << path << std::endl;
		}
		std::unique_ptr<Hall::Color[]> data = std::make_unique<Hall::Color[]>(bmp.width * bmp.height);
		
		//This is stupid, but changing bmpread to directly output R5G5B5A1 did not seem so straight forward
		for(int i = 0; i < bmp.width * bmp.height; i++)
		{
			unsigned char red   = bmp.data[4 * i + 0];
			unsigned char green = bmp.data[4 * i + 1];
			unsigned char blue  = bmp.data[4 * i + 2];
			unsigned char alpha = bmp.data[4 * i + 3];
			
			red = red >> 3;
			green = green >> 3;
			blue = blue >> 3;
			
			Hall::Color color = CreateColor(red, green, blue, alpha >= 192);
			data[i] = color;
		}
		
		std::unique_ptr<Image> image = std::make_unique<Image>();
		image->SetData(std::move(data));
		image->width = bmp.width;
		image->height = bmp.height;
		bmpread_free(&bmp);

		return image;
	}

	Hall::Color CreateColor(char red, char green, char blue, bool alpha)
	{
		Hall::Color color = 0;
		color = SetRed(color, red);
		color = SetGreen(color, green);
		color = SetBlue(color, blue);
		color = SetAlpha(color, alpha);
		return color;
	}

	Hall::Color SetRed(Hall::Color color, char red)
	{
		return (color & 0b0000011111111111) | (((unsigned short)red & 0b11111) << 11);
	}

	Hall::Color SetGreen(Hall::Color color, char green)
	{
		return (color & 0b1111100000111111) | (((unsigned short)green & 0b11111) << 6);
	}

	Hall::Color SetBlue(Hall::Color color, char blue)
	{
		return (color & 0b1111111111000001) | (((unsigned short)blue & 0b11111) << 1);
	}

	Hall::Color SetAlpha(Hall::Color color, bool alpha)
	{
		unsigned short alphaVal = alpha ? 1 : 0;
		return (color & 0b1111111111111110) | alphaVal;
	}

	char GetRed(Hall::Color color)
	{
		return (color >> 11) & 0b11111;
	}

	char GetGreen(Hall::Color color)
	{
		return (color >> 6) & 0b11111;
	}

	char GetBlue(Hall::Color color)
	{
		return (color >> 1) & 0b11111;
	}

	bool GetAlpha(Hall::Color color)
	{
		return color & 0b1;
	}

} // namespace Halib::Data
