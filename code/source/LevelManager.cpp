#include "LevelManager.hpp"
#include "Data.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace Halib
{
	/// @brief Splits the given string by the given delimiter. The delimiter will not be contained in any of the resulting substrings
	/// @param str 
	/// @param delimiter 
	/// @return 
	static std::vector<std::string> Split(const std::string& str, const std::string& delimiter)
	{
		std::vector<std::string> result{};
		result.reserve(10);

		int lastIndex = 0;
		int index = str.find_first_of(delimiter, lastIndex);
		while(index != std::string::npos)
		{
			std::string substr = str.substr(lastIndex, index - lastIndex);
			if(substr.size() > 0)
				result.push_back(substr);

			lastIndex = index + delimiter.length();
			index = str.find_first_of(delimiter, lastIndex);
		}

		return result;
	}

	static std::string Trim(const std::string& str)
	{
		std::string result = str;
		//Trim front
		result.erase(result.begin(), std::find_if(result.begin(), result.end(), 
		[](unsigned char ch) { return !std::isspace(ch); }
		));

		//Trim back
		result.erase(std::find_if(result.rbegin(), result.rend(), 
		[](unsigned char ch) { return !std::isspace(ch); }
		).base(), result.end());

		return result;
	}

	void LevelManager::Init()
	{
		std::ifstream bgFile(backgroundPath);
		std::string str;
		std::getline(bgFile, str);
		std::vector<std::string> line = Split(str, ";");
		std::string tilesetPath = line[0];

		auto bgimage = LoadImage(std::string(tilesetPath));
		tilesetPath.replace(tilesetPath.find(".bmp"), std::string::npos, "75.bmp");
		auto bgimage75 = LoadImage(std::string(tilesetPath));
		Vec2 frameCount = Vec2(std::stoi(line[1]), std::stoi(line[2]));

		bgData.tileset = std::make_shared<Sprite>(bgimage, bgimage75, frameCount);
		
		
		while(std::getline(bgFile, str))
		{
			line = Split(str, ";");
			std::vector<int> column{};
			for(std::string tile : line)
				column.push_back(std::stoi(tile));

			bgData.tilemap.push_back(column);
		}
	}

	void LevelManager::Render()
	{
		Vec2 tileSize = bgData.tileset->GetScaledFrameSize();
		Vec2 position{ 0, static_cast<short>(Hall::SCREEN_HEIGHT - tileSize.y) };

		for(const auto& column : bgData.tilemap)
		{
			for(int tile : column)
			{
				int frameCountX = bgData.tileset->GetFrameCount().x;
				Vec2 frame = Vec2(tile % frameCountX, tile % frameCountX);
				bgData.tileset->SetActiveFrame(frame);
				::Render(bgData.tileset, position.x, position.y);
				position.y -= tileSize.y;
			}
			
			position.x += tileSize.x;
			position.y = static_cast<short>(Hall::SCREEN_HEIGHT - tileSize.y);
			if(position.x + tileSize.x > Hall::SCREEN_WIDTH) break;
		}
	}
} // namespace Halib
