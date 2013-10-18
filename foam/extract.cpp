#include <string>
//#include <numeric>
//#include <algorithm>
using namespace std;

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
namespace po = boost::program_options;

#include <DGtal/base/Common.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/ImageSelector.h>
#include <DGtal/images/ConstImageAdapter.h>
#include <DGtal/io/readers/GenericReader.h>
#include <DGtal/io/writers/GenericWriter.h>
#include <DGtal/io/viewers/Viewer3D.h>
using namespace DGtal;
using namespace Z3i;

#include <QApplication>

int main(int argc,char * argv[])
{
	typedef unsigned int Value;

	struct InputParam
	{
		string input;
		string output;
		Value threshold;
	};

	InputParam params;
	po::options_description options(string(argv[0])+" [options] [input]");
	options.add_options()
		("help,h", "display this message")
		("input,i", po::value<string>(&params.input)->default_value(""), "input file")
		("threshold,t", po::value<Value>(&params.threshold)->default_value(60), "threshold");
	po::positional_options_description positional;
	positional.add("input",1);
	positional.add("output",1);
	positional.add("threshold",1);

	try
	{
		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(options).positional(positional).run(), vm);
		po::notify(vm);

		if (vm.count("help")) 
		{
			trace.info() << options;
			return 0;
		}

		trace.info() << "input " << params.input << endl;
		trace.info() << "threshold " << params.threshold << endl;

		typedef ImageSelector<Domain, Value>::Type InputImage;
		InputImage input_image = GenericReader<InputImage>::import(params.input);

		trace.info() << input_image << endl;

		typedef Thresholder<InputImage::Value, false, false> MyThresholder;
		typedef ConstImageAdapter<InputImage, InputImage::Domain, DefaultFunctor, bool, MyThresholder> ThresholdedImage;
		const ThresholdedImage thresholded_image(input_image, input_image.domain(), DefaultFunctor(), MyThresholder(params.threshold));
		const ThresholdedImage::Domain thresholded_domain = thresholded_image.domain();

		trace.info() << thresholded_image << endl;

		typedef DigitalSetSelector<Domain, BIG_DS | LOW_VAR_DS | HIGH_ITER_DS | HIGH_BEL_DS>::Type DigitalSet;
		DigitalSet registered(input_image.domain());

		ThresholdedImage::Domain::Size total = 0;
		for (ThresholdedImage::Domain::Iterator iter=thresholded_domain.begin(), iter_end=thresholded_domain.end(); iter!=iter_end; iter++)
		{
			const ThresholdedImage::Domain::Point& point = *iter;
			if (!thresholded_image(point)) continue;
			registered.insertNew(*iter);
			total++;
		}

		//copy_if(input_image.begin(), input_image.end(), registered.begin(), MyThresholder(params.threshold)); //C++11

		trace.info() << "total " << total << " " << static_cast<int>(100.*total/input_image.size()) << "%" << endl;

		QApplication application(argc,argv);

		typedef Viewer3D<> Viewer;
		Viewer viewer;
		viewer.show();

		viewer << registered;
		viewer << Viewer::updateDisplay;

		trace.info() << "byebye" << endl;
		return application.exec();
	}
	catch (exception& ex)
	{
		trace.error() << ex.what() << endl;
		trace.info() << options;
		return 1;
	}

	return 0;
}

