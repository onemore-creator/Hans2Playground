#include "Image.hpp"

Hall::Color *Image::GetData() {
  wasDataRequested = true;
  return data.get();
}

void Image::SetData(std::unique_ptr<Hall::Color[]> data) {
  this->data = std::move(data);
  wasDataSet = true;
}
