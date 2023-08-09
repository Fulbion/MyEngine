#include "Engine/Application.hpp"

namespace my
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		MYENGINE_CORE_TRACE(e.toString());

		while (true)
		{

		}
	}
}