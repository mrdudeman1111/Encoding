#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <va/va.h>
#include <va/va_drm.h>
#include <va/va_enc_h264.h>

int main()
{
  VAProfile Profile;
  VAEntrypoint EntryPoint;
  VADisplay MainDisplay;
  VAConfigID ConfID;
  VAStatus Res;

  int DRM = open("/dev/dri/renderD128", O_RDWR);
  MainDisplay = vaGetDisplayDRM(DRM);

  int Minor, Major;

  if((Res = vaInitialize(MainDisplay, &Major, &Minor)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to initialize VA-API with error: " + std::to_string(Res));
  }
  else
  {
    std::cout << "Initialized VA API with Major version: " << Major << " and Minor version: " << Minor << '\n';
  }

  int ProfileCount;
  VAProfile* AvProfiles = new VAProfile[vaMaxNumProfiles(MainDisplay)];

  vaQueryConfigProfiles(MainDisplay, AvProfiles, &ProfileCount);

  for(uint32_t i = 0; i < ProfileCount; i++)
  {
    if(AvProfiles[i] == VAProfileH264High || AvProfiles[i] == VAProfileH264Main)
    {
      int EntryPointCount;
      VAEntrypoint* EntryPoints = new VAEntrypoint[vaMaxNumEntrypoints(MainDisplay)];
      vaQueryConfigEntrypoints(MainDisplay, AvProfiles[i], EntryPoints, &EntryPointCount);

      for(uint32_t x = 0; x < EntryPointCount; x++)
      {
        if(EntryPoints[x] == VAEntrypointEncSlice)
        {
          Profile = AvProfiles[i];
          EntryPoint = EntryPoints[x];
          delete[] EntryPoints;
          break;
        }
      }
    }
  }

  delete[] AvProfiles;

  VAConfigAttrib AvAttribs[2];
  VAConfigAttrib InAttribs[2];

  AvAttribs[0].type = VAConfigAttribRTFormat;
  AvAttribs[1].type = VAConfigAttribRateControl;

  vaGetConfigAttributes(MainDisplay, Profile, EntryPoint, AvAttribs, 2);

  if(AvAttribs[0].value & VA_RT_FORMAT_YUV420)
  {
    InAttribs[0].type = VAConfigAttribRTFormat;
    InAttribs[0].value = VA_RT_FORMAT_YUV420;
  }

  uint32_t RCMethod = AvAttribs[1].value;

  if(RCMethod & VA_RC_CBR)
  {
    InAttribs[1].value = VA_RC_CBR;
  }
  else if(RCMethod & VA_RC_VBR)
  {
    InAttribs[1].value = VA_RC_VBR;
  }
  else if(RCMethod & VA_RC_ICQ)
  {
    InAttribs[1].value = VA_RC_ICQ;
  }

  if((Res = vaCreateConfig(MainDisplay, Profile, EntryPoint, InAttribs, 2, &ConfID)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to create config for VA API with error: " + std::to_string(Res));
  }


  int Width, Height, Channels;
  uint8_t* Pixels = stbi_load("Texture.jpg", &Width, &Height, &Channels, STBI_rgb);

  if(Channels != 3)
  {
    throw std::runtime_error("failed to load image with 3 channels");
  }


  VASurfaceID inSurface;
  VAImage SurfaceImage;

  VABufferID outBuffer;

  if((Res = vaCreateSurfaces(MainDisplay, VA_RT_FORMAT_YUV420, Width, Height, &inSurface, 1, NULL, 0)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to allocate input surfaces with error " + std::to_string(Res));
  }

  // InAttribs[0] is our VA_RT_FORMAT attribute
  VAImageFormat Format;
  Format.fourcc = VA_FOURCC_I420;
  Format.byte_order = VA_LSB_FIRST;
  Format.bits_per_pixel = 16;

  vaCreateImage(MainDisplay, VAImageFormat *format, int width, int height, VAImage *image);
  if((Res = vaGetImage(MainDisplay, inSurface, 0, 0, (unsigned int)Width, (unsigned int)Height, SurfaceImage.image_id)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to get image with error: " + std::to_string(Res));
  }

  void* inSurfaceMemory;
  vaMapBuffer(MainDisplay, SurfaceImage.buf, &inSurfaceMemory);
  vaUnmapBuffer(MainDisplay, SurfaceImage.buf);

  std::cout << "Success\n";
}

