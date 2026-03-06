#include "ImGUILayer.hpp"

#include <iostream>

ui::ImGUILayer::ImGUILayer()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();

    // Create custom backends
    io.BackendPlatformName = "CustomCore";
    io.BackendRendererName = "CustomRenderer";

    // Setup Global style
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

        this->_recoverVertex(*cmdList);

        uint32_t vertexOffset = _buffer.vertices.size() - cmdList->VtxBuffer.size();
        this->_recoverIndices(*cmdList, vertexOffset);

        this->_recoverCommands(*cmdList);
    }
    return this->_buffer;
}

void ui::ImGUILayer::shutdown()
{
    ImGui::DestroyContext();
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

void ui::ImGUILayer::_recoverCommands(ImDrawList& cmdList)
{
    for (size_t j = 0; j < cmdList.CmdBuffer.size(); j += 1) {
        common::DrawCmd drawCmd{};
        drawCmd.indexOffset = cmdList.CmdBuffer[j].IdxOffset + static_cast<uint32_t>(_buffer.indices.size());
        drawCmd.elementCount = cmdList.CmdBuffer[j].ElemCount;
        drawCmd.textureID = cmdList.CmdBuffer[j].GetTexID();
        drawCmd.clipX = cmdList.CmdBuffer[j].ClipRect.x;
        drawCmd.clipY = cmdList.CmdBuffer[j].ClipRect.y;
        drawCmd.clipZ = cmdList.CmdBuffer[j].ClipRect.z;
        drawCmd.clipW = cmdList.CmdBuffer[j].ClipRect.w;
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

    ImVec4* colors = ImGui::GetStyle().Colors;

    // Temp Colors to test if its correct
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
