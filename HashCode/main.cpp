#include "SlideMaker.h"

int main()
{
	SlideMaker sm("datasets/b.txt");
	sm.makeSlideShow("out/B_out.txt");
	return 0;
}