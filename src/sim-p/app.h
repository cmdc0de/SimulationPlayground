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

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
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
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void querySwapChainSupport(VkPhysicalDevice device, SwapChainSupportDetails &scsd);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();
private:
    GLFWwindow* Window;
    VkInstance Instance;
    VkDebugUtilsMessengerEXT debugMessenger;
	 VkPhysicalDevice PhysicalDevice;
	 VkDevice SelectedDevice;
	 VkQueue GraphicsQueue;
	 VkSurfaceKHR Surface;
	 VkQueue PresentQueue;
	 VkSwapchainKHR SwapChain;
	 std::vector<VkImage> SwapChainImages;
	 VkFormat SwapChainImageFormat;
    VkExtent2D SwapChainExtent;
};
