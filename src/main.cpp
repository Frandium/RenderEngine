#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "window.h"
#include "Shader.h"
#include "mesh.h"
#include "input.h"
#include "monobehaviour.h"
#include "texture2D.h"
#include "camera.h"
#include "model.h"
#include "shadertoy.h"
#include "gametime.h"

int main() {
    Window::Init(800, 600);
    GameTime gametime;
    
    ShaderToy st;

    auto call_init = [](MonoBehaviour* mono)->void {
        mono->Init();
    };
    MonoBehaviour::Traverse(call_init);

    auto call_update = [](MonoBehaviour* mono)->void {
        mono->Update();
    };
  
    Window::Instance()->Clear();

    while (!Input::GetKeyDown(GLFW_KEY_ESCAPE))
    {
        MonoBehaviour::Traverse(call_update);
        GameObjectFactory::RenderGameObject();
        Window::Instance()->Clear();
    }

    Window::Instance()->Delete();
    return 0;
}