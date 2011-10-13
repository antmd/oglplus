/**
 *  @example oglplus/022_volumetric_light.cpp
 *  @brief Shows how to render a volumetric light
 *
 *  @image html 022_volumetric_light.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/images/load.hpp>

#include <oglplus/bound/texture.hpp>

#include "example.hpp"

namespace oglplus {

class VolLightExample : public Example
{
private:
	// wrapper around the current OpenGL context
	Context gl;

	VertexShader volume_vs, plane_vs;
	GeometryShader volume_gs;
	FragmentShader volume_fs, plane_fs;

	Program volume_prog, plane_prog;

	VertexArray volume, plane;
	Buffer volume_pos, plane_pos;

	const size_t samples;

	Texture light_tex;
public:
	VolLightExample(void)
	 : volume_vs("Volume vertex")
	 , plane_vs("Plane vertex")
	 , volume_gs("Volume geometry")
	 , volume_fs("Volume fragment")
	 , plane_fs("Plane fragment")
	 , volume_prog("Volume")
	 , plane_prog("Plane")
	 , samples(150)
	{
		volume_vs.Source(
			"#version 330\n"
			"in vec4 Position;"
			"uniform int SampleCount;"
			"uniform mat4 CameraMatrix;"
			"uniform vec3 ViewZ;"
			"uniform float Size;"
			"void main(void)"
			"{"
			"	float hp = (SampleCount-1) * 0.5;"
			"	float ZOffs = (gl_InstanceID - hp)/hp;"
			"	gl_Position = vec4("
			"		Position.xyz +"
			"		ViewZ*ZOffs*Size*0.5,"
			"		1.0"
			"	);"
			"}"
		);
		volume_vs.Compile();

		volume_gs.Source(
			"#version 330\n"
			"layout(points) in;"
			"layout(triangle_strip, max_vertices = 4) out;"
			"uniform mat4 CameraMatrix, ProjectionMatrix;"
			"uniform mat4 TexProjectionMatrix;"
			"uniform vec3 ViewX, ViewY;"
			"uniform float Size;"
			"in float vertZOffs[];"
			"out vec4 geomTexCoord;"
			"void main(void)"
			"{"
			"	float zo = vertZOffs[0];"
			"	float yo[2] = float[2](-1.0, 1.0);"
			"	float xo[2] = float[2](-1.0, 1.0);"
			"	for(int j=0;j!=2;++j)"
			"	for(int i=0;i!=2;++i)"
			"	{"
			"		vec4 v = vec4("
			"			gl_in[0].gl_Position.xyz+"
			"			ViewX * xo[i] * Size+"
			"			ViewY * yo[j] * Size,"
			"			1.0"
			"		);"
			"		geomTexCoord = "
			"			TexProjectionMatrix *"
			"			v;"
			"		gl_Position = "
			"			ProjectionMatrix *"
			"			CameraMatrix * v;"
			"		EmitVertex();"
			"	}"
			"	EndPrimitive();"
			"}"
		);
		volume_gs.Compile();

		volume_fs.Source(
			"#version 330\n"
			"uniform sampler2D LightTex;"
			"uniform int SampleCount;"
			"in vec4 geomTexCoord;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	vec2 coord = geomTexCoord.st/geomTexCoord.q;"
			"	float depth = geomTexCoord.z;"
			"	if(depth < 0.0) discard;"
			"	vec4 t  = texture(LightTex, coord*0.5 + 0.5);"
			"	if(t.a == 0.0) discard;"
			"	float alpha = 10.0*(1.0-t.a)/SampleCount;"
			"	alpha *= (t.r+t.g+t.b)*0.3333;"
			"	alpha /= sqrt(depth);"
			"	fragColor = vec4(t.rgb, alpha);"
			"}"
		);
		volume_fs.Compile();

		volume_prog.AttachShader(volume_vs);
		volume_prog.AttachShader(volume_gs);
		volume_prog.AttachShader(volume_fs);
		volume_prog.Link();
		volume_prog.Use();

		// bind the VAO for the volumes
		volume.Bind();

		// bind the VBO for the volume positions
		volume_pos.Bind(Buffer::Target::Array);
		{
			GLfloat position[3] = {0.0, 0.0, 0.0};
			Buffer::Data(Buffer::Target::Array, 3, position);
			VertexAttribArray attr(volume_prog, "Position");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}

		Vec3f lightPos(2.0f, 4.0f, -3.0f);
		auto texProjMat =
			CamMatrixf::Perspective(Degrees(60), 1.0, 0.1, 10.0) *
			CamMatrixf::LookingAt(lightPos, Vec3f(0, 0, 0));

		Uniform(volume_prog, "SampleCount").Set(GLint(samples));
		Uniform(volume_prog, "Size").Set(Length(lightPos));
		Uniform(volume_prog, "TexProjectionMatrix").SetMatrix(texProjMat);

		plane_vs.Source(
			"#version 330\n"
			"in vec4 Position;"
			"uniform mat4 CameraMatrix, ProjectionMatrix;"
			"uniform mat4 TexProjectionMatrix;"
			"out vec2 vertChecker;"
			"out vec4 vertTexCoord;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		Position;"
			"	vertTexCoord = "
			"		TexProjectionMatrix *"
			"		Position;"
			"	vertChecker = Position.xz;"
			"}"
		);
		plane_vs.Compile();

		plane_fs.Source(
			"#version 330\n"
			"uniform sampler2D LightTex;"
			"in vec4 vertTexCoord;"
			"in vec2 vertChecker;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	vec2 coord = vertTexCoord.st/vertTexCoord.q;"
			"	vec4 t  = texture(LightTex, coord*0.5 + 0.5);"
			"	float i = ("
			"		1 +"
			"		int(vertChecker.x+10) % 2+"
			"		int(vertChecker.y+10) % 2"
			"	) % 2;"
			"	vec3 color = vec3(0.1, 0.1, 0.1);"
			"	color += t.rgb * (1.0 - t.a);"
			"	color *= mix("
			"		vec3(0.9, 0.9, 1.0), "
			"		vec3(0.4, 0.4, 0.9), "
			"		i"
			"	);"
			"	fragColor = vec4(color, 1.0);"
			"}"
		);
		plane_fs.Compile();

		plane_prog.AttachShader(plane_vs);
		plane_prog.AttachShader(plane_fs);
		plane_prog.Link();
		plane_prog.Use();

		Uniform(plane_prog, "TexProjectionMatrix").SetMatrix(texProjMat);

		plane.Bind();

		// bind the VBO for the plane vertices
		plane_pos.Bind(Buffer::Target::Array);
		{
			GLfloat data[4*3] = {
				-9.0f, -4.0f,  9.0f,
				-9.0f, -4.0f, -9.0f,
				 9.0f, -4.0f,  9.0f,
				 9.0f, -4.0f, -9.0f
			};
			Buffer::Data(Buffer::Target::Array, 4*3, data);
			plane_prog.Use();
			VertexAttribArray attr(plane_prog, "Position");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}

		Texture::Active(0);
		Uniform(volume_prog, "LightTex").Set(0);
		{
			auto bound_tex = Bind(light_tex, Texture::Target::_2D);
			bound_tex.Image2D(images::LoadTexture("flower_glass"));
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.BorderColor(Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
			bound_tex.WrapS(TextureWrap::ClampToBorder);
			bound_tex.WrapT(TextureWrap::ClampToBorder);
		}

		gl.ClearColor(0.0f, 0.05f, 0.1f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.BlendFunc(BlendFn::SrcAlpha, BlendFn::One);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		auto perspective = CamMatrixf::Perspective(
			Degrees(48),
			double(width)/height,
			1, 100
		);
		ProgramUniform(
			plane_prog,
			"ProjectionMatrix"
		).SetMatrix(perspective);
		ProgramUniform(
			volume_prog,
			"ProjectionMatrix"
		).SetMatrix(perspective);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		auto cameraMatrix = CamMatrixf::Orbiting(
			Vec3f(0.0f, 3.0f, 0.0f),
			6.5f,
			FullCircles(time / 12.0),
			Degrees(SineWave(time / 20.0) * 80)
		);

		plane.Bind();
		plane_prog.Use();
		Uniform(plane_prog, "CameraMatrix").SetMatrix(cameraMatrix);

		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

		gl.Enable(Capability::Blend);

		volume.Bind();
		volume_prog.Use();
		Uniform(volume_prog, "CameraMatrix").SetMatrix(cameraMatrix);
		Uniform(volume_prog, "ViewX").Set(
			Row<0>(cameraMatrix).xyz()
		);
		Uniform(volume_prog, "ViewY").Set(
			Row<1>(cameraMatrix).xyz()
		);
		Uniform(volume_prog, "ViewZ").Set(
			Row<2>(cameraMatrix).xyz()
		);
		gl.DrawArraysInstanced(
			PrimitiveType::Points,
			0, 1,
			samples
		);

		gl.Disable(Capability::Blend);
	}

	bool Continue(double time)
	{
		return time < 60.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new VolLightExample);
}

} // namespace oglplus