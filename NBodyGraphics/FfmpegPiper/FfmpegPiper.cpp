#include <iostream>
#include "FfmpegPiper.h"

#include <glad/glad.h>

FfmpegPiper::FfmpegPiper(const int width, const int height, const int framerate) {
    this->width = width;
    this->height = height;
    this->frameRate = framerate;

    // ffmpeg -f rawvideo -pixel_format rgba -video_size WIDTHxHEIGHT -framerate FRAMERATE -i - -c:v libx264 -preset ultrafast -tune zerolatency -f flv http://your-http-server/stream
    // -pix_fmt rgb24  -f flv rtmp://<streaming_server>/<stream_key>
    std::string const command = "ffmpeg -f rawvideo -pix_fmt rgb24 -s " + std::to_string(width) + "x" + std::to_string(height) + " -r " + std::to_string(framerate) + " -i - -c:v libx264 -preset ultrafast -tune zerolatency -f flv rtmp://localhost/live/test";

    pipe = popen(command.c_str(), "wb");

    if (pipe == nullptr)
    {
        std::cout << "Error opening pipe for output" << std::endl;
    }
}

FfmpegPiper::~FfmpegPiper() {
    pclose(pipe);
}

void FfmpegPiper::updateFrame(const unsigned char* fbo) {
}

//    fwrite(fbo, 1, width * height * 3, pipe);
// void FfmpegPiper::updateFrame(const unsigned char* frame) {
//     // Send a FBO frame to ffmpeg
//     fwrite(frame, 1, width * height * 3, pipe);
// }
