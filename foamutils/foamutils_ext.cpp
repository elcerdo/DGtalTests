#include <boost/python.hpp>
using namespace boost::python;

#include <DGtal/base/Common.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/ImageSelector.h>
#include <DGtal/io/readers/GenericReader.h>
#include <DGtal/io/writers/GenericWriter.h>
using namespace DGtal;
using namespace Z3i;

using std::endl;

tuple image_import(const std::string filename)
{
	trace.emphase() << filename << endl;

	typedef ImageSelector<Domain, unsigned char>::Type Image;
	const Image image = GenericReader<Image>::import(filename);
	trace.info() << image << endl;

	const Point lower_bound = image.domain().lowerBound();
	const Point upper_bound = image.domain().upperBound();
	const Point delta = upper_bound-lower_bound+Point(1,1,1);
	trace.info() << lower_bound << " " << upper_bound << endl;

	const Image::ConstRange range = image.constRange();
	list flat;
	for (Image::ConstRange::ConstIterator iter=range.begin(), iter_end=range.end(); iter!=iter_end; iter++)
		flat.append(*iter);

	tuple payload = make_tuple(
			make_tuple(delta[2], delta[1], delta[0]),
			flat
			);

	return payload;
}

void image_export(tuple shape, list flat, const std::string filename)
{
	trace.emphase() << filename << endl;

	const Domain::Size sx = extract<Domain::Size>(shape[2]);
	const Domain::Size sy = extract<Domain::Size>(shape[1]);
	const Domain::Size sz = extract<Domain::Size>(shape[0]);
	const Domain domain(Point(0,0), Point(sx-1, sy-1, sz-1));
	trace.info() << domain << endl;

	typedef ImageSelector<Domain, unsigned char>::Type Image;
	Image image(domain);

	Image::Range range = image.range();
	size_t kk = 0;
	for (Image::Range::Iterator iter=range.begin(), iter_end=range.end(); iter!=iter_end; iter++)
	{
		Image::Value value = extract<Image::Value>(flat[kk]);
		*iter = value;
		kk++;
	}

	image >> filename;
}

BOOST_PYTHON_MODULE(foamutils_ext)
{
	def("image_import", image_import);
	def("image_export", image_export);
}

