#include "rtrpch.h"
#include "RTREngine/Core/App.h"
#include "RTREngine/Core/Log.h"
#include "RTREngine/Input/Input.h"

#include <glfw/glfw3.h>


namespace RTREngine {

	App* App::s_Instance = nullptr;

	App::App()
	{
	}

	App::~App()
	{
	}

	void App::OnEvent(Event& e)
	{
	}

	void App::Run()
	{
		WindowResizeEvent e(1366, 768);
		RTR_CLIENT_TRACE(e);


		while (m_Running)
		{
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		return false;
	}

	bool App::OnWindowResize(WindowResizeEvent& e)
	{
		return false;
	}
}
