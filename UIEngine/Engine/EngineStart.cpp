#include "pch.h"

// Tracy C++ profiler
#include <Tracy.hpp>

#include "ECS.h"
#include "ImGuiLayer.h"
#include "SceneStateMachine.h"
#include "Services.h"
#include "TestingScene.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"

int main()
{
	// Memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::string windowName = "OpenGL UI Testing";

	// Create Window
	auto window = std::make_unique<Window>(1920, 1080, windowName);
	if (!window)
	{
		std::cout << "Failed to create Window!" << std::endl;
		return -1;
	}

	auto shaderManager = ResourceManager<Shader>();
	shaderManager.Initialise("Shader Manager");

	auto textureManager = ResourceManager<Texture>();
	textureManager.Initialise("Texture Manager");

	// Load shaders
	Shader* basicShader = shaderManager.Load("Shaders/lit.vert", "Shaders/lit.frag").get();
	Shader* fontShader  = shaderManager.Load("Shaders/font.vert", "Shaders/font.frag").get();

	Renderer2D renderer = Renderer2D(nullptr, basicShader, fontShader);
	ECS::Instance()->Init(&renderer);

	Services services(window.get());
	services.SetShaderManager(&shaderManager);
	services.SetTextureManager(&textureManager);

	TestingScene scene("FirstScene");

	auto stateMachine = SceneStateMachine(&services);
	stateMachine.AddScene(&scene);
	stateMachine.SetCurrentScene(&scene);

	// ImGui Setup
	ImGuiLayer imguiLayer(window->GetWindow());

	// Engine Loop
	while (!window->Window_shouldClose())
	{
		ZoneScopedN("Frame");
		// Update Window
		window->Update_Window();
		float dt = window->GetDeltaTime();

		// Start the Dear ImGui frame
		imguiLayer.NewFrame();
		
		stateMachine.update(dt);
		
		stateMachine.render(*window);

		ECS::Instance()->Update();

		ImGui::Render();
		renderer.Draw();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		imguiLayer.UpdateViewPorts();
		FrameMark;
	}

	ECS::Instance()->Destroy();
	return 0;
}