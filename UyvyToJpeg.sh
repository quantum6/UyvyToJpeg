
EXE_FILE=UyvyToJpeg
if [ -f ${EXE_FILE} ]; then
    rm ${EXE_FILE}
fi

JPG_FILE=Uyvy-1280x720.jpg
if [ -f ${JPG_FILE} ]; then
    rm ${JPG_FILE}
fi

gcc \
    ../YuvLib/YuvLibFile.c ../YuvLibJpeg/YuvLibJpeg.c \
    UyvyToJpegApp.c \
    -o ${EXE_FILE} \
    -I /usr/local/include \
    -L /usr/lib/ -ljpeg \
    -I ../YuvLib \
    -I ../YuvLibJpeg

./${EXE_FILE}

