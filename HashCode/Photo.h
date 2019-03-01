#ifndef PHOTO_H
#define PHOTO_H
#include <vector>
#include <algorithm>
class Photo
{
public:
	Photo() {};
	Photo(char o,int nTags, size_t id): _tags(0), _orient(o), id(id)
	{
		_tags.reserve(nTags); 
	};
	Photo(const Photo& firstPhoto, const Photo& secondPhoto) {

		std::vector<std::string> temporary;

		if (firstPhoto.getSize() > secondPhoto.getSize()) {

			for (int i = 0; i < firstPhoto.getSize(); i++) {
				for (int j = 0; j < secondPhoto.getSize(); j++) {


					temporary.emplace_back(firstPhoto.getTag(i));

				}
			}
		}
		else {

			for (int i = 0; i < secondPhoto.getSize(); i++) {
				for (int j = 0; j < firstPhoto.getSize(); j++) {


					temporary.emplace_back(secondPhoto.getTag(i));

				}
			}
		}

		std::sort(temporary.begin(), temporary.end());
		temporary.erase(std::unique(temporary.begin(), temporary.end()), temporary.end());
	}


	~Photo();
	void addTag(std::string& x) { _tags.push_back(x); };
	void setOrientation(char x) { _orient = x; };
	bool operator > (const Photo& src)
	{
		return _orient > src._orient;
	}
	bool operator < (const Photo& src)
	{
		return _orient < src._orient;
	}
	char getOrient()const { return _orient; };
	size_t getID() const { return id; };
	//void sortTags()const { std::sort(_tags.begin(), _tags.end()); };
	size_t checkWspolne(const Photo& x)const
	{
		size_t a = _tags.size();
		size_t b = x._tags.size();
		size_t min = std::min(a,b);
		size_t max = std::max(a,b);
		size_t count = 0;
		if (a > b)
		{
			for (size_t i = 0; i < min; i++)
			{
				for (size_t j = 0; j < max; ++j)
				{
					if (x._tags[i] == _tags[j])count++;
				}
			}
		}
		else
		{
			for (size_t i = 0; i < min; i++)
			{
				for (size_t j = 0; j < max; ++j)
				{
					if (_tags[i] == x._tags[j])count++;
				}
			}
		}
	};
	size_t checkAloneLeft(const Photo& x)
	{
		
	};
	size_t checkAloneRight(const Photo& x) {};
	int getSize() const { return _tags.size(); };
	std::string getTag(int i)const { return _tags[i]; };
	std::vector<std::string>& getVector() { return _tags; }
	
private:
	std::vector<std::string> _tags;
	char _orient;
	size_t id;
};
#endif
