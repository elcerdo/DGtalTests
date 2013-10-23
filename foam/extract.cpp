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
#include <DGtal/images/ImageContainerByITKImage.h>
#include <DGtal/images/ConstImageAdapter.h>
#include <DGtal/geometry/volumes/distance/DistanceTransformation.h>
#include <DGtal/io/readers/GenericReader.h>
#include <DGtal/io/writers/GenericWriter.h>
#include <DGtal/io/viewers/Viewer3D.h>
using namespace DGtal;
using namespace Z3i;

#include <itkImageFileWriter.h>

#include <QApplication>

typedef unsigned int ImageValue;
typedef Viewer3D<> Viewer;

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

template <typename Image>
void write_itk_image(const Image& image, const string& filename)
{
	BOOST_CONCEPT_ASSERT(( CConstImage<Image> ));

	typedef experimental::ImageContainerByITKImage<typename Image::Domain, typename Image::Value> MyITKImage;
	MyITKImage itk_image(image.domain());

	std::copy(image.constRange().begin(), image.constRange().end(), itk_image.range().outputIterator());

	typedef itk::ImageFileWriter<typename MyITKImage::ITKImage> MyITKImageWriter;
	typename MyITKImageWriter::Pointer writer = MyITKImageWriter::New();
	writer->SetFileName(filename);
	writer->SetInput(itk_image.getITKImagePointer());
	writer->Update();

	trace.info() << "wrote " << filename << endl;
}

template <typename Image>
int display_image(const Image& image, Viewer& viewer) 
{
	BOOST_CONCEPT_ASSERT(( CConstImage<Image> ));

	typedef typename DigitalSetSelector<typename Image::Domain, BIG_DS | LOW_VAR_DS | HIGH_ITER_DS | HIGH_BEL_DS>::Type DigitalSet;
	const typename Image::Domain domain = image.domain();
	DigitalSet registered_set(domain);

	typename Image::Domain::Size displayed = 0;
	for (typename Image::Domain::Iterator iter=domain.begin(), iter_end=domain.end(); iter!=iter_end; iter++)
	{
		const typename Image::Domain::Point& point = *iter;
		if (!image(point)) continue;
		registered_set.insertNew(*iter);
		displayed++;
	}
	trace.info() << "displayed=" << displayed << " " << static_cast<int>(100.*displayed/domain.size()) << "%" << endl;


	viewer << registered_set;
}

int main(int argc, char* argv[])
{
	QApplication application(argc,argv);
	Viewer viewer;
	viewer.show();

	Params params = parse_options(argc, argv);

	// load input image
	trace.beginBlock("loading");
	trace.info() << "input=" << params.input << endl;
	typedef ImageSelector<Domain, ImageValue>::Type InputImage;
	const InputImage input_image = GenericReader<InputImage>::import(params.input);
	const Domain domain = input_image.domain();
	trace.info() << "domain=" << domain << endl;
	trace.endBlock();

	// threshold input image
	trace.beginBlock("thresholding");
	trace.info() << "threshold=" << params.threshold << endl;
	typedef Thresholder<ImageValue, false, false> InputThresholder;
	typedef ConstImageAdapter<InputImage, InputImage::Domain, DefaultFunctor, bool, InputThresholder> ThresholdedInputImage;
	const ThresholdedInputImage thresholded_input_image(input_image, domain, DefaultFunctor(), InputThresholder(params.threshold));
	display_image(thresholded_input_image, viewer);
	trace.endBlock();

	trace.beginBlock("morphologic closing");
	// erode image
	typedef DistanceTransformation<Space, ThresholdedInputImage, L2Metric> DistanceErodeImage;
	const DistanceErodeImage distance_erode_image(domain, thresholded_input_image, L2Metric());
	write_itk_image(distance_erode_image, "distance_erode.mha");
	trace.endBlock();

	viewer << Viewer::updateDisplay;
	return application.exec();
}


