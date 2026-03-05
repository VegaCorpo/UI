#include "ImGUILayer.hpp"

ui::ImGUILayer::ImGUILayer()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();

    // Create custom backends
    io.BackendPlatformName = "CustomCore";
    io.BackendRendererName = "CustomRenderer";
}

void ui::ImGUILayer::beginFrame(float delta_time, float width, float height)
{
    ImGuiIO& io = ImGui::GetIO();

    io.DeltaTime = delta_time;
    io.DisplaySize = ImVec2(width, height);

    ImGui::NewFrame();
}

ui::RenderDrawData& ui::ImGUILayer::getFrame()
{
    ImGui::Render();
    ImDrawData* drawData = ImGui::GetDrawData();
    return convertToUIRenderData(drawData);
}

ui::RenderDrawData& ui::ImGUILayer::convertToUIRenderData(ImDrawData* drawData)
{

    this->_buffer.vertices.clear();
    this->_buffer.indices.clear();
    this->_buffer.commands.clear();
    for (size_t i = 0; i < drawData->CmdListsCount; i += 1) {
        ImDrawList* cmdList = drawData->CmdLists[i];

        recoverVertex(*cmdList);

        uint32_t vertexOffset = _buffer.vertices.size() - cmdList->VtxBuffer.size();
        recoverIndices(*cmdList, vertexOffset);

        recoverCommands(*cmdList);
    }
    return this->_buffer;
}

void ui::ImGUILayer::shutdown()
{
    ImGui::DestroyContext();
}

void ui::ImGUILayer::recoverVertex(ImDrawList& cmdList)
{
    for (size_t j = 0; j < cmdList.VtxBuffer.size(); j += 1) {
        Vertex vertex{};
        vertex.x = cmdList.VtxBuffer[j].pos.x;
        vertex.y = cmdList.VtxBuffer[j].pos.y;
        vertex.u = cmdList.VtxBuffer[j].uv.x;
        vertex.v = cmdList.VtxBuffer[j].uv.y;
        vertex.color = cmdList.VtxBuffer[j].col;
        this->_buffer.vertices.push_back(vertex);
    }
}

void ui::ImGUILayer::recoverIndices(ImDrawList& cmdList, uint32_t vertexOffset)
{
    for (size_t j = 0; j < cmdList.IdxBuffer.size(); j += 1) {
        this->_buffer.indices.push_back(cmdList.IdxBuffer[j] + vertexOffset);
    }
}

void ui::ImGUILayer::recoverCommands(ImDrawList& cmdList)
{
    for (size_t j = 0; j < cmdList.CmdBuffer.size(); j += 1) {
        DrawCmd drawCmd{};
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
