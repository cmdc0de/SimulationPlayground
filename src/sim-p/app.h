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
private:
    GLFWwindow* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
};
