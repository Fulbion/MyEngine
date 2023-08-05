#pragma once

#include "Engine/Application.hpp"

#ifdef MYENGINE_PLATFORM_WINDOWS

extern my::Application* my::createApplication();

void main(int argc, char** argv)
{
	auto app = my::createApplication();
	app->run();
	delete app;
}

#endif // MYENGINE_PLATFORM_WINDOWS