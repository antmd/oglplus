/**
 *  @file oglplus/images/sphere_bmap.hpp
 *  @brief Generator of a normal/depth map with "imprinted" sphere
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMAGES_SPHERE_BMAP_1107121519_HPP
#define OGLPLUS_IMAGES_SPHERE_BMAP_1107121519_HPP

#include <oglplus/images/image.hpp>

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/vector.hpp>
#include <cassert>
#include <cmath>
#endif

namespace oglplus {
namespace images {

class SphereBumpMap
 : public Image
{
public:
	SphereBumpMap(
		GLsizei width,
		GLsizei height,
		GLsizei xrep = 1,
		GLsizei yrep = 1
	);
};

// Implementation
#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)

OGLPLUS_LIB_FUNC
SphereBumpMap::SphereBumpMap(
	GLsizei width,
	GLsizei height,
	GLsizei xrep,
	GLsizei yrep
): Image(
	width,
	height,
	1,
	4,
	(GLfloat*)0,
	PixelDataFormat::RGBA,
	PixelDataInternalFormat::RGBA16F
)
{
	assert(width != 0 && height != 0);
	assert(xrep != 0 && yrep != 0);

	typedef double number;
	number one = number(1);
	number invw = (2.0f*xrep)/width;
	number invh = (2.0f*yrep)/height;
	GLsizei hi = number(width)/xrep;
	GLsizei hj = number(height)/yrep;

	auto p = this->_begin<GLfloat>();
	for(GLsizei j=0; j!=height; ++j)
	{
		number y = number((j % hj) - hj/2)*invh;
		for(GLsizei i=0; i!=width; ++i)
		{
			number x = number((i % hi) - hi/2)*invw;
			number l = std::sqrt(x*x + y*y);
			number d = sqrt(one-l*l);
			Vector<number, 3> z(0.0, 0.0, one);
			Vector<number, 3> n(-x, -y, d);
			Vector<number, 3> v = (l >= one)?
				z:
				Normalized(z+n);
			if(l >= one) d = 0;
			assert(p != this->_end<GLfloat>());
			*p = v.x(); ++p;
			*p = v.y(); ++p;
			*p = v.z(); ++p;
			*p = d; ++p;
		}
	}
	assert(p == this->_end<GLfloat>());
}

#endif // OGLPLUS_LINK_LIBRARY

} // images
} // oglplus

#endif // include guard
