#include <list>
#include <DGtal/base/Common.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/Color.h>
#include <DGtal/io/boards/Board2D.h>

using namespace std;

using namespace DGtal;
using namespace Z2i;

int main(int argc,char * argv[])
{
	trace.emphase() << "DGtal version " << DGTAL_VERSION << endl;

	typedef Board2D Board;
	Board board;

	const Domain domain(Point(-1,-1),Point(4,4));
	const Point origin(0,0);

	board << domain;
	trace.info() << "coucou " << origin.className() << endl;

	board << CustomStyle(origin.className(), new CustomFillColor(Color::Red));
	for (Domain::ConstIterator iter=domain.begin(), iter_end=domain.end(); iter!=iter_end; iter++)
	{
		const Point& point = *iter;
		if ((point-origin).norm()>4) continue;
		board << point;
	}

	typedef list<Point> Points;
	Points points;
	points.push_back(Point(0,1));
	points.push_back(Point(0,0));
	points.push_back(Point(3,0));

	board << CustomStyle(origin.className(), new CustomFillColor(Color::Yellow));
	for (Points::const_iterator iter=points.begin(), iter_end=points.end(); iter!=iter_end; iter++)
	{
		const Point& point = *iter;
		trace.info() << point << endl;
		board << point;
	}

	trace.emphase() << "byebye" << endl;
	board.saveSVG("coucou.svg");
	board.saveCairo("coucou.pdf", Board::CairoPDF);


	return 0;
}

