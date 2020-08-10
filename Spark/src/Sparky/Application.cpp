#include "sppch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"

#include "Log.h"

#include "Layer.h"

#include "Sparky/Input.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "ImGui/ImGuiLayer.h"

#include "Sparky\Renderer\Buffer.h"

#include "Renderer/Renderer.h"

#include "Renderer/OrthographicCamera.h"

#include "Sparky/Core/File/SparkyFile.h"

#include "Sparky/ImGui/ImGuiLayer.h"

#include <imgui.h>


#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <Windows.h>

namespace Sparky {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SP_CORE_ASSERT(!s_Instance, "Application already exists!");

		{
			s_Instance = this;
			m_Window = std::unique_ptr<Window>(Window::Create());
			m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
			m_Window->SetVSync(false);
		}

		{
			m_ImGuiLayer = new ImGuiLayer();
			m_FPSLayer = new ImGuiFPS();
			m_RenderStats = new ImGuiRenderStats();
			m_ImguiTopBar = new ImguiTopBar();
			m_EditorLayer = new EditorLayer();
		}

		{
			PushOverlay(m_ImGuiLayer);
			PushOverlay(m_RenderStats);
			PushOverlay(m_ImguiTopBar);
			PushOverlay(m_EditorLayer);
		}

	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{

			float time = (float)glfwGetTime(); //Platform::GetTime();

			Timestep timestep = time - LastFrameTime;

			LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

			/*
			bool bIsFileOpened = false;
			bool bWasFileOpened = false;
			if (!bIsFileOpened && !bWasFileOpened)
			{
				bWasFileOpened = true;


				FileCreation::NewProjectFile();

				bIsFileOpened = true;


				//FileReader::ReadFile("good3dgame.sproject", "testReader");

			}*/
		}
		while (m_Crashed)
		{
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);


			float time = (float)glfwGetTime(); //Platform::GetTime();

			Timestep timestep = time - LastFrameTime;

			LastFrameTime = time;

			m_Window->OnUpdate();
		}
	}

	void Application::SetCrashState(bool state)
	{
		m_Crashed = state;
		m_Running = !state;
	}

	bool Application::SetRunningState(bool state)
	{
		m_Running = state;

		return state;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	std::string Application::OpenFile(const char* filter) const
	{

		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.lpstrFilter = filter;
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)m_Window->GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrTitle = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}
		return std::string();
	}

	std::string Application::SaveFile() const
	{

		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };

		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.lpstrFilter = "SparkySaveFile\0 * .sasset; \0\0";
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)m_Window->GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrTitle = "Save file";
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetSaveFileNameA(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}
		return std::string();
	}

	std::string Application::OpenProjectFile() const
	{

		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAMEA));

		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.lpstrFilter = "ProjectFile\0*.sproject;\0\0";
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)m_Window->GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrTitle = "Open Project file";
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}
		return std::string();
	}


}