#ifndef PHOTO_H
#define PHOTO_H
#include <vector>
class Photo
{
public:
	Photo() {};
	Photo(char o,int nTags, size_t id): _tags(0), _orient(o), id(id)
	{
		_tags.reserve(nTags); 
	};
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
	char getOrient() { return _orient; };
	size_t getID() { return id; };
private:
	std::vector<std::string> _tags;
	char _orient;
	size_t id;
};
#endif
