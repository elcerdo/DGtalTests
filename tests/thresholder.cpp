#include <string>
#include <numeric>
#include <sys/stat.h>
using namespace std;

bool file_exists(const string& filename)
{
	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}

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
using namespace DGtal;
using namespace Z3i;

template <typename V>
struct MyThresholder : unary_function<V,bool>
{
	public:
		MyThresholder(const V& threshold) : threshold(threshold) {}
		bool operator()(const V& value) const { return value>threshold; }
	private:
		V threshold;
};

int main(int argc,char * argv[])
{
	struct InputParam
	{
		string input;
		string output;
		double threshold;
	};

	InputParam params;
	po::options_description options(string(argv[0])+" [options] [input]");
	options.add_options()
		("help,h", "display this message")
		("input,i", po::value<string>(&params.input)->default_value(""), "input file")
		("output,o", po::value<string>(&params.output)->default_value("output.vol"), "output file")
		("threshold,t", po::value<double>(&params.threshold)->default_value(0.), "threshold");
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

		if (!file_exists(params.input)) throw runtime_error("input file does not exists");

		trace.info() << "input " << params.input << endl;
		trace.info() << "output " << params.output << endl;
		trace.info() << "threshold " << params.threshold << endl;

		typedef ImageSelector<Domain, double>::Type InputImage;
		InputImage image = GenericReader<InputImage>::import(params.input);

		trace.info() << image << endl;

		typedef ImageSelector<Domain, unsigned char>::Type OutputImage;
		typedef Composer<MyThresholder<InputImage::Value>, CastFunctor<OutputImage::Value>, OutputImage::Value> MyActualThresholder;
		typedef ConstImageAdapter<InputImage, OutputImage::Domain, DefaultFunctor, OutputImage::Value, MyActualThresholder> ThresholdedImage;
		DefaultFunctor id;
		MyActualThresholder	thresholder(MyThresholder<InputImage::Value>(params.threshold), CastFunctor<OutputImage::Value>());
		ThresholdedImage thresholded_image(image, image.domain(), id, thresholder);

		trace.info() << thresholded_image << endl;

		thresholded_image >> params.output;

		unsigned int total = accumulate(thresholded_image.constRange().begin(), thresholded_image.constRange().end(), 0);
		trace.info() << "total " << total << endl;
	}
	catch (exception& ex)
	{
		trace.error() << ex.what() << endl;
		trace.info() << options;
		return 1;
	}

	return 0;
}

