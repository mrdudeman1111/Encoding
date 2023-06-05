#include <iostream>
#include <fstream>

#include <va/va.h>
#include <va/va_enc_h264.h>

const int frameWidth = 1920;    // video frame width
const int frameHeight = 1080;   // video frame height
const int frameRate = 30;       // video frame rate
const int bitrate = 6000000;    // video bitrate
const int gopSize = 60;         // size of each GOP

int main(int argc, char** argv)
{
    VAStatus vaStatus;
    VADisplay vaDisplay;
    VAConfigID vaConfigID;
    VAContextID vaContextID;
    VASurfaceID inputSurfaceID, outputSurfaceID;
    VAConfigAttrib attribs[2];
    VAEntrypoint entrypoints[5];
    VAProfile profiles[5];
    int numEntryPoints, numProfiles, i;

    vaStatus = vaInitialize(&vaDisplay, NULL);
    if (vaStatus != VA_STATUS_SUCCESS)
    {
        // handle error
    }

    // query supported profiles and entry points
    vaQueryConfigProfiles(vaDisplay, profiles, &numProfiles);
    vaQueryConfigEntrypoints(vaDisplay, VAProfileH264High, entrypoints, &numEntryPoints);

    // create a H.264 profile
    for (i = 0; i < numProfiles; i++)
    {
        if (profiles[i] == VAProfileH264High)
        {
            attribs[0].type = VAConfigAttribRTFormat;
            attribs[0].value = VA_RT_FORMAT_YUV420;
            attribs[1].type = VAConfigAttribRateControl;
            attribs[1].value = VA_RC_CBR;
            vaStatus = vaCreateConfig(vaDisplay, VAProfileH264High, VAEntrypointEncSlice, attribs, 2, &vaConfigID);
            if (vaStatus == VA_STATUS_SUCCESS)
                break;
        }
    }
    if (i == numProfiles)
    {
        // handle error - H.264 not supported
    }

    // create a context for encoding
    vaStatus = vaCreateContext(vaDisplay, vaConfigID, frameWidth, frameHeight, VA_PROGRESSIVE, NULL, 0, &vaContextID);
    if (vaStatus != VA_STATUS_SUCCESS)
    {
        // handle error
    }

    // acquire a surface for input
    vaStatus = vaCreateSurfaces(vaDisplay, VA_RT_FORMAT_YUV420, frameWidth, frameHeight, &inputSurfaceID, 1, NULL, 0);
    if (vaStatus != VA_STATUS_SUCCESS)
    {
        // handle error
    }

    // acquire a surface for output
    vaStatus = vaCreateSurfaces(vaDisplay, VA_RT_FORMAT_YUV420, frameWidth, frameHeight, &outputSurfaceID, 1, NULL, 0);
    if (vaStatus != VA_STATUS_SUCCESS)
    {
        // handle error
    }

    // output H.264 stream to file
    FILE* outFile = fopen("output.h264", "wb");
    if (!outFile)
    {
        // handle error
    }

    // start encoding
    VAEncSequenceParameterBufferH264 seqParam;
    VAEncPictureParameterBufferH264 picParam;
    VAEncSliceParameterBufferH264 sliceParam;
    int frameNumber = 0;
    while (/* loop until end of video */)
    {
        // fill in sequence parameter buffer
        seqParam.level_idc = 0; // TODO: fill in level
        seqParam.intra_period = gopSize;
        seqParam.idr_period = gopSize;
        seqParam.frame_width = frameWidth;
        seqParam.frame_height = frameHeight;
        seqParam.frame_cropping_flag = 0;
        seqParam.frame_rate = frameRate;
        seqParam.bits_per_second = bitrate;
        vaStatus = vaCreateBuffer(vaDisplay, vaContextID, VAEncSequenceParameterBufferType, sizeof(seqParam), 1, &seqParam, NULL, &picParam.seq_parameter_buf_id);
        if (vaStatus != VA_STATUS_SUCCESS)
        {
            // handle error
        }

        // fill in picture parameter buffer
        picParam.CurrPic.picture_id = inputSurfaceID;
        picParam.CurrPic.frame_idx = frameNumber % gopSize;
        picParam.CurrPic.TopFieldOrderCnt = 0;
        picParam.CurrPic.BottomFieldOrderCnt = 0;
        picParam.ReferenceFrames[0].picture_id = VA_INVALID_SURFACE;
        picParam.ReferenceFrames[1].picture_id = VA_INVALID_SURFACE;
        picParam.ReferenceFrames[2].picture_id = VA_INVALID_SURFACE;
        picParam.picture_width_in_mbs = frameWidth / 16;
        picParam.picture_height_in_mbs = frameHeight / 16;
        picParam.bPicture = 0;
        picParam.pic_order_cnt_type = 0;
        picParam.num_ref_frames = 1;
        picParam.frame_num = frameNumber % gopSize;
        picParam.deblocking_filter_idc = 0;
        vaStatus = vaCreateBuffer(vaDisplay, vaContextID, VAEncPictureParameterBufferType, sizeof(picParam), 1, &picParam, NULL, &picParam.pic_parameter_buf_id);
        if (vaStatus != VA_STATUS_SUCCESS)
        {
            // handle error
        }

        // fill in slice parameter buffer
        sliceParam.restart_interval = 0;
        sliceParam.slice_mb_height = 0;
        sliceParam.slice_mb_width = 0;
        sliceParam.num_ctu_in_slice = 0;
        sliceParam.slice_qp_delta = 0;
        sliceParam.slice_type = VAEncSliceTypeInterP;
        vaStatus = vaCreateBuffer(vaDisplay, vaContextID, VAEncSliceParameterBufferType, sizeof(sliceParam), 1, &sliceParam, NULL, &sliceParam.slice_param_buf_id);
        if (vaStatus != VA_STATUS_SUCCESS)
        {
            // handle error
        }

        // render video frame
        VAImage inputImage = { 0 };
        VAImage surfaceImage = { 0 };
        vaStatus = vaDeriveImage(vaDisplay, inputSurfaceID, &inputImage);
        if (vaStatus != VA_STATUS_SUCCESS)
        {
            // handle error
        }
        uint8_t* inputData = (uint8_t*)inputImage.buf;
        uint8_t* surfaceData = (uint8_t*)surfaceImage.buf;
        // TODO: fill in YUV data for input

        vaStatus = vaPutImage(vaDisplay, inputSurfaceID, inputImage.image_id, 0, 0, frameWidth, frameHeight,
                              0, 0, frameWidth, frameHeight);
        if (vaStatus != VA_STATUS_SUCCESS)
        {
            // handle error
        }

        // encode video frame
        VABufferID inputBufferID, outputBufferID;
        VAEncSequenceParameterBufferH264* seqParamBuffer;
        VAEncPictureParameterBufferH264* picParamBuffer;
        VAEncSliceParameterBufferH264* sliceParamBuffer;
        uint8_t* bufferData;
        uint32_t bufferSize;
        vaStatus = vaCreateBuffer(vaDisplay, vaContextID, VAEncMiscParameterBufferType, sizeof(VAEncMiscParameterBuffer), 1, NULL, NULL, &inputBufferID);
        vaStatus = vaCreateBuffer(vaDisplay, vaContextID, VAEncSliceParameterBufferType, sizeof(*sliceParamBuffer), 1, NULL, NULL, &outputBufferID);
        vaStatus = vaBeginPicture(vaDisplay, vaContextID, outputSurfaceID);
        vaStatus = vaRenderPicture(vaDisplay, vaContextID, &seqParamBuffer.sequence_parameter_buf_id, 1);
        vaStatus = vaRenderPicture(vaDisplay, vaContextID, &picParamBuffer.pic_parameter_buf_id, 1);
        vaStatus = vaRenderPicture(vaDisplay, vaContextID, &sliceParamBuffer.slice_param_buf_id, 1);
        vaStatus = vaRenderPicture(vaDisplay, vaContextID, &inputBufferID, 0);
        vaStatus = vaEndPicture(display, context);
        vaStatus = vaCreateBuffer(vaDisplay, vaContextID, VAEncCodedBufferType, bufferSize, 1, NULL, NULL, &outputBufferID);
        vaStatus = vaRenderPicture(vaDisplay, vaContextID, &outputBufferID, 1);
        vaStatus = vaSyncSurface(vaDisplay, outputSurfaceID);

        // write encoded frame to file
        VAEncCodedBufferH264 outputBuffer = { 0 };
        vaMapBuffer(vaDisplay, outputBufferID, (void**)&bufferData);
        fwrite(bufferData, 1, outputBuffer.iLength, outFile);
        vaUnmapBuffer(vaDisplay, outputBufferID);

        frameNumber++;
    }

    // cleanup
    fclose(outFile);
    vaDestroySurfaces(vaDisplay, &inputSurfaceID, 1);
    vaDestroySurfaces(vaDisplay, &outputSurfaceID, 1);
    vaDestroyConfig(vaDisplay, vaConfigID);
    vaDestroyContext(vaDisplay, vaContextID);
    vaTerminate(vaDisplay);

    return 0;
}