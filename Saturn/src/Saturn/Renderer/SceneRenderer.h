#pragma once

#include "Saturn/Scene/Scene.h"
#include "Saturn/Renderer/Mesh.h"
#include "RenderPass.h"

namespace Saturn {

	struct SceneRendererOptions
	{
		bool ShowGrid = true;
		bool ShowBoundingBoxes = false;
	};

	struct SceneRendererCamera
	{
		Saturn::EditorCamera Camera;
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