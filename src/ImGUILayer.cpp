#include "ImGUILayer.hpp"

#include <iostream>
#include "imgui.h"

void ui::ImGUILayer::init(common::TextureLoader loader)
{
    this->_isShutdown = false;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendPlatformName = "CustomCore";
    io.BackendRendererName = "CustomRenderer";

    unsigned char* pixels = nullptr;
    int width = 0, height = 0;
    this->getFontData(&pixels, &width, &height);
    unsigned int id = loader(pixels, width, height);

    this->setFontTextureID(id);

    io.Fonts->ClearTexData();

    this->_setupStyle();
}

void ui::ImGUILayer::beginFrame(float delta_time, float width, float height)
{
    ImGuiIO& io = ImGui::GetIO();

    io.DeltaTime = delta_time;
    io.DisplaySize = ImVec2(width, height);

    ImGui::NewFrame();
}

common::RenderDataBuffer& ui::ImGUILayer::getFrame()
{
    this->_mainMenu();
    ImGui::Render();
    ImDrawData* drawData = ImGui::GetDrawData();
    return convertToUIRenderData(drawData);
}

common::RenderDataBuffer& ui::ImGUILayer::convertToUIRenderData(ImDrawData* drawData)
{
    this->_buffer.vertices.clear();
    this->_buffer.indices.clear();
    this->_buffer.commands.clear();
    for (size_t i = 0; i < drawData->CmdListsCount; i += 1) {
        ImDrawList* cmdList = drawData->CmdLists[i];

        auto vertexOffset = static_cast<uint32_t>(this->_buffer.vertices.size());
        
        auto indexBaseOffset = static_cast<uint32_t>(this->_buffer.indices.size());

        this->_recoverVertex(*cmdList);
        this->_recoverIndices(*cmdList, vertexOffset);
        
        this->_recoverCommands(*cmdList, indexBaseOffset);
    }
    return this->_buffer;
}

void ui::ImGUILayer::shutdown()
{
    if (ImGui::GetCurrentContext() != nullptr)
        ImGui::DestroyContext();
    this->_isShutdown = true;
}

void ui::ImGUILayer::getFontData(unsigned char** pixels, int* width, int* height)
{
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    ImFont* font = io.Fonts->AddFontFromFileTTF("./UI/font/Philosopher-Regular.ttf", 28.0f);
    if (font == nullptr) {
        std::cout << "Font not load" << std::endl;
    }
    io.Fonts->GetTexDataAsRGBA32(pixels, width, height);
}

void ui::ImGUILayer::setFontTextureID(unsigned int id)
{
    this->_fontTextureId = id;
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->SetTexID((ImTextureID)(intptr_t)id);
    std::cout << "ID: " << id << std::endl;
}

void ui::ImGUILayer::_recoverVertex(ImDrawList& cmdList)
{
    for (size_t j = 0; j < cmdList.VtxBuffer.size(); j += 1) {
        common::Vertex vertex{};
        vertex.x = cmdList.VtxBuffer[j].pos.x;
        vertex.y = cmdList.VtxBuffer[j].pos.y;
        vertex.u = cmdList.VtxBuffer[j].uv.x;
        vertex.v = cmdList.VtxBuffer[j].uv.y;
        vertex.color = cmdList.VtxBuffer[j].col;
        this->_buffer.vertices.push_back(vertex);
    }
}

void ui::ImGUILayer::_recoverIndices(ImDrawList& cmdList, uint32_t vertexOffset)
{
    for (size_t j = 0; j < cmdList.IdxBuffer.size(); j += 1) {
        this->_buffer.indices.push_back(cmdList.IdxBuffer[j] + vertexOffset);
    }
}

void ui::ImGUILayer::_recoverCommands(ImDrawList& cmdList, uint32_t indexBaseOffset)
{
    for (size_t j = 0; j < cmdList.CmdBuffer.size(); j += 1) {
        const ImDrawCmd& cmd = cmdList.CmdBuffer[j];
        
        common::DrawCmd drawCmd{};
        drawCmd.indexOffset = indexBaseOffset + cmd.IdxOffset;
        drawCmd.elementCount = cmd.ElemCount;
        
        drawCmd.textureID = (uint32_t)(intptr_t)cmd.GetTexID();
        
        drawCmd.clipX = cmd.ClipRect.x;
        drawCmd.clipY = cmd.ClipRect.y;
        drawCmd.clipZ = cmd.ClipRect.z;
        drawCmd.clipW = cmd.ClipRect.w;
        
        this->_buffer.commands.push_back(drawCmd);
    }
}

void ui::ImGUILayer::_setupStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.ScrollbarRounding = 6.0f;
    style.WindowBorderSize = 1.0f;
    style.FontSizeBase = 28.0f;

    ImVec4* colors = ImGui::GetStyle().Colors;

    // Temp Colors to test if its correct
    colors[ImGuiCol_Text] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.12f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.2f, 0.3f, 0.6f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.4f, 0.8f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.2f, 0.5f, 1.0f);
}

void ui::ImGUILayer::_mainMenu()
{
    ImGuiIO& io = ImGui::GetIO();

    float width = io.DisplaySize.x * 0.25f;
    float height = io.DisplaySize.y;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGui::Begin("Main Menu", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Orbital Engine");
    ImGui::Separator();
    ImGui::Text("Test main menu sayin he loves Axel !");
    if (ImGui::Button("Place holders Button"))
        std::cout << "First Button Pressed !" << std::endl;
    if (ImGui::Button("Second Place holders Button"))
        std::cout << "Second Button Pressed !" << std::endl;
    ImGui::End();
}
