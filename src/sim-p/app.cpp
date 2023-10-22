#include "app.h"
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <map>

const uint32_t WIDTH = 1024;
const uint32_t HEIGHT = 768;

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback([[maybe_unused]] VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity
		, [[maybe_unused]]VkDebugUtilsMessageTypeFlagsEXT messageType
		, [[maybe_unused]] const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, [[maybe_unused]] void* pUserData) {
	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
	return VK_FALSE;
}

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo
		, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger
		, const VkAllocationCallbacks* pAllocator) {
    auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}



App::App(): window(nullptr), instance(0), debugMessenger(), physicalDevice(VK_NULL_HANDLE) {

}

void App::initVulkan() {
	createInstance();
	setupDebugMessenger();
	pickPhysicalDevice();
}

void App::createInstance() {
	if (enableValidationLayers && !checkValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Sim Playground";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "bdcacb";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = 0;
	
	std::vector<const char*> extensions;
	getRequiredExtensions(extensions);
	std::vector<VkExtensionProperties> allExtensions;
	getAllExtensions(allExtensions);

	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();

		populateDebugMessengerCreateInfo(debugCreateInfo);
		//createInfo.pNext = reinterpret_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&debugCreateInfo);
		createInfo.pNext = &debugCreateInfo;
	} else {
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
	}

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
	
}

void App::run() {
   initWindow();
   initVulkan();
   mainLoop();
   cleanUp();
}

void App::initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void App::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}


void App::cleanUp() {
	if (enableValidationLayers) {
		DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	}

	vkDestroyInstance(instance, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
}


void App::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
}


void App::setupDebugMessenger() {
	if (!enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	populateDebugMessengerCreateInfo(createInfo);

	if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug messenger!");
	}
}

void App::getRequiredExtensions(std::vector<const char*> &extensions) {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	printf("Extensions: %u\n", glfwExtensionCount);
	for(uint32_t i = 0;i<glfwExtensionCount;++i) {
		printf("%s\n",glfwExtensions[i]);
		extensions.push_back(glfwExtensions[i]);
	}

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}
}
	
void App::getAllExtensions([[maybe_unused]] std::vector<VkExtensionProperties> &all) {
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	//allExtensions.reserve(extensionCount+1);
	std::vector<VkExtensionProperties> allExtensions(extensionCount);


	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, allExtensions.data());

	std::cout << "ALL available extensions: " << extensionCount << "\n";
	//for (const auto& props : allExtensions) {
	for(uint32_t i=0;i<extensionCount;++i) {
		std::cout << '\t' << allExtensions[i].extensionName << " spec version: " << allExtensions[i].specVersion << std::endl;
	}
	std::cout << "extensions complete" << std::endl;

}

bool App::checkValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

void App::logFeatures(VkPhysicalDeviceFeatures &f) {
	printf("feature List: \nrobustBufferAccess: %d\n", f.robustBufferAccess);
	printf("fullDrawIndexUint32: %d\n", f.fullDrawIndexUint32);
   printf("imageCubeArray: %d\n", f.imageCubeArray);
   printf("indetendentBlend: %d\n", f.independentBlend);
   printf("geometryShader: %d\n", f.geometryShader);
   printf("tessellationShader: %d\n", f.tessellationShader);
   printf("sampleRateShading: %d\n", f.sampleRateShading);
   printf("dualSrcBlend: %d\n", f.dualSrcBlend);
   printf("logicOp: %d\n", f.logicOp);
   printf("multiDrawIndirect: %d\n", f.multiDrawIndirect);
   printf("drawIndirectFirstInstance: %d\n", f.drawIndirectFirstInstance);
   printf("depthClamp: %d\n", f.depthClamp);
   printf("depthBiasClamp: %d\n", f.depthBiasClamp);
   printf("fillModeNonSolid: %d\n", f.fillModeNonSolid);
   printf("depthBounds: %d\n", f.depthBounds);
   printf("wideLines: %d\n", f.wideLines);
   printf("largePoints: %d\n", f.largePoints);
   printf("alphaToOne: %d\n", f.alphaToOne);
   printf("multiViewport: %d\n", f.multiViewport);
   printf("samplerAnisotropy: %d\n", f.samplerAnisotropy);
   printf("textureCompressionETC2: %d\n", f.textureCompressionETC2);
   printf("textureCompressionASTC_LDR: %d\n", f.textureCompressionASTC_LDR);
   printf("textureCompressionBC: %d\n", f.textureCompressionBC);
   printf("occlusionQueryPrecise; %d\n", f.occlusionQueryPrecise);
   printf("pipelineStatisticsQuery; %d\n", f.pipelineStatisticsQuery);
   printf("vertexPipelineStoresAndAtomics; %d\n", f.vertexPipelineStoresAndAtomics);
   printf("fragmentStoresAndAtomics; %d\n", f.fragmentStoresAndAtomics);
   printf("shaderTessellationAndGeometryPointSize; %d\n", f.shaderTessellationAndGeometryPointSize);
   printf("shaderImageGatherExtended; %d\n", f.shaderImageGatherExtended);
   printf("shaderStorageImageExtendedFormats; %d\n", f.shaderStorageImageExtendedFormats);
   printf("shaderStorageImageMultisample; %d\n", f.shaderStorageImageMultisample);
   printf("shaderStorageImageReadWithoutFormat; %d\n", f.shaderStorageImageReadWithoutFormat);
   printf("shaderStorageImageWriteWithoutFormat; %d\n", f.shaderStorageImageWriteWithoutFormat);
   printf("shaderUniformBufferArrayDynamicIndexing; %d\n", f.shaderUniformBufferArrayDynamicIndexing);
   printf("shaderSampledImageArrayDynamicIndexing; %d\n", f.shaderSampledImageArrayDynamicIndexing);
   printf("shaderStorageBufferArrayDynamicIndexing; %d\n", f.shaderStorageBufferArrayDynamicIndexing);
   printf("shaderStorageImageArrayDynamicIndexing; %d\n", f.shaderStorageImageArrayDynamicIndexing);
   printf("shaderClipDistance; %d\n", f.shaderClipDistance);
   printf("shaderCullDistance; %d\n", f.shaderCullDistance);
   printf("shaderFloat64; %d\n", f.shaderFloat64);
   printf("shaderInt64; %d\n", f.shaderInt64);
   printf("shaderInt16; %d\n", f.shaderInt16);
   printf("shaderResourceResidency; %d\n", f.shaderResourceResidency);
   printf("shaderResourceMinLod; %d\n", f.shaderResourceMinLod);
   printf("sparseBinding; %d\n", f.sparseBinding);
   printf("sparseResidencyBuffer; %d\n", f.sparseResidencyBuffer);
   printf("sparseResidencyImage2D; %d\n", f.sparseResidencyImage2D);
   printf("sparseResidencyImage3D; %d\n", f.sparseResidencyImage3D);
   printf("sparseResidency2Samples; %d\n", f.sparseResidency2Samples);
   printf("sparseResidency4Samples; %d\n", f.sparseResidency4Samples);
   printf("sparseResidency8Samples; %d\n", f.sparseResidency8Samples);
   printf("sparseResidency16Samples; %d\n", f.sparseResidency16Samples);
   printf("sparseResidencyAliased; %d\n", f.sparseResidencyAliased);
   printf("variableMultisampleRate; %d\n", f.variableMultisampleRate);
   printf("inheritedQueries; %d\n", f.inheritedQueries);
}

bool App::isDeviceSuitable(const VkPhysicalDevice &device) {
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	logFeatures(deviceFeatures);

	return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;// && deviceFeatures.geometryShader;
}

void App::pickPhysicalDevice() {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}
	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
	std::multimap<int, VkPhysicalDevice> candidates;

	for (const auto& device : devices) {
		if (isDeviceSuitable(device)) {
			uint32_t score = rateDevice(device);
			candidates.insert(std::make_pair(score, device));
			break;
		}
	}

	// Check if the best candidate is suitable at all
	if (candidates.rbegin()->first > 0) {
		physicalDevice = candidates.rbegin()->second;
	} else {
		throw std::runtime_error("failed to find a suitable GPU!");
	}

	if (physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
}

uint32_t App::rateDevice(const VkPhysicalDevice &device) {
	uint32_t score = 0;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	// Discrete GPUs have a significant performance advantage
	if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		score += 1000;
	}

	// Maximum possible size of textures affects graphics quality
	score += deviceProperties.limits.maxImageDimension2D;

	// Application can't function without geometry shaders
	if (!deviceFeatures.geometryShader) {
		return 0;
	}
	return score;
}


