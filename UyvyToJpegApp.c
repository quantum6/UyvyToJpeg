
#include "YuvToJpegLib.h"


#define FORMAT_PIXEL    "uyvy"

#define FILE_YUV_FRAME  FORMAT_PIXEL  ".frame"
#define FILE_JPEG       FORMAT_PIXEL  ".jpg"

#define FRAME_WIDTH     1280
#define FRAME_HEIGHT     720

#define JPEG_QUALITY      75

int UyvyToJpgFile(const UCHAR *pJpgFile, const UCHAR* pYuvFrame,
    const int nWidth, const int nHeight)
{
    YuvJpegInfo oJpegInfo = {0};
    UCHAR* pYuvData  = NULL;
    UCHAR* pJpegLine = NULL;
    int i   = 0;
    int i2  = 0;
    int idx = 0;

    if (YUV_InitJpegInfo(&oJpegInfo, JPEG_QUALITY, nWidth, nHeight, pJpgFile))
    {
        return -1;
    }
    
    pYuvData  = (UCHAR*)pYuvFrame;
    pJpegLine = oJpegInfo.pYuvLine;
    while (YUV_NeedMoreData(&oJpegInfo))
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
        YUV_SaveLine(&(oJpegInfo));
        pYuvData += nWidth*2;
    }
    
    YUV_ReleaseJpegInfo(&(oJpegInfo));

    return 0;
}

int main(const int argc, const char** argv)
{
    int dataCount = (FRAME_WIDTH*FRAME_HEIGHT*2);
    UCHAR* pBuffer = (UCHAR*)malloc(dataCount);
    
    memset(pBuffer, 0, dataCount);

    YUV_ReadFromFile(FILE_YUV_FRAME, pBuffer, dataCount);

    UyvyToJpgFile(FILE_JPEG, pBuffer, FRAME_WIDTH, FRAME_HEIGHT);
    
    free(pBuffer);
}

