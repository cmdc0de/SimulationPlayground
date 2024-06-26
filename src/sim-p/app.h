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
	void createDescriptorSetLayout();
	void createUniformBuffers();
	void createDescriptorSets();
	void createDescriptorPool();
	void updateUniformBuffer(uint32_t currentFrame);
	void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling
			, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void createTextureImage();
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
	void createTextureImageView();
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	void createTextureSampler();
	void createDepthResources();
	bool hasStencilComponent(VkFormat format);
	VkFormat findDepthFormat();
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	void loadModel();
	void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
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
	VkDescriptorSetLayout DescriptorSetLayout;
	std::vector<VkBuffer> UniformBuffers;
	std::vector<VkDeviceMemory> UniformBuffersMemory;
	std::vector<void*> UniformBuffersMapped;
	VkDescriptorPool DescriptorPool;
	std::vector<VkDescriptorSet> DescriptorSets;
	VkImage TextureImage;
	VkDeviceMemory TextureImageMemory;
	VkImageView TextureImageView;
	VkSampler TextureSampler;
	VkImage DepthImage;
	VkDeviceMemory DepthImageMemory;
	VkImageView DepthImageView;
	uint32_t MipLevels;

};
