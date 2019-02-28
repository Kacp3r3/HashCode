#ifndef SLIDER_H
#define SLIDER_H
#include "Photo.h"
#include <string>
#include <fstream>
#include <algorithm>

std::vector<std::string> getEquals(std::vector<std::string>&& firstPhoto, std::vector<std::string>&& secondPhoto) {
	
	std::vector<std::string> temporary;

	if (firstPhoto.size() > secondPhoto.size()) {

		for (int i = 0; i < firstPhoto.size(); i++) {
			for (int j = 0; j < secondPhoto.size(); j++) {

				if (secondPhoto[j] == firstPhoto[i]) {
					temporary.emplace_back(firstPhoto[i]);
				}
			}
		}
	}
	else {

		for (int i = 0; i < secondPhoto.size(); i++) {
			for (int j = 0; j < firstPhoto.size(); j++) {

				if (firstPhoto[j] == secondPhoto[i]) {
					temporary.emplace_back(secondPhoto[i]);
				}
			}
		}
	}

	return temporary;
}

class SlideMaker
{
public:
	SlideMaker() : _photo(0) {};
	SlideMaker(std::string file)
	{
		std::fstream _plik;
		_plik.open(file, std::ios::in);

		size_t nPhotos;
		_plik >> nPhotos;
		_photo.reserve(nPhotos);
		for (size_t i = 0; i < nPhotos; ++i)
		{
			char orient;
			size_t nTags;
			_plik >> orient;
			_plik >> nTags;
			_photo.emplace_back(orient, nTags);
			for (size_t j = 0; j < nTags; ++j)
			{
				std::string tag;
				_plik >> tag;
				_photo[i].addTag(tag);
			}
		}
	}

	void makeSlideShow(std::string x)
	{
		std::fstream _plik;
		_plik.open(x, std::ios::out);
		std::sort(_photo.begin(), _photo.end());
		size_t V = countVertical();
		size_t H = countHorizontal();
		
		size_t nSlides = H + V / 2;
		size_t Vcount = 0;
		_plik << nSlides << '\n';
		for (size_t i = 0; i < _photo.size(); ++i)
		{
			if (_photo[i].getOrient() == 'H')
			{
				_plik << i << '\n';
				getEquals(_photo[i].getTags(), _photo[i + 1].getTags());
			}
			else
			{
				Vcount++;
				if (Vcount > V) break;
				_plik << i << ' ' << i + 1 << '\n';
				i++;
			}
		}


	}

	

	size_t countVertical()
	{
		size_t count = 0;
		for (size_t i = 0; i < _photo.size(); i++)
		{
			if (_photo[i].getOrient() == 'V')count++;
		}
		return count;
	};

	size_t countHorizontal()
	{
		size_t count = 0;
		for (size_t i = 0; i < _photo.size(); i++)
		{
			if (_photo[i].getOrient() == 'H')count++;
		}
		return count;
	};


	~SlideMaker() {

	}

private:
	std::vector<Photo> _photo;
};
#endif