#include <iostream>
#include <fstream>
#include <pstl/glue_execution_defs.h>
#include <vector>
#include <string>

#include <stdexcept>
#include <iomanip>
#include <bitset>

#include <fcntl.h>
#include <dlfcn.h>

#include <va/va.h>
#include <va/va_drm.h>
#include <va/va_x11.h>
#include <va/va_enc_h264.h>

int Width = 1920;
int Height = 1080;
int BitRate = 50000000;

std::string AttribString(int Var)
{
  switch(Var)
  {
    case VAConfigAttribRTFormat: return "VAConfigAttribRTFormat";
    case VAConfigAttribSpatialResidual: return "VAConfigAttribSpatialResidual";
    case VAConfigAttribSpatialClipping: return "VAConfigAttribSpatialClipping";
    case VAConfigAttribIntraResidual: return "VAConfigAttribIntraResidual";
    case VAConfigAttribEncryption: return "VAConfigAttribEncryption";
    case VAConfigAttribRateControl: return "VAConfigAttribRateControl";
    case VAConfigAttribDecSliceMode: return "VAConfigAttribDecSliceMode";
    case VAConfigAttribDecJPEG: return "VAConfigAttribDecJPEG";
    case VAConfigAttribDecProcessing: return "VAConfigAttribDecProcessing";
    case VAConfigAttribEncPackedHeaders: return "VAConfigAttribEncPackedHeaders";
    case VAConfigAttribEncInterlaced: return "VAConfigAttribEncInterlaced";
    case VAConfigAttribEncMaxRefFrames: return "VAConfigAttribEncMaxRefFrames";
    case VAConfigAttribEncMaxSlices: return "VAConfigAttribEncMaxSlices";
    case VAConfigAttribEncSliceStructure: return "VAConfigAttribEncSliceStructure";
    case VAConfigAttribEncMacroblockInfo: return "VAConfigAttribEncMacroblockInfo";
    case VAConfigAttribMaxPictureWidth: return "VAConfigAttribMaxPictureWidth";
    case VAConfigAttribMaxPictureHeight: return "VAConfigAttribMaxPictureHeight";
    case VAConfigAttribEncJPEG: return "VAConfigAttribEncJPEG";
    case VAConfigAttribEncQualityRange: return "VAConfigAttribEncQualityRange";
    case VAConfigAttribEncQuantization: return "VAConfigAttribEncQuantization";
    case VAConfigAttribEncIntraRefresh: return "VAConfigAttribEncIntraRefresh";
    case VAConfigAttribEncSkipFrame: return "VAConfigAttribEncSkipFrame";
    case VAConfigAttribEncROI: return "VAConfigAttribEncROI";
    case VAConfigAttribEncRateControlExt: return "VAConfigAttribEncRateControlExt";
    case VAConfigAttribProcessingRate: return "VAConfigAttribProcessingRate";
    case VAConfigAttribEncDirtyRect: return "VAConfigAttribEncDirtyRect";
    case VAConfigAttribEncParallelRateControl: return "VAConfigAttribEncParallelRateControl";
    case VAConfigAttribEncDynamicScaling: return "VAConfigAttribEncDynamicScaling";
    case VAConfigAttribFrameSizeToleranceSupport: return "VAConfigAttribFrameSizeToleranceSupport";
    case VAConfigAttribFEIFunctionType: return "VAConfigAttribFEIFunctionType";
    case VAConfigAttribFEIMVPredictors: return "VAConfigAttribFEIMVPredictors";
    case VAConfigAttribStats: return "VAConfigAttribStats";
    case VAConfigAttribEncTileSupport: return "VAConfigAttribEncTileSupport";
    case VAConfigAttribCustomRoundingControl: return "VAConfigAttribCustomRoundingControl";
    case VAConfigAttribQPBlockSize: return "VAConfigAttribQPBlockSize";
    case VAConfigAttribMaxFrameSize: return "VAConfigAttribMaxFrameSize";
    case VAConfigAttribPredictionDirection: return "VAConfigAttribPredictionDirection";
    case VAConfigAttribMultipleFrame: return "VAConfigAttribMultipleFrame";
    case VAConfigAttribContextPriority: return "VAConfigAttribContextPriority";
    case VAConfigAttribDecAV1Features: return "VAConfigAttribDecAV1Features";
    case VAConfigAttribTEEType: return "VAConfigAttribTEEType";
    case VAConfigAttribTEETypeClient: return "VAConfigAttribTEETypeClient";
    case VAConfigAttribProtectedContentCipherAlgorithm: return "VAConfigAttribProtectedContentCipherAlgorithm";
    case VAConfigAttribProtectedContentCipherBlockSize: return "VAConfigAttribProtectedContentCipherBlockSize";
    case VAConfigAttribProtectedContentCipherMode: return "VAConfigAttribProtectedContentCipherMode";
    case VAConfigAttribProtectedContentCipherSampleType: return "VAConfigAttribProtectedContentCipherSampleType";
    case VAConfigAttribProtectedContentUsage: return "VAConfigAttribProtectedContentUsage";
    case VAConfigAttribEncHEVCFeatures: return "VAConfigAttribEncHEVCFeatures";
    case VAConfigAttribEncHEVCBlockSizes: return "VAConfigAttribEncHEVCBlockSizes";
    case VAConfigAttribEncAV1: return "VAConfigAttribEncAV1";
    case VAConfigAttribEncAV1Ext1: return "VAConfigAttribEncAV1Ext1";
    case VAConfigAttribEncAV1Ext2: return "VAConfigAttribEncAV1Ext2";
    case VAConfigAttribEncPerBlockControl: return "VAConfigAttribEncPerBlockControl";
  }

  return "";
}

std::string ProfString(int Var)
{
  switch(Var)
  {
    case VAProfileNone: return "VAProfileNone";
    case VAProfileMPEG2Simple: return "VAProfileMPEG2Simple";
    case VAProfileMPEG2Main: return "VAProfileMPEG2Main";
    case VAProfileMPEG4Simple: return "VAProfileMPEG4Simple";
    case VAProfileMPEG4AdvancedSimple: return "VAProfileMPEG4AdvancedSimple";
    case VAProfileMPEG4Main: return "VAProfileMPEG4Main";
    case VAProfileH264Baseline: return "VAProfileH264Baseline va_deprecated_enum";
    case VAProfileH264Main: return "VAProfileH264Main";
    case VAProfileH264High: return "VAProfileH264High";
    case VAProfileVC1Simple: return "VAProfileVC1Simple";
    case VAProfileVC1Main: return "VAProfileVC1Main";
    case VAProfileVC1Advanced: return "VAProfileVC1Advanced";
    case VAProfileH263Baseline: return "VAProfileH263Baseline";
    case VAProfileJPEGBaseline: return "VAProfileJPEGBaseline";
    case VAProfileH264ConstrainedBaseline: return "VAProfileH264ConstrainedBaseline";
    case VAProfileVP8Version0_3: return "VAProfileVP8Version0_3";
    case VAProfileH264MultiviewHigh: return "VAProfileH264MultiviewHigh";
    case VAProfileH264StereoHigh: return "VAProfileH264StereoHigh";
    case VAProfileHEVCMain: return "VAProfileHEVCMain";
    case VAProfileHEVCMain10: return "VAProfileHEVCMain10";
    case VAProfileVP9Profile0: return "VAProfileVP9Profile0";
    case VAProfileVP9Profile1: return "VAProfileVP9Profile1";
    case VAProfileVP9Profile2: return "VAProfileVP9Profile2";
    case VAProfileVP9Profile3: return "VAProfileVP9Profile3";
    case VAProfileHEVCMain12: return "VAProfileHEVCMain12";
    case VAProfileHEVCMain422_10: return "VAProfileHEVCMain422_10";
    case VAProfileHEVCMain422_12: return "VAProfileHEVCMain422_12";
    case VAProfileHEVCMain444: return "VAProfileHEVCMain444";
    case VAProfileHEVCMain444_10: return "VAProfileHEVCMain444_10";
    case VAProfileHEVCMain444_12: return "VAProfileHEVCMain444_12";
    case VAProfileHEVCSccMain: return "VAProfileHEVCSccMain";
    case VAProfileHEVCSccMain10: return "VAProfileHEVCSccMain10";
    case VAProfileHEVCSccMain444: return "VAProfileHEVCSccMain444";
    case VAProfileAV1Profile0: return "VAProfileAV1Profile0";
    case VAProfileAV1Profile1: return "VAProfileAV1Profile1";
    case VAProfileHEVCSccMain444_10: return "VAProfileHEVCSccMain444_10";
    case VAProfileProtected: return "VAProfileProtected";
    case VAProfileH264High10: return "VAProfileH264High10";
  }
  return "Error Prof";
}

std::string EPString(int Var)
{
  switch(Var)
  {
    case VAEntrypointVLD: return "VAEntrypointVLD";
    case VAEntrypointIZZ: return "VAEntrypointIZZ";
    case VAEntrypointIDCT: return "VAEntrypointIDCT";
    case VAEntrypointMoComp: return "VAEntrypointMoComp";
    case VAEntrypointDeblocking: return "VAEntrypointDeblocking";
    case VAEntrypointEncSlice: return "VAEntrypointEncSlice";
    case VAEntrypointEncPicture: return "VAEntrypointEncPicture";
    case VAEntrypointEncSliceLP: return "VAEntrypointEncSliceLP";
    case VAEntrypointVideoProc: return "VAEntrypointVideoProc";
    case VAEntrypointFEI: return "VAEntrypointFEI";
    case VAEntrypointStats: return "VAEntrypointStats";
    case VAEntrypointProtectedTEEComm: return "VAEntrypointProtectedTEEComm";
    case VAEntrypointProtectedContent: return "VAEntrypointProtectedContent";
  }

  return "Error";
}

int main()
{
  VADisplay MainDisplay;
  VAConfigID ConfId;
  VAContextID EncContext;
  VAProfile Profile;
  VAEntrypoint EntryPoint;

  VABufferID SeqPBuffer;

  int DRM = open("/dev/dri/renderD128", O_RDWR);

  MainDisplay = vaGetDisplayDRM(DRM);

  VAStatus Res;
  int Minor, Major;

  if((Res = vaInitialize(MainDisplay, &Major, &Minor)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to Initiate libVA (VA-API)" + std::to_string(Res));
  }

  std::cout << "Major: " << Major << '\n';
  std::cout << "Minor: " << Minor << '\n';

  int ProfileCount;
  VAProfile* Profiles = new VAProfile[vaMaxNumProfiles(MainDisplay)]; // small inline here where we Get the largest number of profiles we could have and just make an array of that size. So that we don't have to worry about overflow
  vaQueryConfigProfiles(MainDisplay, Profiles, &ProfileCount);

  for(uint32_t i = 0; i < ProfileCount; i++)
  {
    if(Profiles[i] == VAProfileH264High || Profiles[i] == VAProfileH264Main)
    {
      int EntryPointCount;
      VAEntrypoint* EntryPoints = new VAEntrypoint[vaMaxNumEntrypoints(MainDisplay)];
      vaQueryConfigEntrypoints(MainDisplay, Profiles[i], EntryPoints, &EntryPointCount);

      for(uint32_t x = 0; x < EntryPointCount; x++)
      {
        if(EntryPoints[x] == VAEntrypointEncSlice)
        {
          Profile = Profiles[i];
          EntryPoint = EntryPoints[x];
          delete[] EntryPoints;
          break;
        }
      }
    }
  }

  delete[] Profiles;

  std::cout << "Chose " << ProfString(Profile) << " Profile with " << EPString(EntryPoint) << " EntryPoint\n";

  std::vector<VAConfigAttrib> AvConfigAttrib(VAConfigAttribTypeMax);
  std::vector<VAConfigAttrib> InConfigAttrib;

  for(int i = 0; i < AvConfigAttrib.size(); i++)
  {
    AvConfigAttrib[i].type = VAConfigAttribType(i);
    
  }

  vaGetConfigAttributes(MainDisplay, Profile, EntryPoint, AvConfigAttrib.data(), AvConfigAttrib.size());

// print defaults for config attribs
  for(uint32_t i = 0; i < AvConfigAttrib.size(); i++)
  {
    if(AvConfigAttrib[i].value != VA_ATTRIB_NOT_SUPPORTED)
    {
      std::cout << AttribString(AvConfigAttrib[i].type) << " : " << AvConfigAttrib[i].value << '\n';
    }
  }

// cleanup config attributes. (remove unsupported)
  for(uint32_t i = 0; i < AvConfigAttrib.size(); i++)
  {
    if(AvConfigAttrib[i].value == VA_ATTRIB_NOT_SUPPORTED)
    {
      AvConfigAttrib.erase(AvConfigAttrib.begin() + i);
    }
  }

// get render target format
  if(AvConfigAttrib[VAConfigAttribRTFormat].value & VA_RT_FORMAT_YUV420)
  {
    InConfigAttrib.push_back({VAConfigAttribRTFormat, VA_RT_FORMAT_YUV420});
  }
  else
  {
    throw std::runtime_error("Failed, RGBP is not a supported Format for this profile/Entrypoint combo.");
  }

// set the rate control method
  if(AvConfigAttrib[VAConfigAttribRateControl].value != VA_ATTRIB_NOT_SUPPORTED)
  {
    int RateCtrl = AvConfigAttrib[VAConfigAttribRateControl].value;

    if(RateCtrl & VA_RC_VBR)
    {
      InConfigAttrib.push_back({VAConfigAttribRateControl, VA_RC_VBR});
    }
    else if(RateCtrl & VA_RC_CBR)
    {
      InConfigAttrib.push_back({VAConfigAttribRateControl, VA_RC_CBR});
    }
    else if(RateCtrl & VA_RC_CQP)
    {
      InConfigAttrib.push_back({VAConfigAttribRateControl, VA_RC_CQP});
    }
  }

  if(AvConfigAttrib[VAConfigAttribEncInterlaced].value != VA_ATTRIB_NOT_SUPPORTED)
  {
    InConfigAttrib.push_back({VAConfigAttribEncInterlaced, VA_ENC_PACKED_HEADER_NONE});
  }

  if((Res = vaCreateConfig(MainDisplay, Profile, EntryPoint, InConfigAttrib.data(), InConfigAttrib.size(), &ConfId)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to create Encoder config with error " + std::to_string(Res));
  }

  std::vector<VASurfaceID> Surfaces(2);

  if((Res = vaCreateSurfaces(MainDisplay, VA_RT_FORMAT_YUV420, Width, Height, Surfaces.data(), Surfaces.size(), NULL, 0)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to create Surfaces with error " + std::to_string(Res));
  }

  if((Res = vaCreateContext(MainDisplay, ConfId, Width, Height, VA_PROGRESSIVE, Surfaces.data(), Surfaces.size(), &EncContext)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to create encoder context with error " + std::to_string(Res));
  }

  // this structure wraps the SPS sequence parameter set. It's a small object that feeds the AVC Encoder information about input and output, as well as Algo info as well.
  VAEncSequenceParameterBufferH264 SequenceParams;
  // Baseline Profile level 3.0 :  30
  // Main Profile Level 4.0 :      40
  // High Profile Level 4.1 :      41
  SequenceParams.level_idc = (Profile == VAProfileH264Main) ? 40 : (Profile == VAProfileH264High) ? 41 : 0;
  SequenceParams.picture_width_in_mbs = (Width + 15) / 16;
  SequenceParams.picture_height_in_mbs = (Height + 15) / 16;
  SequenceParams.max_num_ref_frames = 4;

  SequenceParams.bits_per_second = BitRate;

  VAEncSliceParameterBufferH264 SliceParams;

  if((Res = vaCreateBuffer(MainDisplay, EncContext, VAEncSequenceParameterBufferType, sizeof(SequenceParams), 1, &SequenceParams, &SeqPBuffer)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to create sequence parameter buffer with error " + std::to_string(Res));
  }

  std::cout << "Successful run complete\n";

  vaDestroyContext(MainDisplay, EncContext);
  vaDestroyConfig(MainDisplay, ConfId);
  vaTerminate(MainDisplay);

  // To get the value of an attribute of type VAConfigAttribX X being the type of Attribute you want to retrieve.

  return 0;
}

