#pragma once

#include "Engine/Core.hpp"

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