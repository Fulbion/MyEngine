#include <MyEngine.hpp>

class ExampleApp : public my::Application
{
public:
	ExampleApp()
	{

	}

	~ExampleApp()
	{

	}
};

my::Application* my::createApplication()
{
	return new ExampleApp();
}