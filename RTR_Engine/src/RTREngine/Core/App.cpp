#include "rtrpch.h"

#include "RTREngine/Core/App.h"
#include "RTREngine/Core/Log.h"
#include "RTREngine/Input/Input.h"
#include "RTREngine/Renderer/Renderer.h"

#include <glfw/glfw3.h>


namespace RTREngine {

	App* App::s_Instance = nullptr;


	App::App()
	{
		RTR_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallback(RTR_BIND_EVENT_FN(App::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}


	App::~App()
	{
	}


	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(RTR_BIND_EVENT_FN(App::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(RTR_BIND_EVENT_FN(App::OnWindowResize));

		// Updates LayerStack from last to first so that unnecessary calculations in deeper layers can be avoided
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}


	void App::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}


	void App::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	/*
	*	Represents the actual render loop of the application
	*/
	void App::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Time deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) 
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(deltaTime);
				}

				// Always update UI GUI last
				m_ImGuiLayer->Begin();
				{
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}


	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}


	bool App::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		return false;
	}
}
