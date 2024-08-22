#pragma once

#ifndef __GAMEENGINE_H
#define __GAMEENGINE_H

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>
#include <cstdint>
#include <vector>
#include <iostream>
#include <optional>

namespace GameEngine
{
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	class GameEngine
	{
	public:
		void run();
		void mainLoop();

		GameEngine();
		void init();

	private:
		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			bool isComplete() const
			{
				return graphicsFamily.has_value();
			}
		};

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		bool isDeviceSuitable(VkPhysicalDevice device);

		void initGLFW();
		void initVulkan();
		void pickPhysicalDevice();
		VkDebugUtilsMessengerEXT debugMessenger;
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void setupDebugMessenger();
		std::vector<const char*> getRequiredExtensions();

		bool is_initialized = false;

		GLFWwindow* window = nullptr;
		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;
		VkInstance instance = nullptr;

		void cleanUpVulkan();
		void cleanUpWindow();
		void cleanUpGLFW();

		void initWindow();

		bool checkValidationLayerSupport();
		void createInstance();

	protected:

	};
}
#endif // __GAMEENGINE_H