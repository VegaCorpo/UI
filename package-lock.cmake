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
    GIT_TAG main
    GITHUB_REPOSITORY VegaCorpo/Common
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
    DOWNLOAD_ONLY YES
)