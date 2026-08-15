# Dear Imgui
CPMDeclarePackage(ImGui
    GIT_TAG v1.92.6
    GITHUB_REPOSITORY ocornut/imgui
    DOWNLOAD_ONLY YES
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)

#Common
CPMDeclarePackage(Common
    GITHUB_REPOSITORY VegaCorpo/Common
    GIT_TAG v0.1.0
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)

# GLFW
CPMDeclarePackage(glfw
    GITHUB_REPOSITORY glfw/glfw
    GIT_TAG 3.4
    OPTIONS
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_DOCS OFF"
        "BUILD_SHARED_LIBS ON"
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)