#ifndef PHOTO_H
#define PHOTO_H
#include <vector>
class Photo
{
public:
	Photo() {};
	Photo(char o, int nTags) : _tags(0), _orient(o), isUsed(false)
	{
		_tags.reserve(nTags);
	};
	~Photo() {

	}
	void addTag(std::string& x) { _tags.push_back(x); };
	void setOrientation(char x) { _orient = x; };
	void setUsed() { isUsed = true; }
	std::vector<std::string> getTags() const { return _tags; }
	bool operator > (const Photo& src)
	{
		return _orient > src._orient;
	}
	bool operator < (const Photo& src)
	{
		return _orient < src._orient;
	}
	char getOrient() { return _orient; };

private:
	std::vector<std::string> _tags;
	char _orient;
	bool isUsed; 
};
#endif

