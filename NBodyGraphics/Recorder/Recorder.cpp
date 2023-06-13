#include "Recorder.h"
#include <iostream>

Recorder::Recorder(int width, int height) : width(width), height(height), framebuffer(new unsigned char[width * height * 3]) {
    InitializeFBO();
    InitializeVideoWriter();
}

Recorder::~Recorder() {
    std::cout << "Recorder destructor" << std::endl;
    videoWriter.release();
    delete[] framebuffer;
}

void Recorder::InitializeFBO() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Recorder::InitializeVideoWriter() {
    int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    cv::Size size = cv::Size(width, height);

    videoWriter.open("output.avi", fourcc, fps, size, true);
    std::cout << "open video" << std::endl;
    if (!videoWriter.isOpened())
    {
        std::cout << "ERROR::RECORDER:: Could not open the output video for writing" << std::endl;
    }
}

void Recorder::StartCapture() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, width, height);
}

void Recorder::StopCapture() {
    glBindTexture(GL_TEXTURE_2D, texture);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, framebuffer);

    cv::Mat image(height, width, CV_8UC3, framebuffer);

    cv::cvtColor(image, image, cv::COLOR_BGR2RGB); // Correct color conversion

    videoWriter.write(image);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Recorder::SetWidthHeight(int width, int height) {
    this->width = width;
    this->height = height;
    delete[] framebuffer;
    framebuffer = new unsigned char[width * height * 3];
}
