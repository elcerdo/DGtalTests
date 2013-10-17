#include <list>
#include <QApplication>
#include <DGtal/base/Common.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/viewers/Viewer3D.h>

using namespace std;

using namespace DGtal;
using namespace Z3i;

int main(int argc,char * argv[])
{
	QApplication application(argc,argv);

	trace.info() << "coucou" << endl;
	trace.emphase() << "DGtal version " << DGTAL_VERSION << endl;

	typedef list<Point> Points;
	Points points;
	points.push_back(Point(0,1,0));
	points.push_back(Point(0,0,2));
	points.push_back(Point(3,0,0));

	typedef Viewer3D<> Viewer;
	Viewer viewer;
	viewer.show();

	for (Points::const_iterator iter=points.begin(), iter_end=points.end(); iter!=iter_end; iter++)
	{
		const Point& point = *iter;
		trace.info() << point << endl;
		viewer << point;
	}
	viewer << Viewer::updateDisplay;

	trace.info() << "byebye" << endl;
	return application.exec();
}

