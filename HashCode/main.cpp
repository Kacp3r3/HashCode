#include "SlideMaker.h"

int main()
{
	SlideMaker sm("datasets/e.txt");
	sm.makeSlideShow("out/E_out.txt");
	return 0;
}