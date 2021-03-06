#include "main_scene.h"

#include <iostream>
#include <imgui.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gopt.hpp>

MainScene::~MainScene()
{
    delete renderer;
    delete shader;
    delete model;
    delete model2;
    delete fb;
}

void MainScene::init()
{
    layout_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

    shader = new Shader();
    renderer = new Renderer(shader);

    model = new Model("assets/Rocket_Pen.stl");
    model->position = {-2.0, 0.0, -1.0};
    model->rotation_matrix = gopt::rotation(-gopt::pi<float> / 2, gopt::Vec3f{ 1, 0, 0 });
    model->color = gopt::Vec3f{ 0.0f, 1.0f, 0.0f };

    model2 = new Model("assets/sphere.stl");
    model2->position = {-3.0, 0.0, -1.0};
    model2->rotation_matrix = gopt::rotation(-gopt::pi<float> / 2, gopt::Vec3f{ 1, 0, 0 });
    model2->color = gopt::Vec3f{ 0.0f, 0.0f, 1.0f };

    unsigned int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), (int*)&width, (int*)&height);
    const auto perspective = gopt::perspective((float)(width) / (float)(height), 65.0f, 0.001f, 1000.0f);
    shader->begin();
    shader->set("projection", perspective);
    shader->end();

    fb = new Framebuffer(1280, 720);
}

void MainScene::input()
{
    ImGuiIO& io = ImGui::GetIO();

    if (io.KeyCtrl)
    {
        if (io.KeysDown[GLFW_KEY_E] && io.KeysDownDuration[GLFW_KEY_E] == 0.0f)
            layout_flags ^= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    }
}

void MainScene::update(double dt)
{
    model->rotation[0] += dt;
}

void MainScene::render()
{
    fb->begin();
    renderer->begin();
    renderer->render(model);
    renderer->render(model2);
    renderer->end();
    fb->end();

    ImGui::Begin("Demo window", nullptr, layout_flags);
    const ImVec2 size = ImGui::GetContentRegionAvail();
    ImGui::GetWindowDrawList()->AddImage((void*)fb->tex, ImVec2(ImGui::GetCursorScreenPos()),
                                         ImVec2(ImGui::GetCursorScreenPos().x + size.x,
                                         ImGui::GetCursorScreenPos().y + size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
    /*int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

    const ImGuiWindowFlags main_win_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                                            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus |
                                            ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration;

    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::SetNextWindowSize({ (float)width, 30.0f });
    ImGui::Begin("Menu", nullptr, main_win_flags | ImGuiWindowFlags_NoDocking);

    if (ImGui::BeginTabBar("blah2"))
    {
        if (ImGui::BeginTabItem("Video"))
        {
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Music"))
        {
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();

    ImGui::SetNextWindowPos({ 0, 30.0f });
    ImGui::SetNextWindowSize({ (float)width, (float)height - 30.0f });
    ImGui::Begin("Simulator", nullptr, main_win_flags);

    ImGui::Begin("Demo window", nullptr, layout_flags);
    if (ImGui::BeginTabBar("blah"))
    {
        if (ImGui::BeginTabItem("Video"))
        {
            ImGui::Button("Save");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Music"))
        {
            ImGui::Button("Upload");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();

    ImGui::Begin("Demo window 2", nullptr, layout_flags);
    ImGui::Button("Hello!");
    ImGui::End();

    ImGui::Begin("Demo window 3", nullptr, layout_flags);
    ImGui::Button("Hello!");
    ImGui::End();

    ImGui::Begin("Demo window 4", nullptr, layout_flags);
    ImGui::Button("Hello!");
    ImGui::End();

    ImGui::Begin("Demo window 5", nullptr, layout_flags);
    ImGui::Button("Hello!");
    ImGui::End();

    ImGui::End();

    /*static bool show_demo_window = false;

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Begin("Demo window", nullptr, layout_flags);
    if (ImGui::BeginTabBar("blah"))
    {
        if (ImGui::BeginTabItem("Video"))
        {
            ImGui::Checkbox("Demo Window", &show_demo_window);
            ImGui::Button("Save");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Music"))
        {
            ImGui::Button("Upload");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();

    ImGui::Begin("Demo window 2", nullptr, layout_flags);
    ImGui::Button("Hello!");
    ImGui::End();*/
}

void MainScene::resize(unsigned int width, unsigned int height)
{

}