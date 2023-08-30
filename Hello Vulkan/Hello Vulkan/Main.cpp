
#include "SDL.h"
#include "SDL_vulkan.h"
#include "vulkan.h"
#include "vk_video/vulkan_video_codecs_common.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const std::vector<const char*> validationLayers = { "VK_Layer_Khronos_validation" };

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif


class HelloTriangleApplication
{
	SDL_Window* window;
	VkInstance instance;
private:
	void initWindow()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("hello vulkan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_VULKAN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
	}
	void createInstance()
	{

		if (enableValidationLayers && !checkValidationLayerSupport()) {
			throw std::runtime_error("validation layers requested, but not available!");
		}



		//This is all optional, but the info may be useful when debugging
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "hello triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;


		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		
		uint32_t SDLExtensionCount;
		std::vector<const char*> SDLExtensions; 
		SDL_Vulkan_GetInstanceExtensions(window, &SDLExtensionCount, nullptr); 
		SDLExtensions = std::vector<const char*> (SDLExtensionCount); 
		SDL_Vulkan_GetInstanceExtensions(window, &SDLExtensionCount, SDLExtensions.data());



		createInfo.enabledExtensionCount = SDLExtensionCount;
		createInfo.ppEnabledExtensionNames = SDLExtensions.data();
		createInfo.enabledLayerCount = 0;
		if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create instance");
		}
		
	}
	void initVulkan()
	{
		createInstance();
	}

	bool checkValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers)
		{
			bool layerFound = false;
			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}

			}
			if (!layerFound)
			{
				return false;
			}
		}
		return true;
	}
	void mainLoop()
	{
		bool isrunning = true;
		while (isrunning)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{


			}
		}
	}
	void cleanup()
	{
		vkDestroyInstance(instance,nullptr);
		SDL_DestroyWindow(window);
		window = NULL;
		SDL_Quit();
	}
public:
	void run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}
};


int main(int argc, char* argv[])
{
	HelloTriangleApplication app;

	try
	{
		app.run();
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS; 
	
	return 0;
}
