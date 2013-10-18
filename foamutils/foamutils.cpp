
const char* hello_world()
{
	return "coucou";
}

#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(libfoamutils)
{
	def("hello_world", hello_world);
}

