#ifndef NBODYGRAPHICS_FFMPEGPIPER_H
#define NBODYGRAPHICS_FFMPEGPIPER_H

#include <string>

class FfmpegPiper {
private:
    int width;
    int height;
    int framerate;

    FILE* pipe;


public:
    FfmpegPiper(const int width, const int height, const int framerate)

        FfmpegPiper(const FfmpegPiper&) = delete;
    auto operator=(const FfmpegPiper&) -> FfmpegPiper& = delete;
    FfmpegPiper(FfmpegPiper&&) = delete;
    auto operator=(FfmpegPiper&&) -> FfmpegPiper& = delete;

    ~FfmpegPiper();

public:
    void updateFrame(const unsigned char* fbo);
};

#endif // NBODYGRAPHICS_FFMPEGPIPER_H
