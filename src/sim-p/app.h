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
	static const uint32_t MAX_FRAMES_IN_FLIGHT = 2;
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
	void createImageViews();
	void createGraphicsPipeline();
	void createRenderPass();
	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createFrameBuffers();
	void createCommandBuffers();
	void createCommandPool();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	void drawFrame();
	void createSyncObjects();
	void recreateSwapChain();
	void cleanupSwapChain();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createVertexBuffer();
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void createIndexBuffer();
protected:
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
private:
	GLFWwindow* Window;
	VkInstance Instance;
	VkDebugUtilsMessengerEXT DebugMessenger;
	VkPhysicalDevice PhysicalDevice;
	VkDevice SelectedDevice;
	VkQueue GraphicsQueue;
	VkSurfaceKHR Surface;
	VkQueue PresentQueue;
	VkSwapchainKHR SwapChain;
	std::vector<VkImage> SwapChainImages;
	VkFormat SwapChainImageFormat;
	VkExtent2D SwapChainExtent;
	std::vector<VkImageView> SwapChainImageViews;
	VkPipelineLayout PipelineLayout;
	VkRenderPass RenderPass;
	VkPipeline GraphicsPipeline;
	std::vector<VkFramebuffer> SwapChainFramebuffers;
	VkCommandPool CommandPool;
	std::vector<VkCommandBuffer> CommandBuffer;
	std::vector<VkSemaphore> ImageAvailableSemaphore;
	std::vector<VkSemaphore> RenderFinishedSemaphore;
	std::vector<VkFence> InFlightFence;
	uint32_t CurrentFrame;
	bool FramebufferResized;
	VkBuffer VertexBuffer;
	VkDeviceMemory VertexBufferMemory;
	VkBuffer IndexBuffer;
	VkDeviceMemory IndexBufferMemory;
};
