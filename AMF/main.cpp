#include <dlfcn.h>
#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <AMF/components/Component.h>
#include "AMF/core/Platform.h"
#include "AMF/core/Result.h"
#include <AMF/core/Surface.h>
#include <AMF/core/Factory.h>
#include <AMF/core/Interface.h>
#include <AMF/core/Context.h>

#include <AMF/components/VideoEncoderVCE.h>
#include <AMF/components/VideoEncoderHEVC.h>
#include <AMF/components/VideoEncoderAV1.h>
#include <AMF/components/ComponentCaps.h>

uint32_t Width = 1280;
uint32_t Height = 720;

int main()
{
  amf_handle Handle = dlopen(AMF_DLL_NAMEA, RTLD_NOW);

  amf_uint64 Version;
  amf::AMFFactory* pFactory;
  amf::AMFContextPtr pContext;
  amf::AMFComponentPtr pEncoder;

  AMFQueryVersion_Fn QueryVersion = (AMFQueryVersion_Fn)dlsym(Handle, AMF_QUERY_VERSION_FUNCTION_NAME);
  AMFInit_Fn Init = (AMFInit_Fn)dlsym(Handle, AMF_INIT_FUNCTION_NAME);

  if(QueryVersion(&Version) != AMF_OK)
  {
    throw std::runtime_error("Failed to query versions");
  }

  if(Init(Version, &pFactory) != AMF_OK)
  {
    throw std::runtime_error("Failed to Init factory");
  }

  if(pFactory->CreateContext(&pContext) != AMF_OK)
  {
    throw std::runtime_error("failed to init context");
  }

  AMF_RESULT Res;
  if((Res = pFactory->CreateComponent(pContext, AMFVideoEncoderVCE_AVC, &pEncoder)) != AMF_OK)
  {
    throw std::runtime_error("Failed to create encoder: " + std::to_string(Res));
  }

  pEncoder->SetProperty(AMF_VIDEO_ENCODER_PROFILE, AMF_VIDEO_ENCODER_PROFILE_BASELINE);
  pEncoder->SetProperty(AMF_VIDEO_ENCODER_QUALITY_PRESET, AMF_VIDEO_ENCODER_QUALITY_PRESET_BALANCED);

  if(pEncoder->Init(amf::AMF_SURFACE_RGBA, Width, Height) != AMF_OK)
  {
    throw std::runtime_error("Failed to init encoder");
  }

  std::cout << "Success\n";
}

