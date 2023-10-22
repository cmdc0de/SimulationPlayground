#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class App {
public:
	App();
	void initVulkan();
	void run();
	void cleanUp();
	void initWindow();
	void mainLoop();
protected:
   void createInstance();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void setupDebugMessenger();
	void getRequiredExtensions(std::vector<const char*> &extensions);
	bool checkValidationLayerSupport();
	void getAllExtensions(std::vector<VkExtensionProperties> &allExtensions);
	void logFeatures(VkPhysicalDeviceFeatures &f);
	bool isDeviceSuitable(const VkPhysicalDevice &device);
	void pickPhysicalDevice();
	uint32_t rateDevice(const VkPhysicalDevice &device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	void createLogicalDevice();
	void createSurface();
private:
    GLFWwindow* Window;
    VkInstance Instance;
    VkDebugUtilsMessengerEXT debugMessenger;
	 VkPhysicalDevice PhysicalDevice;
	 VkDevice SelectedDevice;
	 VkQueue GraphicsQueue;
	 VkSurfaceKHR Surface;
	 VkQueue PresentQueue;
};
