#pragma once

#ifdef MYENGINE_PLATFORM_WINDOWS

extern my::Application* my::createApplication();

void main(int argc, char** argv)
{
	my::Log::init();
	MYENGINE_CORE_WARN("Initialized log.");
	MYENGINE_CLIENT_TRACE("Okie-doki!");

	auto app = my::createApplication();
	app->run();
	delete app;
}

#endif // MYENGINE_PLATFORM_WINDOWS