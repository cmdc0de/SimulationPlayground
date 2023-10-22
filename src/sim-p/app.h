#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

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
private:
    GLFWwindow* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
	 VkPhysicalDevice physicalDevice;
};
