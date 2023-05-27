#include <iostream>
#include <string>
#include <vector>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

struct VulkanData
{
  public:
    VkInstance Instance;
    VkPhysicalDevice PDev;
    VkDevice Device;

    uint32_t ComputeFam;
    VkQueue ComputeQueue;

    VkCommandPool Pool;
    VkCommandBuffer PrimBuff;
};

VulkanData* Dat;

std::vector<const char*> InstLayers = {"VK_LAYER_KHRONOS_validation"};

void InitBase()
{
  VkInstanceCreateInfo InstCI{};
  InstCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  InstCI.enabledLayerCount = InstLayers.size();
  InstCI.ppEnabledLayerNames = InstLayers.data();

  if(vkCreateInstance(&InstCI, nullptr, &Dat->Instance) != VK_SUCCESS)
  {
    throw std::runtime_error("Failed to create instance");
  }

  uint32_t PDevCount;
  vkEnumeratePhysicalDevices(Dat->Instance, &PDevCount, nullptr);
  std::vector<VkPhysicalDevice> PDevices(PDevCount);
  vkEnumeratePhysicalDevices(Dat->Instance, &PDevCount, PDevices.data());

  for(uint32_t i = 0; i < PDevCount; i++)
  {
    VkPhysicalDeviceProperties DevProps;
    vkGetPhysicalDeviceProperties(PDevices[i], &DevProps);
    if(DevProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
      Dat->PDev = PDevices[i];
      break;
    }
  }

  uint32_t FamCount;
  vkGetPhysicalDeviceQueueFamilyProperties(Dat->PDev, &FamCount, nullptr);
  std::vector<VkQueueFamilyProperties> FamProps(FamCount);
  vkGetPhysicalDeviceQueueFamilyProperties(Dat->PDev, &FamCount, FamProps.data());

  for(uint32_t i = 0; i < FamCount; i++)
  {
    if(FamProps[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
    {
      Dat->ComputeFam = i;
      break;
    }
  }

  VkDeviceQueueCreateInfo ComCI{};
  ComCI.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  ComCI.queueCount = 1;
  ComCI.queueFamilyIndex = Dat->ComputeFam;

  VkDeviceCreateInfo DevCI{};
  DevCI.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  DevCI.queueCreateInfoCount = 1;
  DevCI.pQueueCreateInfos = &ComCI;

  if(vkCreateDevice(Dat->PDev, &DevCI, nullptr, &Dat->Device) != VK_SUCCESS)
  {
    throw std::runtime_error("Failed to create vulkan device");
  }

  vkGetDeviceQueue(Dat->Device, Dat->ComputeFam, 0, &Dat->ComputeQueue);
}

void InitCommands()
{
  VkCommandPoolCreateInfo PoolCI{};
  PoolCI.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  PoolCI.queueFamilyIndex = Dat->ComputeFam;

  if(vkCreateCommandPool(Dat->Device, &PoolCI, nullptr, &Dat->Pool) != VK_SUCCESS)
  {
    throw std::runtime_error("Failed to create pool");
  }

  VkCommandBufferAllocateInfo CmdAlloc{};
  CmdAlloc.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  CmdAlloc.commandPool = Dat->Pool;
  CmdAlloc.commandBufferCount = 1;
  CmdAlloc.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

  if(vkAllocateCommandBuffers(Dat->Device, &CmdAlloc, &Dat->PrimBuff) != VK_SUCCESS)
  {
    throw std::runtime_error("Failed to allocate command buffers");
  }
}

void InitCompute()
{
}

int main()
{
  Dat = new VulkanData();
  InitBase();
  InitCommands();

  std::cout << "Success\n";
  return 0;
}
