#include "shadertoy.h"
#include "gametime.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static bool firstMouse = true;
    static float lastX = 0;
    static float lastY = 0;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 1;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    Camera::Instance()->Rotate(xoffset, yoffset);

}

void ShaderToy::Init() {

    main_camera = Camera::Instance();

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    ShaderPtr light_shader = std::make_shared<Shader>("shader/light.vs", "shader/light.fs");
    light_shader->Use();

    ModelPtr light = std::make_shared<Model>(lightPos, glm::vec3(0, 0, 0), glm::vec3(.2f));
    light_shader->SetMat4("model", light->GetModelMatrix());
    light_shader->SetMat4("projection", main_camera->GetProjectionMatrix());
    light_shader->SetMat4("view", main_camera->GetViewMatrix());
    light_shader->SetVec3("viewPos", main_camera->GetPosition());

    ShaderPtr cube_shader = std::make_shared<Shader>("shader/cube.vs", "shader/cube.fs");
    cube_shader->Use();

    ModelPtr cube =std::make_shared<Model>(glm::vec3(0, 0, 9.5), glm::vec3(0, 0, 0));
    cube_shader->SetMat4("model", cube->GetModelMatrix());
    cube_shader->SetMat4("projection", main_camera->GetProjectionMatrix());
    cube_shader->SetMat4("view", main_camera->GetViewMatrix());
    cube_shader->SetVec3("material.ambient", glm::vec3(1));
    cube_shader->SetVec3("material.diffuse", glm::vec3(1));
    cube_shader->SetVec3("material.specular", glm::vec3(1));
    cube_shader->SetFloat("material.shininess", 32.0f);
    cube_shader->SetVec3("light.position", lightPos);
    cube_shader->SetVec3("light.ambient", glm::vec3(.2f));
    cube_shader->SetVec3("light.diffuse", glm::vec3(.5f));
    cube_shader->SetVec3("light.specular", glm::vec3(1));
        
    Texture2D tex1("texture/skadi.png",1u);
    cube_shader->SetInt("MainTex", 1);

    std::shared_ptr<Mesh> mp = Mesh::GetCube();// std::make_shared<Mesh>(vp, ip, uvp, np);
    
    cube->SetMesh(mp);
    light->SetMesh(mp);

    lasttime = glfwGetTime();

    cubego = GameObjectFactory::CreateGameObject("cube", cube, cube_shader);
    cubeaabb = std::make_shared<AABB>(cubego, glm::vec3(1));
    auto cube_mouse_callback = [=]()->void {
        cubego->Rotate(glm::vec3(0,30 *  GameTime::DeltaTime(), 0));
    };
    cubeaabb->onClick = (cube_mouse_callback);

    lightgo = GameObjectFactory::CreateGameObject("light", light, light_shader);

//    glfwSetCursorPosCallback(Window::Instance()->glfwwindow(),mouse_callback);
}

void ShaderToy::Update() {

    float dis = camera_speed * GameTime::DeltaTime();
 
    if (Input::GetKeyDown(GLFW_KEY_A)) {
        Camera::Instance()->Translate(LEFT, dis);
    }
    else if (Input::GetKeyDown(GLFW_KEY_D)) {
        Camera::Instance()->Translate(RIGHT, dis);
    }
    else if (Input::GetKeyDown(GLFW_KEY_S)) {
        Camera::Instance()->Translate(BACK, dis);
    }
    else if (Input::GetKeyDown(GLFW_KEY_W)) {
        Camera::Instance()->Translate(FRONT, dis);
    }
    else if (Input::GetKeyDown(GLFW_KEY_Q)) {
        Camera::Instance()->Translate(UP, dis);
    }
    else if (Input::GetKeyDown(GLFW_KEY_E)) {
        Camera::Instance()->Translate(DOWN, dis);
    }

//    glm::vec3 pos = cubego->GetModel()->GetPosition();
//    std::cout << "(" << pos.x << "," << pos.y << "," << pos.z << ")\n";
    
//    cubego->Translate(glm::vec3(0, 1, 0), GameTime::DeltaTime());
//    cubego->Rotate(glm::vec3(0, 0, GameTime::DeltaTime() * 90));

}

