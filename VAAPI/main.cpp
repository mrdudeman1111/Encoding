#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <stdexcept>
#include <iomanip>
#include <bitset>

#include <fcntl.h>
#include <dlfcn.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <va/va.h>
#include <va/va_drm.h>
#include <va/va_x11.h>
#include <va/va_enc_h264.h>

int Width = 1920;
int Height = 1080;
int BitRate = 50000000;
FILE* outFile;

#define NAL_REF_IDC_NONE        0
#define NAL_REF_IDC_LOW         1
#define NAL_REF_IDC_MEDIUM      2
#define NAL_REF_IDC_HIGH        3

#define NAL_NON_IDR             1
#define NAL_IDR                 5
#define NAL_SPS                 7
#define NAL_PPS                 8
#define NAL_SEI                 6
#define NAL_DELIMITER           9


#define SLICE_TYPE_P            0
#define SLICE_TYPE_B            1
#define SLICE_TYPE_I            2

#define FRAME_IDR 7

#define ENTROPY_MODE_CAVLC      0
#define ENTROPY_MODE_CABAC      1

#define PROFILE_IDC_BASELINE    66
#define PROFILE_IDC_MAIN        77
#define PROFILE_IDC_HIGH        100

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

void FillSurface(VADisplay* Display, VASurfaceID* Surface)
{
  int Width, Height, Channels;
  stbi_load("input.jpg", &Width, &Height, &Channels, STBI_rgb);

  VAImage DstImage;

  vaDeriveImage(*Display, *Surface, &DstImage);

  void* SurfaceMemory;
  vaMapBuffer(*Display, DstImage.buf, &SurfaceMemory);

  void* Mem;
  vaMapBuffer(*Display, *Surface, &Mem);
}

int main()
{
  VADisplay MainDisplay;
  VAConfigID ConfId;
  VAContextID EncContext;
  VAProfile Profile;
  VAEntrypoint EntryPoint;

  /* Setup output file */
  outFile = fopen("Output.mp4", "wb");

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

  std::vector<VAConfigAttrib> AvConfigAttrib(2);
  std::vector<VAConfigAttrib> InConfigAttrib;

  AvConfigAttrib[0].type = VAConfigAttribRTFormat;
  AvConfigAttrib[1].type = VAConfigAttribRateControl;

  vaGetConfigAttributes(MainDisplay, Profile, EntryPoint, AvConfigAttrib.data(), AvConfigAttrib.size());

// print defaults for config attribs
  for(uint32_t i = 0; i < AvConfigAttrib.size(); i++)
  {
    if(AvConfigAttrib[i].value != VA_ATTRIB_NOT_SUPPORTED)
    {
      std::cout << AttribString(AvConfigAttrib[i].type) << " : " << AvConfigAttrib[i].value << '\n';
    }
  }

// get render target format
  if(AvConfigAttrib[VAConfigAttribRTFormat].value & VA_RT_FORMAT_YUV420)
  {
    InConfigAttrib.push_back({VAConfigAttribRTFormat, VA_RT_FORMAT_YUV420});
  }
  else
  {
    throw std::runtime_error("Failed, YUV420 is not a supported Format for this profile/Entrypoint combo.");
  }

// set the rate control method
  uint32_t RateCtrl = AvConfigAttrib[VAConfigAttribRateControl].value;

  if(RateCtrl & VA_RC_VBR) // variable bit rate
  {
    InConfigAttrib.push_back({VAConfigAttribRateControl, VA_RC_VBR});
  }
  else if(RateCtrl & VA_RC_CBR) // constant bit rate
  {
    InConfigAttrib.push_back({VAConfigAttribRateControl, VA_RC_CBR});
  }
  else if(RateCtrl & VA_RC_CQP) // constant QP value. (more strict version of CBR)
  {
    InConfigAttrib.push_back({VAConfigAttribRateControl, VA_RC_CQP});
  }
  else
  {
    throw std::runtime_error("no supported rate control methods available");
  }

  if(AvConfigAttrib[VAConfigAttribEncInterlaced].value != VA_ATTRIB_NOT_SUPPORTED)
  {
    InConfigAttrib.push_back({VAConfigAttribEncInterlaced, VA_ENC_PACKED_HEADER_NONE});
  }

  if((Res = vaCreateConfig(MainDisplay, Profile, EntryPoint, InConfigAttrib.data(), InConfigAttrib.size(), &ConfId)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to create Encoder config with error " + std::to_string(Res));
  }

  VASurfaceID inSurface;
  VAImage inImage;

  VABufferID outBuffer;

  if((Res = vaCreateSurfaces(MainDisplay, VA_RT_FORMAT_YUV420, Width, Height, &inSurface, 1, NULL, 0)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to create Surfaces with error " + std::to_string(Res));
  }

  if((Res = vaCreateContext(MainDisplay, ConfId, Width, Height, VA_PROGRESSIVE, &inSurface, 1, &EncContext)) != VA_STATUS_SUCCESS)
  {
    throw std::runtime_error("Failed to create encoder context with error " + std::to_string(Res));
  }

  if((Res = vaCreateBuffer(MainDisplay, EncContext, VABufferType::VAEncCodedBufferType, Width*Height, 1, NULL, &outBuffer) != VA_STATUS_SUCCESS))
  {
    throw std::runtime_error("Failed to create the codec output Buffer with error " + std::to_string(Res));
  }

  FillSurface(&MainDisplay, &inSurface);

  // this structure wraps the SPS sequence parameter set. It's a small object that feeds the AVC Encoder information about input and output, as well as Algo info as well.
  VAEncSequenceParameterBufferH264 SequenceParams;
  VABufferID SeqBuffer;

  // this structure wraps the H.264 PPS picture parameter set.
  VAEncPictureParameterBufferH264 PictureParams;
  VABufferID PicBuffer;

  // this structure wraps the H.264 Slice parameter set.
  VAEncSliceParameterBufferH264 SliceParams;
  VABufferID SliceBuffer;

  uint32_t FrameIndex = 0;

  for(uint32_t i = 0; i < 20; i++)
  {
    // Baseline Profile level 3.0 :  30
    // Main Profile Level 4.0 :      40
    // High Profile Level 4.1 :      41
    SequenceParams.level_idc = (Profile == VAProfileH264Main) ? PROFILE_IDC_MAIN: (Profile == VAProfileH264High) ? PROFILE_IDC_HIGH : 0; // check h.264 wiki though, this might be wrong

    SequenceParams.picture_width_in_mbs = (Width + 15) / 16;
    SequenceParams.picture_height_in_mbs = (Height + 15) / 16;

    SequenceParams.seq_parameter_set_id = 0;
    SequenceParams.intra_period = 30;
    SequenceParams.intra_idr_period = 30;
    SequenceParams.max_num_ref_frames = 4;
    SequenceParams.ip_period = 1;
    SequenceParams.max_num_ref_frames = 4;
    SequenceParams.seq_fields.bits.frame_mbs_only_flag = 1;
    SequenceParams.seq_fields.bits.chroma_format_idc = 1;
    SequenceParams.bits_per_second = BitRate;

    if((Res = vaCreateBuffer(MainDisplay, EncContext, VAEncSequenceParameterBufferType, sizeof(SequenceParams), 1, &SequenceParams, &SeqBuffer)) != VA_STATUS_SUCCESS)
    {
      throw std::runtime_error("Failed to create sequence parameter buffer with error " + std::to_string(Res));
    }

    PictureParams.CurrPic.picture_id = inSurface;
    PictureParams.CurrPic.frame_idx = FrameIndex;
    PictureParams.CurrPic.TopFieldOrderCnt = 0;
    PictureParams.CurrPic.BottomFieldOrderCnt = 0;
    PictureParams.coded_buf = outBuffer;
    PictureParams.frame_num = i;
    PictureParams.ReferenceFrames[0].picture_id = VA_INVALID_SURFACE;
    PictureParams.ReferenceFrames[1].picture_id = VA_INVALID_SURFACE;
    PictureParams.ReferenceFrames[2].picture_id = VA_INVALID_SURFACE;
    if((Res = vaCreateBuffer(MainDisplay, EncContext, VAEncPictureParameterBufferType, sizeof(PictureParams), 1, &PictureParams, &PicBuffer)) != VA_STATUS_SUCCESS)
    {
      throw std::runtime_error("Failed to create Picture parameter buffer with error: " + std::to_string(Res));
    }

    SliceParams.slice_qp_delta = 0;
    SliceParams.slice_type = VASliceParameterBufferType;
    if((Res = vaCreateBuffer(MainDisplay, EncContext, VAEncPictureParameterBufferType, sizeof(SliceParams), 1, &PictureParams, &SliceBuffer)) != VA_STATUS_SUCCESS)
    {
      throw std::runtime_error("Failed to create Slice Parameter buffer with error: " + std::to_string(Res));
    }

    vaDeriveImage(MainDisplay, inSurface, &inImage);
    uint8_t* yPlane;
    uint8_t* uPlane;
    uint8_t* vPlane; // YUV because we are using VA_RT_FORMAT_YUV420
    void* ImgBuffer;

    vaMapBuffer(MainDisplay, inImage.buf, &ImgBuffer);

    yPlane = (uint8_t*)ImgBuffer + inImage.offsets[0];
    uPlane = (uint8_t*)ImgBuffer + inImage.offsets[1];
    vPlane = uPlane + 1;

    /* Write to buffer */

    vaUnmapBuffer(MainDisplay, inImage.buf);

    vaBeginPicture(MainDisplay, EncContext, inSurface);
    vaRenderPicture(MainDisplay, EncContext, &SeqBuffer, 1);
    vaRenderPicture(MainDisplay, EncContext, &PicBuffer, 1);
    vaRenderPicture(MainDisplay, EncContext, &SliceBuffer, 1);
    vaEndPicture(MainDisplay, EncContext);

    //vaSyncSurface(MainDisplay, inSurface);

    //VACodedBufferSegment* CodedData;

    //if((Res = vaMapBuffer(MainDisplay, outBuffer, (void**)&CodedData)) != VA_STATUS_SUCCESS)
    //{
    //  throw std::runtime_error("Failed to map output buffer with error " + std::to_string(Res));
    //}

    //// we can also use uchar
    //uint8_t* CodedMemory = (uint8_t*)CodedData->buf;

    //fwrite(CodedMemory, CodedData->size, 1, outFile);

    //if((Res = vaUnmapBuffer(MainDisplay, outBuffer)) != VA_STATUS_SUCCESS)
    //{
    //  throw std::runtime_error("Failed to unmap output buffer with errror " + std::to_string(Res));
    //}

    //FrameIndex++;
  }

  std::cout << "Successful run complete\n";

  vaDestroyImage(MainDisplay, inImage.image_id);
  vaDestroyContext(MainDisplay, EncContext);
  vaDestroyConfig(MainDisplay, ConfId);
  vaTerminate(MainDisplay);

  // To get the value of an attribute of type VAConfigAttribX X being the type of Attribute you want to retrieve.

  return 0;
}

