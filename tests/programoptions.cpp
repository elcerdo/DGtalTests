#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
namespace po = boost::program_options;

int main(int argc,char * argv[])
{
	std::string input_string = "coucou";
	int threshold_int = 0;
	double param_double = 3.1415;

	po::options_description options("Allowed options");
	options.add_options()
		("help,h", "display this message")
		("input,i", po::value<std::string>(&input_string), "input string")
		("threshold,t", po::value<int>(&threshold_int)->default_value(42), "integer option")
		("param,p", po::value<double>(&param_double), "real option");

	try
	{
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, options), vm);
		po::notify(vm);
		if (vm.count("help")) 
		{
			std::cout << options;
			return 0;
		}

	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << options;
		return 1;
	}

	std::cout << "input_string " << input_string << std::endl;
	std::cout << "threshold_int " << threshold_int << std::endl;
	std::cout << "param_double " << param_double << std::endl;
	return 0;
}

