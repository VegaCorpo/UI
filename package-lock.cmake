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
    GIT_TAG main
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
)
