#pragma once
#include <Hall/Hall.h>
#include <memory>
#include "Vec2.hpp"

namespace Halib::Data
{
	struct Image;
	struct Sprite;
}


namespace Halib::System
{
	void Render(const std::shared_ptr<Data::Image> image, short x, short y, short xScale, short yScale);
	void Render(const std::shared_ptr<Data::Sprite> sprite, short x, short y);
}

namespace Halib::Data
{
	/// @brief A datatype that holds an R5G5B5A1 image
	struct Image
	{
		friend void Halib::System::Render(const std::shared_ptr<Data::Image> image, short x, short y, short xScale, short yScale);
		friend void Halib::System::Render(const std::shared_ptr<Data::Sprite> sprite, short x, short y);

		Vec2 size;
		
		/// @brief 
		/// @return A raw pointer to the underlying raw image data.
		Hall::Color* GetData();
		
		/// @brief Replaces the data of the image. In case the new data has a different size, "width" and "height" also need to be adapted manually
		void SetData(std::unique_ptr<Hall::Color[]> data);
		
	private:
		std::unique_ptr<Hall::Color[]> data;
		bool wasDataRequested = false;
		bool wasDataSet = false;
	};
} // namespace Halib::Data
