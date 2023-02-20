#include "YuvLibFile.h"
#include "YuvLibJpeg.h"


#define FILE_NAME_SIZE  256

#define FRAME_WIDTH     1280
#define FRAME_HEIGHT     720

#define JPEG_QUALITY      75

int UyvyToJpgFile(const char *pJpgFile, const char* pYuvFrame,
    const int nWidth, const int nHeight)
{
    YuvJpegInfo oJpegInfo = {0};
    char* pYuvData  = NULL;
    char* pJpegLine = NULL;
    int i   = 0;
    int i2  = 0;
    int idx = 0;

    if (YUV_Jpeg_InitInfo(&oJpegInfo, JPEG_QUALITY, nWidth, nHeight, pJpgFile))
    {
        return -1;
    }
    
    pYuvData  = (char*)pYuvFrame;
    pJpegLine = oJpegInfo.pYuvLine;
    while (YUV_Jpeg_NeedMoreData(&oJpegInfo))
    {
        idx=0;
        for (i=0; i<nWidth; i++)
        {
            i2 = (i<<1);
            if (i % 2 == 0)
            {
                pJpegLine[idx++]=pYuvData[i2+1];
                pJpegLine[idx++]=pYuvData[i2  ];
                pJpegLine[idx++]=pYuvData[i2+2];
            }
            else
            {
                pJpegLine[idx++]=pYuvData[i2+1];
                pJpegLine[idx++]=pYuvData[i2-2];
                pJpegLine[idx++]=pYuvData[i2  ];
            }
        }
        YUV_Jpeg_SaveLine(&(oJpegInfo));
        pYuvData += nWidth*2;
    }
    
    YUV_Jpeg_ReleaseInfo(&(oJpegInfo));

    return 0;
}

int main(const int argc, const char** argv)
{
    char uyvyFile[FILE_NAME_SIZE] = {0};
    char jpegFile[FILE_NAME_SIZE] = {0};
    
    int dataCount = (FRAME_WIDTH*FRAME_HEIGHT*2);
    char* pUyvy = (char*)malloc(dataCount);

    YUV_CreateFileNameFrame(uyvyFile, "../RgbToUyvy/Uyvy", FRAME_WIDTH, FRAME_HEIGHT);
    YUV_ReadFromFile(uyvyFile, pUyvy, dataCount);

    YUV_CreateFileName(jpegFile, "Uyvy", "jpg", FRAME_WIDTH, FRAME_HEIGHT);
    UyvyToJpgFile(jpegFile, pUyvy, FRAME_WIDTH, FRAME_HEIGHT);

    free(pUyvy);
}

