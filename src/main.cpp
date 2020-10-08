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
#include "aftereffects.h"

int main() {
    Window::Init(800, 600);
    GameTime gametime;
    
    // 初始化 AfterEffects
    AfterEffects::Instance();
    
    // 用户应该在这里实例化他所定义的类
    ShaderToy st;

    auto call_init = [](MonoBehaviour* mono)->void {
        mono->Init();
    };
    MonoBehaviour::Traverse(call_init);

    auto call_update = [](MonoBehaviour* mono)->void {
        mono->Update();
    };
  

    while (!Input::GetKeyDown(GLFW_KEY_ESCAPE))
    {
        Input::TestMouseDown();
        MonoBehaviour::Traverse(call_update);
        AfterEffects::Instance()->SetTextureBufferAsRenderTarget();
        GameObjectFactory::RenderGameObject();
        AfterEffects::Instance()->SetDefaultWindowAsRenderTarget();
//        GameObjectFactory::RenderGameObject();
        Window::Instance()->Clear();
    }

    Window::Instance()->Delete();
    return 0;
}