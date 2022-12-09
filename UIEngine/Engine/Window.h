#include "gl/glew.h"
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window(int width, int height, std::string_view name);

	~Window();

	// Window Functions
	int Window_intit(int width, int height, std::string_view name);

	void Update_Window();

	int Window_shouldClose();

	void Window_destroy();

	float GetDeltaTime() const;

private:
	// Main Window
	GLFWwindow* window;

	// DeltaTime
	double last = 0.0;
	double now  = 0.0;
	float delta = 1.0f;
};
