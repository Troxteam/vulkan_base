#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <chrono>
#include <functional>
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "HashVertex.h"
#include "SwapChainSupportDetails.h"
#include "QueueFamilyIndices.h"
#include "UniformBufferObject.h"
#include "VDeleter.h"
#include "Vertex.h"

//Do not remove, currently broken without
#define USE_PLANE
#define USE_TESSELATION

class VulkanBase
{
public:
	VulkanBase();
	~VulkanBase();
	
	void run();

private:
	void initWindow();
	void initVulkan();
	void mainLoop();
	void createInstance();
	void setupDebugCallback();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createDescriptorSetLayout();
	void createComputeDescriptorSetLayout();
	void createGraphicsPipeline();
	void createComputePipeline();
	void createShaderModule(const std::vector<char>& code, VDeleter<VkShaderModule>& shaderModule);
	void createFramebuffers();
	void createCommandPool();
	void createVertexBuffer();
	void createCommandBuffers();
	void createSemaphores();
	void createBuffer(VkDeviceSize size,
		VkBufferUsageFlags usage,
		VkMemoryPropertyFlags properties,
		VDeleter<VkBuffer>& buffer,
		VDeleter<VkDeviceMemory>& bufferMemory);
	void createIndexBuffer();
	void createUniformBuffer();
	void createDescriptorPool();
	void createDescriptorSet();
	void createComputeDescriptorPool();
	void createComputeDescriptorSet();
	void createDepthResources();
	void createDisplacementImage();
	void createDisplacementImageView();
	void createDisplacementSampler();
	void createTextureImage();
	void createTextureImageView();
	void createTextureSampler();
	void createImage(uint32_t width, 
		uint32_t height,
		VkFormat format,
		VkImageTiling tiling,
		VkImageUsageFlags usage,
		VkMemoryPropertyFlags properties,
		VDeleter<VkImage>& image,
		VDeleter<VkDeviceMemory>& imageMemory);
	void createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VDeleter<VkImageView>& imageView);

	void recreateSwapChain();
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void updateUniformBuffer();
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyImage(VkImage srcImage, VkImage dstImage, uint32_t width, uint32_t height);
	void loadModel();

	bool checkValidationLayerSupport();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
	std::vector<const char*> getRequiredExtensions();
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData);
	VkResult CreateDebugReportCallbackExt(VkInstance instance,
		const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugReportCallbackEXT* pCallback);
	static void DestroyDebugReportCallbackEXT(VkInstance instance,
		VkDebugReportCallbackEXT callback,
		const VkAllocationCallbacks* pAllocator);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	static std::vector<char> readFile(const std::string& filename);
	void drawFrame();
	static void onWindowResized(GLFWwindow* window, int width, int height);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat();
	bool hasStencilComponent(VkFormat format);

	/*MEMBER VARIABLES*/
	const int WIDTH{ 1920 };
	const int HEIGHT{ 1080 };
#ifdef USE_PLANE
	const std::vector<std::string> MODEL_PATHS{ "data/models/plane.obj" };
	const std::string TEXTURE_PATH = "data/textures/bricks.jpg";
	const std::string DISPLACEMENT_PATH = "data/textures/bricks_h_128.jpg";
#else
	const std::vector<std::string> MODEL_PATHS = { "data/models/chalet.obj" };
	const std::string TEXTURE_PATH = "data/textures/chalet.jpg";
	const std::string DISPLACEMENT_PATH = "data/textures/bricks_h2.jpg";
#endif // USE_PLANE
	std::vector<Vertex> staticVertices{};
	std::vector<uint32_t> staticIndices{};
	GLFWwindow* window{};
	VDeleter<VkInstance> mInstance{ vkDestroyInstance };
	VDeleter<VkDebugReportCallbackEXT> callback{ mInstance, DestroyDebugReportCallbackEXT };
	VDeleter<VkDevice> device{ vkDestroyDevice };
	VDeleter<VkSurfaceKHR> surface{ mInstance, vkDestroySurfaceKHR };
	VDeleter<VkSwapchainKHR> swapChain{ device, vkDestroySwapchainKHR };
	std::vector<VDeleter<VkImageView>> swapChainImageViews{};
	VDeleter<VkDescriptorSetLayout> descriptorSetLayout{ device, vkDestroyDescriptorSetLayout };
	VDeleter<VkPipelineLayout> pipelineLayout{ device, vkDestroyPipelineLayout };
	VDeleter<VkRenderPass> renderPass{ device, vkDestroyRenderPass };
	VDeleter<VkPipeline> graphicsPipeline{ device, vkDestroyPipeline };
	std::vector<VDeleter<VkFramebuffer>> swapChainFramebuffers{};
	VDeleter<VkCommandPool> commandPool{ device, vkDestroyCommandPool };
	VDeleter<VkSemaphore> imageAvailableSemaphore{ device, vkDestroySemaphore };
	VDeleter<VkSemaphore> renderFinishesdSemaphore{ device, vkDestroySemaphore };
	VDeleter<VkImage> textureImage{ device, vkDestroyImage };
	VDeleter<VkDeviceMemory> textureImageMemory{ device, vkFreeMemory };
	VDeleter<VkBuffer> vertexBuffer{ device, vkDestroyBuffer };
	VDeleter<VkDeviceMemory> vertexBufferMemory{ device, vkFreeMemory };
	VDeleter<VkBuffer> indexBuffer{ device, vkDestroyBuffer };
	VDeleter<VkDeviceMemory> indexBufferMemory{ device, vkFreeMemory };
	VDeleter<VkBuffer> uniformStagingBuffer{ device, vkDestroyBuffer };
	VDeleter<VkDeviceMemory> uniformStagingBufferMemory{ device,  vkFreeMemory };
	VDeleter<VkBuffer> uniformBuffer{ device, vkDestroyBuffer };
	VDeleter<VkDeviceMemory> uniformBufferMemory{ device, vkFreeMemory };
	VDeleter<VkDescriptorPool> descriptorPool{ device, vkDestroyDescriptorPool };
	VDeleter<VkImage> displacementImage{ device, vkDestroyImage };
	VDeleter<VkDeviceMemory> displacementImageMemory{ device, vkFreeMemory };
	VDeleter<VkImageView> displacementImageView{ device, vkDestroyImageView };
	VDeleter<VkSampler> displacementSampler{ device, vkDestroySampler };
	VDeleter<VkImageView> textureImageView{ device, vkDestroyImageView };
	VDeleter<VkSampler> textureSampler{ device, vkDestroySampler };
	VDeleter<VkImage> depthImage{ device, vkDestroyImage };
	VDeleter<VkDeviceMemory> depthImageMemory{ device, vkFreeMemory };
	VDeleter<VkImageView> depthImageView{ device, vkDestroyImageView };
	VDeleter<VkBuffer> vertexStagingBuffer{ device, vkDestroyBuffer };
	VDeleter<VkDeviceMemory> vertexStagingBufferMemory{ device,  vkFreeMemory };
	VDeleter<VkBuffer> indexStagingBuffer{ device, vkDestroyBuffer };
	VDeleter<VkDeviceMemory> indexStagingBufferMemory{ device, vkFreeMemory };

	std::vector<VDeleter<VkPipeline>> computePipelines{};
	VDeleter<VkPipelineLayout> computePipelineLayout{ device, vkDestroyPipelineLayout };
	VkDescriptorSet computeDescriptorSet{};
	VDeleter<VkDescriptorSetLayout> computeDescriptorSetLayout{ device, vkDestroyDescriptorSetLayout };
	VDeleter<VkDescriptorPool> computeDescriptorPool{ device, vkDestroyDescriptorPool };
	VDeleter<VkCommandPool> computeCommandPool{ device, vkDestroyCommandPool };

	const std::vector<const char*> validationLayers { "VK_LAYER_LUNARG_standard_validation", "VK_LAYER_LUNARG_monitor" };
	const std::vector<const char*> deviceExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	VkPhysicalDevice physicalDevice{ VK_NULL_HANDLE };
	VkQueue graphicsQueue{};
	VkQueue presentQueue{};
	VkQueue computeQueue{};
	std::vector<VkImage> swapChainImages{};
	VkFormat swapChainImageFormat{};
	VkExtent2D swapChainExtent{};
	VkViewport viewport{};
	VkRect2D scissor{};
	std::vector<VkCommandBuffer> commandBuffers{};
	VkDescriptorSet descriptorSet{};

	UniformBufferObject ubo {};

};
