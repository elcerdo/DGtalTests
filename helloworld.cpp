#include <DGtal/base/Common.h>
using std::endl;

int main(int argc,char * argv[])
{
	DGtal::trace.info() << "coucou" << endl;
	DGtal::trace.emphase() << "DGtal version " << DGTAL_VERSION << endl;

	return 0;
}

