#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <string>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>

#include "Clock.h"

class Window
{
public:
    Window(const std::string& windowTitle, int windowWidth, int windowHeight)
    {
        if (!glfwInit())
            throw std::runtime_error("glfw is not initialized");

        m_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
        if (!m_window)
        {
            glfwTerminate();
            throw std::runtime_error("could not create window");
        }

        glfwSetFramebufferSizeCallback(m_window, &Window::OnSize);
    }

    ~Window()
    {
        glfwTerminate();
    }

    // draw clock in different class
    void MainLoop()
    {
        glfwMakeContextCurrent(m_window);

        int width, height;
        glfwGetWindowSize(m_window , &width, &height);
        OnSize(m_window, width, height);

        while (!glfwWindowShouldClose(m_window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0, 0, 0, 0);

            m_clock.Draw();

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

private:
    static void OnSize(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        double aspect = (double)width / height;
        double viewHeight = 2;
        double viewWidth = aspect * viewHeight;

        glOrtho(
            -viewWidth, +viewWidth,
            -viewHeight, +viewHeight,
            -1, 1
        );

        glMatrixMode(GL_MODELVIEW);
    }

    GLFWwindow* m_window;
    Clock m_clock;
};