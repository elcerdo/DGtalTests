#include <itkImageRegion.h>
using namespace std;

int main(int argc,char * argv[])
{
	typedef itk::ImageRegion<3> ImageRegion;

	ImageRegion::IndexType index;
	index[0] = 1;
	index[1] = 2;
	index[2] = 3;
	cout << index << endl;

	ImageRegion::SizeType size;
	size[0] = 10;
	size[1] = 9;
	size[2] = 8;
	cout << size << endl;

	ImageRegion region(index, size);
	cout << region << endl;
}


