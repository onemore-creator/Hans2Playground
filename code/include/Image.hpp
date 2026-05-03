#pragma once
#include <Hall/Hall.h>
#include <memory>
namespace Halib::Data
{
	/// @brief A datatype that holds an R5G5B5A1 image
	struct Image
	{
		short width; //Image width in pixels
		short height; //Image height in pixels

		/// @brief 
		/// @return A raw pointer to the underlying raw image data.
		Hall::Color* GetData();

		/// @brief Replaces the data of the image. In case the new data has a different size, "width" and "height" also need to be adapted manually
		void SetData(std::unique_ptr<Hall::Color[]> data);

		bool wasDataRequested = false; //TODO make this private by using a friend class to update the data
		bool wasDataSet = false;   //TODO make this private by using a friend class to update the data
	private:
		std::unique_ptr<Hall::Color[]> data;
	};
} // namespace Halib::Data
