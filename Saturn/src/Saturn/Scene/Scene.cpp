#include "sppch.h"
#include "Scene.h"

#include "Components.h"

#include <glm/glm.hpp>
#include "Entity.h"
#include "Saturn/Core/Math/Math.h"
#include "Saturn/GameBase/GameObject.h"
#include "Saturn/Core/World/Level.h"

namespace Saturn {

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{

	}

	Scene::Scene()
	{

		m_data.ID = Random::Float();
		m_data.name = m_data.name.empty() ? "Scene" : m_data.name;


		/*******************************************************************************************************************/
		m_CurrentLevel = new Level();
		m_CurrentLevel->CreateGameLayer();

		/*******************************************************************************************************************/
#if ENTT_EXAMPLE_CODE
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();


		if (m_Registry.has<TransformComponent>(entity))
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);


		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		}
#endif
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Unmaned Entity" : name;

		auto& ID = entity.AddComponent<IdComponent>();
		ID.Id = Random::Float();

		return entity;
	}

	GameObject Scene::CreateEntityGameObject(const std::string& name)
	{
		GameObject entity = { m_Registry.create(), this };

		entity.AddComponent<TransformComponent>();
		
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Unmaned GameObject" : name;

		auto& ID = entity.AddComponent<IdComponent>();
		ID.Id = Random::Float();

		return entity;
	}

	GameObject * Scene::CreateEntityGameObjectprt(const std::string& name)
	{
		GameObject * entity = new GameObject( m_Registry.create(), this );

		entity->AddComponent<TransformComponent>();

		auto& tag = entity->AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Unmaned GameObject" : name;

		auto& ID = entity->AddComponent<IdComponent>();
		ID.Id = Random::Float();

		entity->Init();

		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		SAT_CORE_ASSERT(m_CurrentLevel->GetGameLayer(), "Error GameLayer is null!");
	}


}