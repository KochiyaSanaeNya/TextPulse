#include "core/platform.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace textpulse {

int run_app(const char* title, float red, float green, float blue) {
  if (!glfwInit()) {
    std::cerr << "GLFW initialization failed\n";
    return 1;
  }

  GLFWwindow* window = glfwCreateWindow(960, 540, title, nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Window creation failed\n";
    glfwTerminate();
    return 1;
  }

  ALCdevice* audio_device = alcOpenDevice(nullptr);
  ALCcontext* audio_context = nullptr;
  if (audio_device == nullptr) {
    std::cerr << "OpenAL device creation failed, continue without audio\n";
  } else {
    audio_context = alcCreateContext(audio_device, nullptr);
    if (audio_context == nullptr) {
      std::cerr << "OpenAL context creation failed, continue without audio\n";
      alcCloseDevice(audio_device);
      audio_device = nullptr;
    } else if (alcMakeContextCurrent(audio_context) == ALC_FALSE) {
      std::cerr << "OpenAL context activation failed, continue without audio\n";
      alcDestroyContext(audio_context);
      audio_context = nullptr;
      alcCloseDevice(audio_device);
      audio_device = nullptr;
    }
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(red, green, blue, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  if (audio_context != nullptr) {
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(audio_context);
  }
  if (audio_device != nullptr) {
    alcCloseDevice(audio_device);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

}  // namespace textpulse
