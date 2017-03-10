#include "ofApp.h"

int main()
{
#ifdef TARGET_OPENGLES
  ofGLESWindowSettings settings;
  settings.windowMode = OF_FULLSCREEN;
  // settings.width = 1280;
  // settings.height = 720;
  //settings.glesVersion = 2;
#else
  ofGLWindowSettings settings;
  settings.setGLVersion(3,2);
#endif

  auto window = ofCreateWindow(settings);
  auto app = make_shared<ofApp>();
  ofRunApp(window, app);

  return ofRunMainLoop();
}
