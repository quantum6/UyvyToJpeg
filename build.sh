
EXE_FILE=uyvyToJpeg
if [ -f ${EXE_FILE} ]; then
    rm ${EXE_FILE}
fi

JPG_FILE=uyvy.jpg
if [ -f ${JPG_FILE} ]; then
    rm ${JPG_FILE}
fi

gcc \
    YuvToJpegLib.c UyvyToJpeg.c \
    -o ${EXE_FILE} \
    -I /usr/local/include \
    -L /usr/lib/ -ljpeg \

