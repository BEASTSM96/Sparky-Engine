#include <Sparky.h>

#include <Sparky/GameBase/GameObject.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

#ifndef SPARKY_SANDBOX
#define SPARKY_SANDBOX
#include <Sparky/Core/Serialisation/Serialiser.h>
#endif // SPARKY_SANDBOX

class ExampleLayer : public Saturn::Layer
{
public:

	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{

		//archive();

		//m_VertexArray.reset(Saturn::VertexArray::Create());

		//float vertices[3 * 7] = {
		//	-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		//	 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		//	 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		//};

		//Saturn::Ref<Saturn::VertexBuffer> vertexBuffer;
		//vertexBuffer.reset(Saturn::VertexBuffer::Create(vertices, sizeof(vertices)));
		//Saturn::BufferLayout layout = {
		//	{ Saturn::ShaderDataType::Float3, "a_Position" },
		//	{ Saturn::ShaderDataType::Float4, "a_Color" }
		//};
		//vertexBuffer->SetLayout(layout);
		//m_VertexArray->AddVertexBuffer(vertexBuffer);

		//uint32_t indices[3] = { 0, 1, 2 };
		//Saturn::Ref<Saturn::IndexBuffer> indexBuffer;
		//indexBuffer.reset(Saturn::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		//m_VertexArray->SetIndexBuffer(indexBuffer);

		//m_SquareVA.reset(Saturn::VertexArray::Create());

		//float squareVertices[5 * 4] = {
		//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		//	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		//	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		//	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		//};

		//Saturn::Ref<Saturn::VertexBuffer> squareVB;
		//squareVB.reset(Saturn::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		//squareVB->SetLayout({
		//	{ Saturn::ShaderDataType::Float3, "a_Position" },
		//	{ Saturn::ShaderDataType::Float2, "a_TexCoord" }
		//	});
		//m_SquareVA->AddVertexBuffer(squareVB);

		//uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		//Saturn::Ref<Saturn::IndexBuffer> squareIB;
		//squareIB.reset(Saturn::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		//m_SquareVA->SetIndexBuffer(squareIB);

		//std::string vertexSrc = R"(
		//	#version 330 core
		//	
		//	layout(location = 0) in vec3 a_Position;
		//	layout(location = 1) in vec4 a_Color;
		//	uniform mat4 u_ViewProjection;
		//	uniform mat4 u_Transform;
		//	out vec3 v_Position;
		//	out vec4 v_Color;
		//	void main()
		//	{
		//		v_Position = a_Position;
		//		v_Color = a_Color;
		//		gl_Position = u_ViewProjection * u_Transform *vec4(a_Position, 1.0);	
		//	}
		//)";

		//std::string fragmentSrc = R"(
		//	#version 330 core
		//	
		//	layout(location = 0) out vec4 color;
		//	in vec3 v_Position;
		//	in vec4 v_Color;
		//	void main()
		//	{
		//		color = vec4(v_Position * 0.5 + 0.5, 1.0);
		//		color = v_Color;
		//	}
		//)";

		//m_Shader.reset(Saturn::Shader::Create(vertexSrc, fragmentSrc));

		//std::string flatShaderVertexSrc = R"(
		//	#version 330 core
		//	
		//	layout(location = 0) in vec3 a_Position;
		//	uniform mat4 u_ViewProjection;
		//	uniform mat4 u_Transform;
		//	out vec3 v_Position;
		//	void main()
		//	{
		//		v_Position = a_Position;
		//		gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
		//	}
		//)";

		//std::string flastShaderFragmentSrc = R"(
		//	#version 330 core
		//	
		//	layout(location = 0) out vec4 color;

		//	in vec3 v_Position;

		//	uniform vec3 u_Color;

		//	void main()
		//	{
		//		color = vec4(u_Color, 1.0);
		//	}
		//)";

		//m_flatShader.reset(Saturn::Shader::Create(flatShaderVertexSrc, flastShaderFragmentSrc));

		//std::string textureShaderVertexSrc = R"(
		//	#version 330 core
		//	
		//	layout(location = 0) in vec3 a_Position;
		//	layout(location = 1) in vec2 a_TexCoord;
		//	uniform mat4 u_ViewProjection;
		//	uniform mat4 u_Transform;
		//	out vec2 v_TexCoord;
		//	void main()
		//	{
		//		v_TexCoord = a_TexCoord;
		//		gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
		//	}
		//)";

		//std::string textureShaderFragmentSrc = R"(
		//	#version 330 core
		//	
		//	layout(location = 0) out vec4 color;
		//	in vec2 v_TexCoord;
		//	
		//	uniform sampler2D u_Texture;
		//	void main()
		//	{
		//		color = texture(u_Texture, v_TexCoord);
		//	}
		//)";

		//m_TextureShader.reset(Saturn::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		//std::vector<STexture> textures {
		//		STexture("Beastpic", "assets/tex/beastpic_pfp_1.png"),
		//		STexture("Checkerboard", "assets/tex/Checkerboard.png")
		//};
	
		//Json::Value serialiser;
		//for (STexture i : textures)
		//{
		//	serialiser["Textures"][i.name]["Path"] = i.path;
		//}

		//{
		//	std::ofstream texFile("assets/tex/json/test1.json");
		//	texFile << serialiser;
		//}

		////Deserialise
		//std::vector<STexture*> deserialiseObjects;
		//uint32_t count = 0;
		//for (const Json::Value& object : serialiser["Textures"])
		//{
		//	deserialiseObjects.push_back(new STexture(serialiser["Textures"].getMemberNames()[count], object.get("Path", 0).asString()));
		//	count++;
		//}

		//deserialiseObjects;

		//m_beastlogo = Saturn::Texture2D::Create(deserialiseObjects.at(0)->path);
		//m_Texture = Saturn::Texture2D::Create(deserialiseObjects.at(1)->path);


		//std::dynamic_pointer_cast<Saturn::OpenGLShader>(m_TextureShader)->Bind();
		//std::dynamic_pointer_cast<Saturn::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Saturn::Timestep ts) override
	{
		/*if (Saturn::Input::IsKeyPressed(SAT_KEY_LEFT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		else if (Saturn::Input::IsKeyPressed(SAT_KEY_RIGHT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}

		if (Saturn::Input::IsKeyPressed(SAT_KEY_DOWN))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}

		else if (Saturn::Input::IsKeyPressed(SAT_KEY_UP))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		if (Saturn::Input::IsKeyPressed(SAT_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		if (Saturn::Input::IsKeyPressed(SAT_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}*/

		/*Saturn::RenderCommand::SetClearColor({ 1, 1, 0, 0 });
		Saturn::RenderCommand::Clear();*/

//		m_Camera.SetPosition(m_CameraPosition);
//		m_Camera.SetRotation(m_CameraRotation);

//		Saturn::Renderer::BeginScene(m_Camera);

		//glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		//std::dynamic_pointer_cast<Saturn::OpenGLShader>(m_flatShader)->Bind();
		//std::dynamic_pointer_cast<Saturn::OpenGLShader>(m_flatShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		/*for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 trasform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Saturn::Renderer::Submit(m_flatShader, m_SquareVA, trasform);
			}

		}*/

		//TEMP
#ifndef SAT_DEBUG

		//m_Texture->Bind();

		//Saturn::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//m_beastlogo->Bind();
		//Saturn::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Saturn::Renderer::Submit(m_Shader, m_VertexArray);
#endif

		/*Saturn::Renderer::EndScene();*/

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();

	}

	void OnEvent(Saturn::Event& event) override
	{
		Saturn::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Saturn::KeyPressedEvent>(SAT_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
	}

	bool OnKeyPressed(Saturn::KeyPressedEvent& event) {
	
		

		return false;

	}

private:

	Saturn::Ref<Saturn::Shader> m_Shader;
	Saturn::Ref<Saturn::VertexArray> m_VertexArray;

	Saturn::Ref<Saturn::Shader> m_flatShader, m_TextureShader;
	Saturn::Ref<Saturn::VertexArray> m_SquareVA;

	Saturn::Ref<Saturn::Texture2D> m_Texture, m_beastlogo;

	Saturn::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;


	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquarePosition;
public:
	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};


class Sandbox : public Saturn::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{

	}

};

Saturn::Application* Saturn::CreateApplication()
{
	return new Sandbox();
}