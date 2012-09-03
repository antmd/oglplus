/*
 *  .file oglplus/enums/ext/nv_path_metric_query_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_metric_query.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLbitfield*,
	PathNVMetricQuery
> EnumValueRange(PathNVMetricQuery*)
OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
static const GLbitfield _values[] = {
#if defined GL_GLYPH_WIDTH_BIT_NV
GL_GLYPH_WIDTH_BIT_NV,
#endif
#if defined GL_GLYPH_HEIGHT_BIT_NV
GL_GLYPH_HEIGHT_BIT_NV,
#endif
#if defined GL_GLYPH_HORIZONTAL_BEARING_X_BIT_NV
GL_GLYPH_HORIZONTAL_BEARING_X_BIT_NV,
#endif
#if defined GL_GLYPH_HORIZONTAL_BEARING_Y_BIT_NV
GL_GLYPH_HORIZONTAL_BEARING_Y_BIT_NV,
#endif
#if defined GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV
GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV,
#endif
#if defined GL_GLYPH_VERTICAL_BEARING_X_BIT_NV
GL_GLYPH_VERTICAL_BEARING_X_BIT_NV,
#endif
#if defined GL_GLYPH_VERTICAL_BEARING_Y_BIT_NV
GL_GLYPH_VERTICAL_BEARING_Y_BIT_NV,
#endif
#if defined GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV
GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV,
#endif
#if defined GL_GLYPH_HAS_KERNING_NV
GL_GLYPH_HAS_KERNING_NV,
#endif
#if defined GL_FONT_X_MIN_BOUNDS_NV
GL_FONT_X_MIN_BOUNDS_NV,
#endif
#if defined GL_FONT_Y_MIN_BOUNDS_NV
GL_FONT_Y_MIN_BOUNDS_NV,
#endif
#if defined GL_FONT_X_MAX_BOUNDS_NV
GL_FONT_X_MAX_BOUNDS_NV,
#endif
#if defined GL_FONT_Y_MAX_BOUNDS_NV
GL_FONT_Y_MAX_BOUNDS_NV,
#endif
#if defined GL_FONT_UNITS_PER_EM_NV
GL_FONT_UNITS_PER_EM_NV,
#endif
#if defined GL_FONT_ASCENDER_NV
GL_FONT_ASCENDER_NV,
#endif
#if defined GL_FONT_DESCENDER_NV
GL_FONT_DESCENDER_NV,
#endif
#if defined GL_FONT_HEIGHT_NV
GL_FONT_HEIGHT_NV,
#endif
#if defined GL_FONT_MAX_ADVANCE_WIDTH_NV
GL_FONT_MAX_ADVANCE_WIDTH_NV,
#endif
#if defined GL_FONT_MAX_ADVANCE_HEIGHT_NV
GL_FONT_MAX_ADVANCE_HEIGHT_NV,
#endif
#if defined GL_FONT_UNDERLINE_POSITION_NV
GL_FONT_UNDERLINE_POSITION_NV,
#endif
#if defined GL_FONT_UNDERLINE_THICKNESS_NV
GL_FONT_UNDERLINE_THICKNESS_NV,
#endif
#if defined GL_FONT_HAS_KERNING_NV
GL_FONT_HAS_KERNING_NV,
#endif
0
};
return aux::CastIterRange<
	const GLbitfield*,
	PathNVMetricQuery
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#endif
