#pragma once

struct GLFWwindow;
class BasicCamera;

class DemoApp
{
public:
   DemoApp(int windowWidth, int windowHeight, const char* windowTitle);
   virtual ~DemoApp();

   virtual void Cleanup();

   void Run();

   virtual void RenderScene();

   void PassiveMouseCB(double x, double y);
   void KeyboardCB(int key, int state);
   void MouseCB(int button, int action, int x, int y);

private:
   virtual void Init(int windowWidth, int windowHeight, const char* windowTitle);

   void CreateGlfwWindow(int windowWidth, int windowHeight, const char* windowTitle);
   void InitCallbacks();
   void InitCamera(int windowWidth, int windowHeight);


private:
   GLFWwindow* m_pWindow;
   BasicCamera* m_pBasicCamera;
   bool m_isWireframe = false;

   double m_deltaTime = 0.0f;	// time between current frame and last frame
   double m_lastFrame = 0.0f;
};

