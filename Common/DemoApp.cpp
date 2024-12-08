#include <pch.h>

#include "DemoApp.h"
#include "BasicCamera.h"

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void CursorPosCallback(GLFWwindow* window, double x, double y);
static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode);

DemoApp* g_App;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (g_App != NULL)
      g_App->KeyboardCB(key, action);
}


static void CursorPosCallback(GLFWwindow* window, double x, double y)
{
   if (g_App != NULL)
      g_App->PassiveMouseCB(x, y);
}


static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode)
{
   double x, y;

   glfwGetCursorPos(window, &x, &y);

   if (g_App != NULL)
      g_App->MouseCB(Button, Action, (int)x, (int)y);
}

DemoApp::DemoApp(int windowWidth, int windowHeight, const char* windowTitle)
{
   Init(windowWidth, windowHeight, windowTitle);
}
DemoApp::~DemoApp()
{
   Cleanup();
}

void DemoApp::Cleanup()
{
   if (m_pBasicCamera != NULL) {
      delete m_pBasicCamera;
      m_pBasicCamera = NULL;
   }
}

void DemoApp::Run()
{
   while (!glfwWindowShouldClose(m_pWindow)) {
      // per-frame time logic
      double currentFrame = glfwGetTime();
      m_deltaTime = currentFrame - m_lastFrame;
      m_lastFrame = currentFrame;

      RenderScene();

      glfwSwapBuffers(m_pWindow);
      glfwPollEvents();
   }
}

void DemoApp::RenderScene()
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DemoApp::PassiveMouseCB(double x, double y)
{
   m_pBasicCamera->MouseControl((float)x, (float)y);
}

void DemoApp::KeyboardCB(int key, int state)
{
   if (state == GLFW_PRESS) {
      switch (key) {
      case GLFW_KEY_ESCAPE:
      case GLFW_KEY_Q:
         glfwDestroyWindow(m_pWindow);
         glfwTerminate();
         exit(0);

      case GLFW_KEY_W:
         m_isWireframe = !m_isWireframe;

         if (m_isWireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         }
         else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         }
         break;
      case GLFW_KEY_UP:
         m_pBasicCamera->ProcessKeyboard(FORWARD, (float)m_deltaTime);
         break;
      case GLFW_KEY_DOWN:
         m_pBasicCamera->ProcessKeyboard(BACKWARD, (float)m_deltaTime);
         break;
      case GLFW_KEY_LEFT:
         m_pBasicCamera->ProcessKeyboard(LEFT, (float)m_deltaTime);
         break;
      case GLFW_KEY_RIGHT:
         m_pBasicCamera->ProcessKeyboard(RIGHT, (float)m_deltaTime);
         break;
      case GLFW_KEY_PAGE_UP:
         m_pBasicCamera->ProcessKeyboard(UP, (float)m_deltaTime);
         break;
      case GLFW_KEY_PAGE_DOWN:
         m_pBasicCamera->ProcessKeyboard(DOWN, (float)m_deltaTime);
         break;
      case GLFW_KEY_R:
         int width, height;
         glfwGetWindowSize(m_pWindow, &width, &height);
         m_pBasicCamera->Reset(width, height);
         break;
      }
   }
}


void DemoApp::MouseCB(int button, int action, int x, int y)
{
}

void DemoApp::Init(int windowWidth, int windowHeight, const char* windowTitle)
{
   CreateGlfwWindow(windowWidth, windowHeight, windowTitle);

   InitCallbacks();

   InitCamera(windowWidth, windowHeight);

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

   glFrontFace(GL_CW);
   glCullFace(GL_BACK);

   glEnable(GL_CULL_FACE);
   glEnable(GL_DEPTH_TEST);
}

void DemoApp::CreateGlfwWindow(int windowWidth, int windowHeight, const char* windowTitle)
{
   int major_ver = 0;
   int minor_ver = 0;

   bool is_full_screen = false;
   m_pWindow = glfw_init(major_ver, minor_ver, windowWidth, windowHeight, is_full_screen, "Terrain Rendering - Demo 1");

   glfwSetCursorPos(m_pWindow, windowWidth / 2, windowHeight / 2);
}

void DemoApp::InitCallbacks()
{
   glfwSetKeyCallback(m_pWindow, KeyCallback);
   glfwSetCursorPosCallback(m_pWindow, CursorPosCallback);
   glfwSetMouseButtonCallback(m_pWindow, MouseButtonCallback);
}

void DemoApp::InitCamera(int windowWidth, int windowHeight)
{
   m_pBasicCamera = new BasicCamera(windowWidth, windowHeight, glm::vec3(0.0, 0.0, 3.0));
}