#ifndef SLIDER_H
#define SLIDER_H
#include "Photo.h"
#include <string>
#include <fstream>
#include <algorithm>
class SlideMaker
{
public:
	SlideMaker() {};
	SlideMaker(std::string file)
	{
		std::fstream _plik;
		_plik.open(file, std::ios::in);

		size_t nPhotos;
		_plik >> nPhotos;
		_photoH.reserve(nPhotos);
		_photoV.reserve(nPhotos);
		size_t nV = 0;
		size_t nH = 0;
		for(size_t i=0;i<nPhotos;++i)
		{
			char orient;
			size_t nTags;
			_plik >> orient;
			_plik >> nTags;
			if (orient == 'H')
			{
				_photoH.emplace_back(orient, nTags, i);
				for (size_t j = 0; j < nTags; ++j)
				{
					std::string tag;
					_plik >> tag;
					_photoH[nH].addTag(tag);
				}
				//_photoH[nH].sortTags();
				nH++;
			}
			else
			{
				_photoV.emplace_back(orient, nTags, i);
				for (size_t j = 0; j < nTags; ++j)
				{
					std::string tag;
					_plik >> tag;
					_photoV[nV].addTag(tag);
				}
				//_photoV[nV].sortTags();
				nV++;
			}
			
			
			
		}
	}
	void makeSlideShow(std::string x)
	{
		std::fstream _plik;
		_plik.open(x, std::ios::out);
		size_t V = countVertical();
		size_t H = countHorizontal();
		size_t nSlides = H + V / 2;
		size_t Vcurrent = 0;
		size_t Hcurrent = 0;
		_plik << nSlides << '\n';

		for (size_t i = 0; i < nSlides; ++i)
		{
			if (H > 0)
			{
				//Horizontal - Vertical
				if (V/2 > 0)
				{
					size_t lewo = 0;
					size_t prawo = 0;
					size_t srodek = 0;
					size_t max = 0;
					size_t maxindexFirst = 0;
					size_t maxindexSecond = 0;
					for (size_t j = 0; j < V; j++)
					{
						for (size_t z = j; z < V; z++)
						{
							if (z != j)
							{
								Photo tmp(_photoV[j], _photoV[z]);
								lewo = checkDifferent(_photoH[Hcurrent], tmp);
								prawo = checkDifferent(tmp, _photoH[Hcurrent]);
								srodek = getEquals(_photoH[Hcurrent].getVector(), tmp.getVector());
								size_t localmax = minnn(lewo, prawo, srodek);
								if (localmax > max)
								{
									max = localmax;
									maxindexFirst = j;
									maxindexSecond = z;
								}
							}
						}
					}
					//Posprzatac trzeba
					_plik << _photoH[Hcurrent].getID() << "\n";
					_photoH[Hcurrent] = _photoH[_photoH.size() - 1];
					_photoH.pop_back();
					H--;
					i++;
					_plik << _photoV[maxindexFirst].getID() << " " << _photoV[maxindexSecond].getID()<<'\n';
					_photoV[maxindexFirst] = _photoV[_photoV.size() - 1];
					_photoV.pop_back();
					_photoV[maxindexSecond] = _photoV[_photoV.size() - 1];
					_photoV.pop_back();
					V--;
					V--;
					Hcurrent++;
					//Chyba o niczym nie zapomnialem XD
				}
				// Horizontal - Horizontal
				else
				{
					size_t lewo = 0;
					size_t prawo = 0;
					size_t srodek = 0;
					size_t max = 0;
					size_t maxindex = 0;
					for (size_t j = 0; j < H; j++)
					{
						if (j != Hcurrent)
						{
							lewo = checkDifferent(_photoH[Hcurrent], _photoH[j]);
							prawo = checkDifferent(_photoH[j], _photoH[Hcurrent]);
							srodek = getEquals(_photoH[Hcurrent].getVector(), _photoH[j].getVector());
							size_t localmax = minnn(lewo, prawo, srodek);
							if (localmax > max)
							{
								max = localmax;
								maxindex = j;
							}
						}
					}
					_plik << _photoH[Hcurrent].getID() << "\n";
					_photoH[Hcurrent] = _photoH[_photoH.size() - 1];
					_photoH.pop_back();
					H--;
					i++;
					if (H > 1)
					{
						_plik << _photoH[maxindex].getID() << "\n";
						_photoH[Hcurrent] = _photoH[_photoH.size() - 1];
						_photoH.pop_back();
						H--;
					}
				}
			}
			//H<0 V>0
			else
			{
				size_t lewo = 0;
				size_t prawo = 0;
				size_t srodek = 0;
				size_t max = 0;
				size_t maxindexFirst = 0;
				size_t maxindexSecond = 0;
				Photo tmp1(_photoV[Vcurrent], _photoV[Vcurrent + 1]);
				for (size_t j = 0; j < V; j++)
				{
					if (j != Vcurrent)
					{
						for (size_t z = j; z < V; z++)
						{
							if (z != j)
							{
								Photo tmp2(_photoV[j], _photoV[z]);
								lewo = checkDifferent(tmp1, tmp2);
								prawo = checkDifferent(tmp2, tmp1);
								srodek = getEquals(tmp1.getVector(), tmp2.getVector());
								size_t localmax = minnn(lewo, prawo, srodek);
								if (localmax > max)
								{
									max = localmax;
									maxindexFirst = j;
									maxindexSecond = z;
								}
							}
						}
					}
				}
				//Posprzatac trzeba
				_plik << _photoV[Vcurrent].getID() <<' ' << _photoV[Vcurrent+1].getID() << "\n";
				_photoV[Vcurrent] = _photoV[_photoV.size() - 1];
				_photoV.pop_back();
				_photoV[Vcurrent+1] = _photoV[_photoV.size() - 1];
				_photoV.pop_back();
				V--;
				V--;
				i++;
				_plik << _photoV[maxindexFirst].getID() << " " << _photoV[maxindexSecond].getID() << '\n';
				_photoV[maxindexFirst] = _photoV[_photoV.size() - 1];
				_photoV.pop_back();
				_photoV[maxindexSecond] = _photoV[_photoV.size() - 1];
				_photoV.pop_back();
				V--;
				V--;
				Vcurrent+=2;
			}
		}
	}

	size_t countVertical() 
	{
		size_t count=0;
		for (size_t i = 0; i < _photoV.size(); i++)
		{
			if (_photoV[i].getOrient() == 'V')count++;
		}
		return count;
	};
	size_t countHorizontal() 
	{
		size_t count = 0;
		for (size_t i = 0; i < _photoH.size(); i++)
		{
			if (_photoH[i].getOrient() == 'H')count++;
		}
		return count;
	};

	int checkDifferent(const Photo& left, const Photo& right) const
	{
		int different = 0;
		bool found = false;
		for (int i = 0; i < left.getSize(); i++)
		{
			found = false;
			for (int j = 0; j < right.getSize(); j++)
			{
				if (left.getTag(i) == right.getTag(j))
				{
					found = true;
				}

			}
			if (found != true)
				different++;
		}

		return different;
	}
	int getEquals(std::vector<std::string>& firstPhoto, std::vector<std::string>& secondPhoto) {

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

		return temporary.size();
	}

	size_t minnn(size_t a, size_t b, size_t c)
	{
		size_t min = a;
		if (b < min) min = b;
		if (c < min) min = c;

		return min;
	}
	~SlideMaker();
private:
	std::vector<Photo> _photoV;
	std::vector<Photo> _photoH;
};
#endif
