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

#pragma once

#include "Saturn/Scene/Scene.h"
#include "Saturn/Renderer/Mesh.h"
#include "RenderPass.h"

namespace Saturn {

	struct SceneRendererOptions
	{
		bool ShowGrid = true;
		bool ShowSolids = true;
		bool ShowBoundingBoxes = false;
	};

	struct SceneRendererCamera
	{
		Saturn::Camera Camera;
		glm::mat4 ViewMatrix;
	};

	class SceneRenderer
	{
	public:
		static void Init( void );

		static void SetViewportSize( uint32_t width, uint32_t height );

		static void BeginScene( const Scene* scene, const SceneRendererCamera& camera );
		static void EndScene( void );

		static void SubmitMesh( Ref<Mesh> mesh, const glm::mat4& transform = glm::mat4( 1.0f ), Ref<MaterialInstance> overrideMaterial = nullptr );
		static void SubmitSelectedMesh( Ref<Mesh> mesh, const glm::mat4& transform = glm::mat4( 1.0f ) );

		static std::pair<Ref<TextureCube>, Ref<TextureCube>> CreateEnvironmentMap( const std::string& filepath );

		static Ref<RenderPass> GetFinalRenderPass( void );
		static Ref<Texture2D> GetFinalColorBuffer( void );

		static uint32_t GetFinalColorBufferRendererID();

		static SceneRendererOptions& GetOptions();
	private:
		static void FlushDrawList( void );
		static void GeometryPass( void );
		static void CompositePass( void );
	};
}