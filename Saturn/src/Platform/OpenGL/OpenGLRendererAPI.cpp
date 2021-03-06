/********************************************************************************************
*                                                                                           *
*                                                                                           *
*                                                                                           *
* MIT License                                                                               *
*                                                                                           *
* Copyright (c) 2020 - 2021 BEAST                                                           *
*                                                                                           *
* Permission is hereby granted, free of charge, to any person obtaining a copy              *
* of this software and associated documentation files (the "Software"), to deal             *
* in the Software without restriction, including without limitation the rights              *
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                 *
* copies of the Software, and to permit persons to whom the Software is                     *
* furnished to do so, subject to the following conditions:                                  *
*                                                                                           *
* The above copyright notice and this permission notice shall be included in all            *
* copies or substantial portions of the Software.                                           *
*                                                                                           *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                  *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE               *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                    *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,             *
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE             *
* SOFTWARE.                                                                                 *
*********************************************************************************************
*/

#include "sppch.h"
#include "Saturn/Renderer/RendererAPI.h"

#include <glad/glad.h>

namespace Saturn {

	static void OpenGLLogMessage( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam )
	{
		switch( severity )
		{
			case GL_DEBUG_SEVERITY_HIGH:
				SAT_CORE_ERROR( "[OpenGL Debug HIGH] {0}", message );
				SAT_CORE_ASSERT( false, "GL_DEBUG_SEVERITY_HIGH" );
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				SAT_CORE_WARN( "[OpenGL Debug MEDIUM] {0}", message );
				break;
			case GL_DEBUG_SEVERITY_LOW:
				SAT_CORE_INFO( "[OpenGL Debug LOW] {0}", message );
				break;
				break;
		}
	}

	void RendererAPI::Init()
	{
		glDebugMessageCallback( OpenGLLogMessage, nullptr );
		glEnable( GL_DEBUG_OUTPUT );
		glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );

		unsigned int vao;
		glGenVertexArrays( 1, &vao );
		glBindVertexArray( vao );

		glEnable( GL_DEPTH_TEST );
		//glEnable(GL_CULL_FACE);
		glEnable( GL_TEXTURE_CUBE_MAP_SEAMLESS );
		glFrontFace( GL_CCW );

		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		glEnable( GL_MULTISAMPLE );
		glEnable( GL_STENCIL_TEST );

		auto& caps = RendererAPI::GetCapabilities();

		caps.Vendor = ( const char* )glGetString( GL_VENDOR );
		caps.Renderer = ( const char* )glGetString( GL_RENDERER );
		caps.Version = ( const char* )glGetString( GL_VERSION );

		glGetIntegerv( GL_MAX_SAMPLES, &caps.MaxSamples );
		glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY, &caps.MaxAnisotropy );

		glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &caps.MaxTextureUnits );

		GLenum error = glGetError();
		while( error != GL_NO_ERROR )
		{
			SAT_CORE_ERROR( "OpenGL Error {0}", error );
			error = glGetError();
		}

		LoadRequiredAssets();
	}

	void RendererAPI::Shutdown()
	{
	}

	void RendererAPI::LoadRequiredAssets()
	{
	}

	void RendererAPI::Clear( float r, float g, float b, float a )
	{
		glClearColor( r, g, b, a );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	}

	void RendererAPI::SetClearColor( float r, float g, float b, float a )
	{
		glClearColor( r, g, b, a );
	}

	void RendererAPI::DrawIndexed( uint32_t count, PrimitiveType type, bool depthTest )
	{
		if( !depthTest )
			glDisable( GL_DEPTH_TEST );

		GLenum glPrimitiveType = 0;
		switch( type )
		{
			case PrimitiveType::Triangles:
				glPrimitiveType = GL_TRIANGLES;
				break;
			case PrimitiveType::Lines:
				glPrimitiveType = GL_LINES;
				break;
		}

		glDrawElements( glPrimitiveType, count, GL_UNSIGNED_INT, nullptr );

		if( !depthTest )
			glEnable( GL_DEPTH_TEST );
	}

	void RendererAPI::SetLineThickness( float thickness )
	{
		glLineWidth( thickness );
	}
}