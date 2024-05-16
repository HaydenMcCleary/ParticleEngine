

#include "glad.h"

#include <GLFW/glfw3.h>

#include "shader.h"

#include <iostream>

#include <cmath>
#include <sstream>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // For saving images



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void captureSnapshot(const char* filename, int width, int height);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("/home/hayden/Documents/ParticleEngine/OpenGL_intro/src/shaders/3.3.shader.vs", "/home/hayden/Documents/ParticleEngine/OpenGL_intro/src/shaders/3.3.shader.fs"); // you can name your shader files however you like


    // VERTICES FOR TRIANGLE
    float vertices[] = {
        // positions         // colors

        // TRIANGLE
         0.2f, -0.2f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.2f, -0.2f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.2f, 0.0f,  0.0f, 0.0f, 1.0f,   // top 

        // RECTANGLES
        -0.4f,  0.4f, 0.0f,  1.0f, 1.0f, 1.0f,  // top top left
         0.4f,  0.4f, 0.0f,  1.0f, 1.0f, 1.0f,  // top top right
         0.3f,  0.3f, 0.0f,  1.0f, 1.0f, 1.0f,  // top bot right
        -0.3f,  0.3f, 0.0f,  1.0f, 1.0f, 1.0f,   // top bot left


        -0.4f, -0.4f, 0.0f,  1.0f, 1.0f, 1.0f,  // bot top left
         0.4f, -0.4f, 0.0f,  1.0f, 1.0f, 1.0f,  // bot top right
         0.3f, -0.3f, 0.0f,  1.0f, 1.0f, 1.0f,  // bot bot right
        -0.3f, -0.3f, 0.0f,  1.0f, 1.0f, 1.0f   // bot bot left


    };

    unsigned int indices[] = {
        // Traingle
        0, 1, 2,

        // Rectangle

        // top
        3, 4, 5,
        5, 6, 3,

        // bot
        7, 8, 9,
        9, 10, 7,

        // right

        4, 5, 8, 
        9, 8, 5, 

        // left

        3, 6, 7, 
        10, 7, 6, 

    };



    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    int i;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        float timeValue = glfwGetTime();
        float movement = (sin(timeValue)/2.0f);

        ourShader.setFloat("xOffset", movement);


        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)(3*sizeof(unsigned int))); // Draw the rectangles
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); // Draw the rectangles
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(21*sizeof(unsigned int))); // Draw the rectangles
        glBindVertexArray(0);



        std::ostringstream filename;

        filename << "screenshot_" << ++i << ".png";
        captureSnapshot(filename.str().c_str(), SCR_WIDTH, SCR_HEIGHT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Set the viewport to cover the entire window
    glViewport(0, 0, width, height);

    // Calculate the aspect ratio of the window
    float aspectRatio = (float)width / (float)height;

    // Adjust the projection matrix
    // For example, if you're using a perspective projection:

}

void captureSnapshot(const char* filename, int width, int height)
{

    
    std::string filepath = "/home/hayden/Documents/ParticleEngine/OpenGL_intro/screenshots_to_gif/screenshots" + std::string(filename);

    // Allocate memory for the image
    std::vector<unsigned char> pixels(3 * width * height);

    // Read the pixels from the framebuffer
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    // Flip the image vertically
    for (int i = 0; i < height / 2; ++i)
    {
        for (int j = 0; j < width * 3; ++j)
        {
            std::swap(pixels[i * width * 3 + j], pixels[(height - i - 1) * width * 3 + j]);
        }
    }

    // Save the image using stb_image_write
    stbi_flip_vertically_on_write(1);
    stbi_write_png(filepath.c_str(), width, height, 3, pixels.data(), width * 3);
}
