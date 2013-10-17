#include <string>
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
using namespace DGtal;
using namespace Z3i;

int main(int argc,char * argv[])
{
	struct InputParam
	{
		string filename;
		double threshold;
	};

	InputParam params;
	po::options_description options(string(argv[0])+" [options] [input]");
	options.add_options()
		("help,h", "display this message")
		("input,i", po::value<string>(&params.filename)->default_value(""), "input file")
		("threshold,t", po::value<double>(&params.threshold)->default_value(0.), "threshold");
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
			cout << options;
			return 0;
		}

		if (!file_exists(params.filename)) throw runtime_error("input file does not exists");
	}
	catch (exception& ex)
	{
		cerr << ex.what() << endl;
		cerr << options;
		return 1;
	}

	trace.info() << "filename " << params.filename << endl;
	trace.info() << "threshold " << params.threshold << endl;

	return 0;
}

