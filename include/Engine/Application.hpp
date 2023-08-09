#pragma once

#include "Engine/Core.hpp"
#include "Engine/Log.hpp"
#include "Engine/Event.hpp"

namespace my
{
	class MYENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

	private:

	};

	Application* createApplication();
}