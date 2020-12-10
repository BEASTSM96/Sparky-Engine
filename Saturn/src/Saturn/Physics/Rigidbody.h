#pragma once

#include <glm/glm.hpp>

#pragma warning(push)
#include <reactphysics3d/reactphysics3d.h>
#pragma  warning(pop)

namespace Saturn {

	class PhysicsScene;

	class Rigidbody {
	public:
		Rigidbody(PhysicsScene* scene, bool useGravity = true, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f));
		~Rigidbody();

		void AddBoxCollider(const glm::vec3& halfExtents);
		void AddSphereCollider(float radius);

		glm::vec3 GetPosition( void );
		glm::quat GetRotation( void );

		inline bool GetKinematic( void ) const { return m_isKinematic; }
		void SetKinematic(bool set);

		float GetMass( void ) const;
		void SetMass(float mass);

		//
		// Manipulation (rb)
		void ApplyForce(glm::vec3 force);
		void ApplyForceAtLocation(glm::vec3 force, glm::vec3 location);
		void ApplyTorque(glm::vec3 torque);
		void SetCOG(glm::vec3 cog);
		void UseGravity(bool use);
	private:
		PhysicsScene* m_scene;

		std::vector<reactphysics3d::Collider*> m_colliders;
		bool m_isKinematic;
		reactphysics3d::RigidBody* m_body;
	private:
		friend class Scene;
	};
}