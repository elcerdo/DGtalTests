#include <string>
//#include <numeric>
//#include <algorithm>
using namespace std;

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/errors.hpp>
namespace po = boost::program_options;

#include <DGtal/base/Common.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/ImageSelector.h>
#include <DGtal/images/ConstImageAdapter.h>
#include <DGtal/geometry/volumes/distance/DistanceTransformation.h>
#include <DGtal/io/readers/GenericReader.h>
#include <DGtal/io/writers/GenericWriter.h>
#include <DGtal/io/viewers/Viewer3D.h>
using namespace DGtal;
using namespace Z3i;

#include <QApplication>

typedef unsigned int ImageValue;

struct Params
{
	string input;
	ImageValue threshold;
};

Params parse_options(int argc, char* argv[])
{
	Params params;
	params.input = "";

	po::options_description options(string(argv[0])+" [options] [input]");
	options.add_options()
		("help,h", "display this message")
		("input,i", po::value<string>(&params.input)->default_value(""), "input file")
		("threshold,t", po::value<ImageValue>(&params.threshold)->default_value(60), "threshold");
	po::positional_options_description positional;
	positional.add("input",1);
	positional.add("threshold",1);

	try
	{
		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(options).positional(positional).run(), vm);
		po::notify(vm);

		if (vm.count("help")) 
		{
			trace.info() << options;
			exit(0);
		}

		if (params.input == "") throw po::required_option("input");

		trace.info() << "input " << params.input << endl;
		trace.info() << "threshold " << params.threshold << endl;
	}
	catch (exception& ex)
	{
		trace.error() << ex.what() << endl;
		trace.info() << options;
		exit(1);
	}

	return params;
}

int main(int argc, char* argv[])
{
	Params params = parse_options(argc, argv);

	typedef ImageSelector<Domain, ImageValue>::Type InputImage;
	InputImage input_image = GenericReader<InputImage>::import(params.input);

	trace.info() << input_image << endl;

	typedef Thresholder<ImageValue, false, false> MyThresholder;
	typedef ConstImageAdapter<InputImage, InputImage::Domain, DefaultFunctor, bool, MyThresholder> ThresholdedImage;
	const ThresholdedImage thresholded_image(input_image, input_image.domain(), DefaultFunctor(), MyThresholder(params.threshold));

	trace.info() << thresholded_image << endl;

	typedef DistanceTransformation<Space, ThresholdedImage, L2Metric> DistanceImage;
	DistanceImage distance_image(thresholded_image.domain(), thresholded_image, L2Metric());

	trace.info() << distance_image << endl;
	//distance_image >> "distance.vol" << endl;

	typedef DigitalSetSelector<Domain, BIG_DS | LOW_VAR_DS | HIGH_ITER_DS | HIGH_BEL_DS>::Type DigitalSet;
	DigitalSet registered_set(thresholded_image.domain());

	ThresholdedImage::Domain::Size total = 0;
	const ThresholdedImage::Domain thresholded_domain = thresholded_image.domain();
	for (ThresholdedImage::Domain::Iterator iter=thresholded_domain.begin(), iter_end=thresholded_domain.end(); iter!=iter_end; iter++)
	{
		const ThresholdedImage::Domain::Point& point = *iter;
		if (!thresholded_image(point)) continue;
		registered_set.insertNew(*iter);
		total++;
	}
	trace.info() << "total " << total << " " << static_cast<int>(100.*total/input_image.size()) << "%" << endl;

	QApplication application(argc,argv);

	typedef Viewer3D<> Viewer;
	Viewer viewer;
	viewer.show();

	viewer << registered_set;
	viewer << Viewer::updateDisplay;

	trace.info() << "byebye" << endl;
	return application.exec();
}

