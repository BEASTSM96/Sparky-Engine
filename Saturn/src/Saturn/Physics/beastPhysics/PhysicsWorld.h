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

#include "Core.h"

#include <vector>

#include "Saturn/Core/Ref.h"
#include "Saturn/Core/Timestep.h"
#include "Saturn/Scene/Scene.h"
#include "Saturn/Scene/Components.h"
#include "Saturn/Scene/Entity.h"
#include "Collision.h"

namespace Saturn {

	class PhysicsWorld : public RefCounted
	{
	public:
		PhysicsWorld( Ref<Scene> scene ) { m_Scene = scene; }

		void Step( Timestep ts ) 
		{
			auto view = m_Scene->GetRegistry().view<TransformComponent, PhysicsComponent>();

			for( const auto& entity : view )
			{
				auto [tc, pc] = view.get<TransformComponent, PhysicsComponent>( entity );

				pc.Force += pc.Mass * m_Gravity;

				pc.Velocity += pc.Force / pc.Mass * ts.GetSeconds();

				pc.Position += pc.Velocity;

				pc.Force = glm::vec3( 0, 0, 0 );

			}
		}

		void SetEntityPos(Entity entity)
		{
			entity.GetComponent<TransformComponent>().Position = entity.GetComponent<PhysicsComponent>().Position;
		}

		void TestAABBWorld ( Entity a, Entity b )
		{
			auto& atc =  a.GetComponent<TransformComponent>();
			auto& btc =  b.GetComponent<TransformComponent>();

			Collision::TestAABB(atc.Position, btc.Position);

		}

	protected:
		Ref<Scene> m_Scene;

	private:
		std::vector<PhysicsComponent> m_PhysicsComponents;
		glm::vec3 m_Gravity = glm::vec3( 0, -9.81f, 0 );
	};


}