#pragma once

#include <cstdint>
#include <vector>

namespace ui {
    // Represents a single vertex used for rendering (triangles).
    struct Vertex {

        // Screen-space position of the vertex
        float x;
        float y;

        // Texture coordinates (UV mapping)
        // Used to sample a texture (font atlas, icons, images, etc.)
        // Range is [0, 1].
        float u;
        float v;

        // Packed RGBA color
        uint32_t color;
    };

    // A renderer will iterate through these commands to perform draw calls (represent single draw command).
    struct DrawCmd {

        // Offset inside the index buffer where this draw call begins.
        uint32_t indexOffset;

        // Number of indices to render for this command.
        uint32_t elementCount;

        // Identifier of the texture used for this draw call.
        uint64_t textureID;

        // Clipping rectangle (scissor region) in screen space.
        float clipX; // left
        float clipY; // top
        float clipZ; // right
        float clipW; // bottom
    };

    // Contains the full set of rendering data produced by the UI system (for a single frame)
    struct RenderDrawData {

        // Vertex buffer containing all UI vertices for the frame.
        std::vector<Vertex> vertices;

        // Index buffer describing how vertices form triangles.
        std::vector<uint32_t> indices;

        // List of draw commands describing how to render the buffers with different textures
        std::vector<DrawCmd> commands;
    };
}