/**
 *  .file oglplus/auxiliary/vector_extr.ipp
 *  .brief Implemenation of the subvector extractors for Vector
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

private:
	enum class _spatial_dims : size_t {_x = 0, _y = 1, _z = 2, __ = 3};
public:

#define OGLPLUS_IMPL_VEC_EXTR_3(A,B,C) \
	Vector<T, 3> A ## B ## C (T v = T(0)) const \
	{ \
		return Extract< \
			_spatial_dims::_ ## A, \
			_spatial_dims::_ ## B, \
			_spatial_dims::_ ## C  \
		>(*this, v); \
	}
	OGLPLUS_IMPL_VEC_EXTR_3(x,x,x);
	OGLPLUS_IMPL_VEC_EXTR_3(x,x,y);
	OGLPLUS_IMPL_VEC_EXTR_3(x,x,z);
	OGLPLUS_IMPL_VEC_EXTR_3(x,x,_);
	OGLPLUS_IMPL_VEC_EXTR_3(x,y,x);
	OGLPLUS_IMPL_VEC_EXTR_3(x,y,y);
	OGLPLUS_IMPL_VEC_EXTR_3(x,y,z);
	OGLPLUS_IMPL_VEC_EXTR_3(x,y,_);
	OGLPLUS_IMPL_VEC_EXTR_3(x,z,x);
	OGLPLUS_IMPL_VEC_EXTR_3(x,z,y);
	OGLPLUS_IMPL_VEC_EXTR_3(x,z,z);
	OGLPLUS_IMPL_VEC_EXTR_3(x,z,_);
	OGLPLUS_IMPL_VEC_EXTR_3(x,_,x);
	OGLPLUS_IMPL_VEC_EXTR_3(x,_,y);
	OGLPLUS_IMPL_VEC_EXTR_3(x,_,z);
	OGLPLUS_IMPL_VEC_EXTR_3(x,_,_);

	OGLPLUS_IMPL_VEC_EXTR_3(y,x,x);
	OGLPLUS_IMPL_VEC_EXTR_3(y,x,y);
	OGLPLUS_IMPL_VEC_EXTR_3(y,x,z);
	OGLPLUS_IMPL_VEC_EXTR_3(y,x,_);
	OGLPLUS_IMPL_VEC_EXTR_3(y,y,x);
	OGLPLUS_IMPL_VEC_EXTR_3(y,y,y);
	OGLPLUS_IMPL_VEC_EXTR_3(y,y,z);
	OGLPLUS_IMPL_VEC_EXTR_3(y,y,_);
	OGLPLUS_IMPL_VEC_EXTR_3(y,z,x);
	OGLPLUS_IMPL_VEC_EXTR_3(y,z,y);
	OGLPLUS_IMPL_VEC_EXTR_3(y,z,z);
	OGLPLUS_IMPL_VEC_EXTR_3(y,z,_);
	OGLPLUS_IMPL_VEC_EXTR_3(y,_,x);
	OGLPLUS_IMPL_VEC_EXTR_3(y,_,y);
	OGLPLUS_IMPL_VEC_EXTR_3(y,_,z);
	OGLPLUS_IMPL_VEC_EXTR_3(y,_,_);

	OGLPLUS_IMPL_VEC_EXTR_3(z,x,x);
	OGLPLUS_IMPL_VEC_EXTR_3(z,x,y);
	OGLPLUS_IMPL_VEC_EXTR_3(z,x,z);
	OGLPLUS_IMPL_VEC_EXTR_3(z,x,_);
	OGLPLUS_IMPL_VEC_EXTR_3(z,y,x);
	OGLPLUS_IMPL_VEC_EXTR_3(z,y,y);
	OGLPLUS_IMPL_VEC_EXTR_3(z,y,z);
	OGLPLUS_IMPL_VEC_EXTR_3(z,y,_);
	OGLPLUS_IMPL_VEC_EXTR_3(z,z,x);
	OGLPLUS_IMPL_VEC_EXTR_3(z,z,y);
	OGLPLUS_IMPL_VEC_EXTR_3(z,z,z);
	OGLPLUS_IMPL_VEC_EXTR_3(z,z,_);
	OGLPLUS_IMPL_VEC_EXTR_3(z,_,x);
	OGLPLUS_IMPL_VEC_EXTR_3(z,_,y);
	OGLPLUS_IMPL_VEC_EXTR_3(z,_,z);
	OGLPLUS_IMPL_VEC_EXTR_3(z,_,_);

	OGLPLUS_IMPL_VEC_EXTR_3(_,x,x);
	OGLPLUS_IMPL_VEC_EXTR_3(_,x,y);
	OGLPLUS_IMPL_VEC_EXTR_3(_,x,z);
	OGLPLUS_IMPL_VEC_EXTR_3(_,x,_);
	OGLPLUS_IMPL_VEC_EXTR_3(_,y,x);
	OGLPLUS_IMPL_VEC_EXTR_3(_,y,y);
	OGLPLUS_IMPL_VEC_EXTR_3(_,y,z);
	OGLPLUS_IMPL_VEC_EXTR_3(_,y,_);
	OGLPLUS_IMPL_VEC_EXTR_3(_,z,x);
	OGLPLUS_IMPL_VEC_EXTR_3(_,z,y);
	OGLPLUS_IMPL_VEC_EXTR_3(_,z,z);
	OGLPLUS_IMPL_VEC_EXTR_3(_,z,_);
	OGLPLUS_IMPL_VEC_EXTR_3(_,_,x);
	OGLPLUS_IMPL_VEC_EXTR_3(_,_,y);
	OGLPLUS_IMPL_VEC_EXTR_3(_,_,z);

#undef OGLPLUS_IMPL_VEC_EXTR_3

#define OGLPLUS_IMPL_VEC_EXTR_2(A,B) \
	Vector<T, 2> A ## B (T v = T(0)) const \
	{ \
		return Extract< \
			_spatial_dims::_ ## A, \
			_spatial_dims::_ ## B  \
		>(*this, v); \
	}

	OGLPLUS_IMPL_VEC_EXTR_2(x,x);
	OGLPLUS_IMPL_VEC_EXTR_2(x,y);
	OGLPLUS_IMPL_VEC_EXTR_2(x,z);
	OGLPLUS_IMPL_VEC_EXTR_2(x,_);
	OGLPLUS_IMPL_VEC_EXTR_2(y,x);
	OGLPLUS_IMPL_VEC_EXTR_2(y,y);
	OGLPLUS_IMPL_VEC_EXTR_2(y,z);
	OGLPLUS_IMPL_VEC_EXTR_2(y,_);
	OGLPLUS_IMPL_VEC_EXTR_2(z,x);
	OGLPLUS_IMPL_VEC_EXTR_2(z,y);
	OGLPLUS_IMPL_VEC_EXTR_2(z,z);
	OGLPLUS_IMPL_VEC_EXTR_2(z,_);
	OGLPLUS_IMPL_VEC_EXTR_2(_,x);
	OGLPLUS_IMPL_VEC_EXTR_2(_,y);
	OGLPLUS_IMPL_VEC_EXTR_2(_,z);

#undef OGLPLUS_IMPL_VEC_EXTR_2

