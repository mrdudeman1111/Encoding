#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>

#include <va/va.h>
#include <va/va_drm.h>

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

void PrintAvFormats(int Frm)
{
  if(Frm & VA_RT_FORMAT_YUV420)
  {
    std::cout << "    YUV420\n";
  }
  if(Frm & VA_RT_FORMAT_YUV422)
  {
    std::cout << "    YUV422\n";
  }
  if(Frm & VA_RT_FORMAT_RGB32)
  {
    std::cout << "    RGB32\n";
  }
  if(Frm & VA_RT_FORMAT_RGBP)
  {
    std::cout << "    RGBP\n";
  }
  if(Frm & VA_RT_FORMAT_RGB16)
  {
    std::cout << "    RGB16\n";
  }
  if(Frm & VA_RT_FORMAT_YUV400)
  {
    std::cout << "    YUV400\n";
  }
  if(Frm & VA_RT_FORMAT_YUV444)
  {
    std::cout << "    YUV444\n";
  }
  if(Frm & VA_RT_FORMAT_YUV411)
  {
    std::cout << "    YUV411\n";
  }
}

int main()
{
  int drmHandle = open("/dev/dri/renderD128", O_RDWR);
  VADisplay MainDisplay = vaGetDisplayDRM(drmHandle);

  VAStatus Res;
  int Major, Minor;

  if((Res = vaInitialize(MainDisplay, &Major, &Minor)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to Initate libva or VAAPI with error: " + std::to_string(Res));
  }

  int ProfileCount;
  VAProfile* Profiles = new VAProfile[vaMaxNumProfiles(MainDisplay)];
  vaQueryConfigProfiles(MainDisplay, Profiles, &ProfileCount);

  for(uint32_t i = 0; i < ProfileCount; i++)
  {
    int EntryPointCount;
    VAEntrypoint* EntryPoints = new VAEntrypoint[vaMaxNumEntrypoints(MainDisplay)];
    vaQueryConfigEntrypoints(MainDisplay, Profiles[i], EntryPoints, &EntryPointCount);

    std::cout << ProfString(Profiles[i]) << '\n';

    for(uint32_t x = 0; x < EntryPointCount; x++)
    {
      std::cout << "  " << EPString(EntryPoints[x]) << '\n';

      VAConfigAttrib FrmAtt;
      FrmAtt.type = VAConfigAttribRTFormat;

      vaGetConfigAttributes(MainDisplay, Profiles[i], EntryPoints[x], &FrmAtt, 1);

      PrintAvFormats(FrmAtt.value);
    }
  }

  return 0;
}

