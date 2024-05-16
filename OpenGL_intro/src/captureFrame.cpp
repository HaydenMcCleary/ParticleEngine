#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "OpenGL Screenshot", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Render your OpenGL scene here

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Capture screenshot
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        std::vector<unsigned char> pixels(3 * width * height);
        glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);

        // You can save pixels to an image file here using libraries like stb_image/stb_image_write
        // Example:
        std::ostringstream filename;
        filename << "screenshot_" << glfwGetTime() << ".png";
        stbi_write_png(filename.str().c_str(), width, height, 3, &pixels[0], 0);
    }

    glfwTerminate();
    return 0;
}
