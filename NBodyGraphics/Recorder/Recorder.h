#ifndef NBODYSIMULATOR_RECORDER_H
#define NBODYSIMULATOR_RECORDER_H

#include <glad/glad.h>
#include <opencv2/opencv.hpp>

class Recorder {
private:
    GLuint fbo;
    GLuint texture;
    unsigned int* framebuffer;

    int width = 1280;
    int height = 720;
    const int fps = 25;
    int frame_id = 0;
    cv::VideoWriter videoWriter;

public:
//    Recorder();
    explicit Recorder(int width, int height);
    Recorder(const Recorder&) = delete;
    auto operator=(const Recorder&) -> Recorder& = delete;
    Recorder(Recorder&&) = delete;
    ~Recorder();

    void InitializeFBO();
    void InitializeVideoWriter();

    void SetWidthHeight(int width, int height);

    void StartCapture();

    void StopCapture();
};



#endif // NBODYSIMULATOR_RECORDER_H
