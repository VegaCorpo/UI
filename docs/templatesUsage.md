# Documentation — UI Template System (ImGui)

## Table of Contents

1. [Overview](#overview)
2. [Architecture](#architecture)
3. [How the Registry System (Factory) Works](#how-the-registry-system-factory-works)
4. [Adding a New Interface](#adding-a-new-interface)
5. [Using an Interface in `ImGUILayer`](#using-an-interface-in-imguilayer)
6. [Positioning and Sizing a Window](#positioning-and-sizing-a-window)
7. [Common Pitfalls](#common-pitfalls)
8. [Summary — Quick Checklist](#summary--quick-checklist)

---

## Overview

The template system allows defining multiple types of independent ImGui-based graphical interfaces, selectable **dynamically at runtime** from a type (`templateType`), without the calling code needing to know the concrete class of the interface it is using.

This system relies on three pillars:

- A **common interface** (`ITemplateContent`) that every interface must implement.
- A **default base class** (`ATemplateContent`) that provides the default behavior.
- A **factory with a dynamic registry** (`TemplateContentFactory`) that builds the correct interface from a type, without needing to modify the factory every time a new interface is added.

---

## Architecture

```
templates/
├── TemplateType.hpp              # Enum of all available interface types
├── ITemplateContent.hpp          # Common interface shared by all interfaces
├── ATemplateContent.hpp / .cpp   # Default interface (DEFAULT)
├── TemplateContentFactory.hpp    # Factory + registry declaration
├── TemplateContentFactory.cpp    # Factory + registry implementation
└── lib/
    ├── InfoInterfaceContent.hpp / .cpp   # Example of an additional interface
    └── ...                                # Other custom interfaces
```

### `TemplateType.hpp`

Contains the enum listing every interface type available in the project. **Every new interface must be added here.**

```cpp
#pragma once

namespace ui {
enum templateType {
    DEFAULT,
    INFO_INTERFACE,
    // Add your new types here
};
}
```

### `ITemplateContent.hpp`

Abstract interface (pure virtual class) that **every** interface must comply with. It defines the minimal contract: a `renderWidgets` method capable of drawing the window's content.

```cpp
#pragma once
#include <imgui.h>

namespace ui {
class ITemplateContent {
public:
    virtual ~ITemplateContent() = default;
    virtual void renderWidgets(const char *windowTitle,
                                ImVec2 position,
                                ImVec2 size,
                                ImGuiCond condition) = 0;
};
}
```

> ⚠️ The destructor **must** be `virtual` on the base interface, otherwise destroying an object through a `std::unique_ptr<ITemplateContent>` will not correctly release the derived class's resources (undefined behavior).

### `ATemplateContent.hpp` / `.cpp`

Base class implementing `ITemplateContent` and representing the **default** interface (`DEFAULT`). It is also the parent class of every custom interface located in the `lib/` folder.

```cpp
// ATemplateContent.hpp
#pragma once
#include "ITemplateContent.hpp"

namespace ui {
class ATemplateContent : public ITemplateContent {
public:
    ATemplateContent() = default;
    ~ATemplateContent() override = default;
    void renderWidgets(const char *windowTitle,
                        ImVec2 position,
                        ImVec2 size,
                        ImGuiCond condition) override;

private:
    float _f = 0.0f;
    int _counter = 0;
};
}
```

```cpp
// ATemplateContent.cpp
#include "ATemplateContent.hpp"

void ui::ATemplateContent::renderWidgets(const char *windowTitle,
                                          ImVec2 position,
                                          ImVec2 size,
                                          ImGuiCond condition) {
    ImGui::SetNextWindowPos(position, condition);
    ImGui::SetNextWindowSize(size, condition);

    ImGui::Begin(windowTitle);
    ImGui::Text("This is some useful text.");

    ImGui::SliderFloat("float", &_f, 0.0f, 1.0f);

    if (ImGui::Button("Button")) {
        _counter++;
    }

    ImGui::SameLine();
    ImGui::Text("counter = %d", _counter);
    ImGui::End();
}
```

> ℹ️ State variables such as `_f` and `_counter` are **instance members**, never `static` locals inside the function. A `static` variable declared inside a method is shared across **every** call to that method, regardless of which instance calls it — which would cause the bug where moving a slider on one interface changes the displayed value on every other instance of the same interface. By storing the state in member variables, each content instance keeps its own independent state.

---

## How the Registry System (Factory) Works

Rather than using a central `switch` statement that would need to be modified every time a new interface is added (violating the *Open/Closed* principle), the system uses a **dynamic registry**: each interface registers itself with the factory when the program starts.

### `TemplateContentFactory.hpp`

```cpp
#pragma once
#include <memory>
#include <functional>
#include "ITemplateContent.hpp"
#include "TemplateType.hpp"

namespace ui {

using ContentCreator = std::function<std::unique_ptr<ITemplateContent>()>;

// Allows an interface to register itself with the factory
void registerTemplateContent(templateType type, ContentCreator creator);

// Builds the interface matching the requested type
std::unique_ptr<ITemplateContent> makeTemplateContent(templateType type);

}
```

### `TemplateContentFactory.cpp`

```cpp
#include "TemplateContentFactory.hpp"
#include "ATemplateContent.hpp"

namespace ui {

// Function-local singleton (Meyer's Singleton): guarantees safe initialization
// regardless of the loading order of the project's .cpp files.
static std::unordered_map<templateType, ContentCreator>& registry() {
    static std::unordered_map<templateType, ContentCreator> instance;
    return instance;
}

void registerTemplateContent(templateType type, ContentCreator creator) {
    registry()[type] = std::move(creator);
}

std::unique_ptr<ITemplateContent> makeTemplateContent(templateType type) {
    auto it = registry().find(type);
    if (it != registry().end()) {
        return it->second();
    }
    return std::make_unique<ATemplateContent>(); // Default fallback
}

}
```

### How it works in practice

1. Every interface (other than `DEFAULT`) registers itself in the registry through an `AutoRegister` block (see next section).
2. This registration happens **automatically when the program loads**, before `main()` even runs, thanks to a global variable whose constructor performs the registration.
3. When `makeTemplateContent(type)` is called, the factory looks up the registry: if an interface has been registered for that `type`, it is built and returned; otherwise, the default interface (`ATemplateContent`) is used as a fallback.

---

## Adding a New Interface

Adding a new interface to the system requires **three steps**:

### Step 1 — Add the type in `TemplateType.hpp`

```cpp
namespace ui {
enum templateType {
    DEFAULT,
    INFO_INTERFACE,
    MAIN_INTERFACE, // <- new type added
};
}
```

### Step 2 — Create the new interface's header (in `lib/`)

```cpp
// lib/MainInterfaceContent.hpp
#pragma once
#include "../ATemplateContent.hpp"

namespace ui {
class MainInterfaceContent : public ATemplateContent {
public:
    void renderWidgets(const char *windowTitle,
                        ImVec2 position,
                        ImVec2 size,
                        ImGuiCond condition) override;
};
}
```

### Step 3 — Create the `.cpp` file with the `AutoRegister` block

This is **the most important step, and the one most often forgotten**. Without this block, the new interface will **never** be known to the factory, and `makeTemplateContent` will consistently fall back to the default interface.

```cpp
// lib/MainInterfaceContent.cpp
#include "MainInterfaceContent.hpp"
#include "../TemplateContentFactory.hpp"
#include "../TemplateType.hpp"

void ui::MainInterfaceContent::renderWidgets(const char *windowTitle,
                                              ImVec2 position,
                                              ImVec2 size,
                                              ImGuiCond condition) {
    ImGui::SetNextWindowPos(position, condition);
    ImGui::SetNextWindowSize(size, condition);

    ImGui::Begin(windowTitle);
    ImGui::TextWrapped("Content specific to the Main interface.");
    ImGui::End();
}

// Auto-registration block — MANDATORY
namespace {
    struct AutoRegister {
        AutoRegister() {
            ui::registerTemplateContent(ui::MAIN_INTERFACE, [] {
                return std::make_unique<ui::MainInterfaceContent>();
            });
        }
    } autoRegister;
}
```

> ⚠️ **Critical points to remember:**
>
> - The `AutoRegister` block must be a **global variable** in the `.cpp` file (inside an anonymous `namespace`), **never** an instance member of the class. An instance member would only be constructed once an object of that class already exists — creating a chicken-and-egg problem (you'd need to already be able to construct the interface in order to register it, when registration is precisely what allows it to be constructed).
> - The anonymous `namespace` gives the `AutoRegister` block **internal linkage**: this prevents any naming conflict with other `.cpp` files in the project that also declare an `AutoRegister` struct. Without this protection, the linker would detect duplicate symbols across the different files.
> - The new interface's `.cpp` file **must be included in the build** (listed in `CMakeLists.txt`, via `add_library`/`target_sources`, or a `GLOB`). A header alone (`.hpp`), if not included in any compiled `.cpp`, generates no object code — the `AutoRegister` block will therefore never run, and the interface will remain invisible to the factory.

---

## Using an Interface in `ImGUILayer`

### Step 1 — Declare a member variable for each frame instance

Every interface being displayed must have **its own instance**, stored as a **class member** (of `ImGUILayer`), rather than recreated on every frame. This ensures each interface's internal state (counters, slider values, etc.) persists correctly across frames, and that two instances of the same interface (e.g. two `DEFAULT` windows) do not share their state.

```cpp
// ImGUILayer.hpp
private:
    std::unique_ptr<ui::ITemplateContent> _context1;
    std::unique_ptr<ui::ITemplateContent> _infos1;
```

> ℹ️ **Why one variable per frame?** If the instance were recreated on every call to `render()` (a local variable inside the function), its state would be reset every frame. And if the state were stored in a `static` variable inside `renderWidgets` instead of a class member, that state would be shared across **all** instances of that interface (for example, moving a slider on one window would change the same value displayed on another window of the same type).

### Step 2 — Create the instance in `init()`

The instance should be created **only once**, typically in an initialization method, by calling `makeTemplateContent` with the desired type:

```cpp
void ui::ImGUILayer::init(GLFWwindow* window)
{
    this->_window = window;
    this->_isShutdown = false;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    this->_context1 = ui::makeTemplateContent(ui::templateType::DEFAULT);
    this->_infos1   = ui::makeTemplateContent(ui::templateType::INFO_INTERFACE);
}
```

### Step 3 — Call `renderWidgets` in `render()`

The ImGui frame cycle (`NewFrame` / `Render`) must be handled **only once per real frame**, in `ImGUILayer::render()` — never inside the interfaces' own content. Each interface only draws its own content between this cycle.

```cpp
void ui::ImGUILayer::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    this->_context1->renderWidgets("Context 1",
                                    ImVec2(50, 50), ImVec2(300, 150),
                                    ImGuiCond_FirstUseEver);

    this->_infos1->renderWidgets("Info 1",
                                  ImVec2(400, 50), ImVec2(300, 150),
                                  ImGuiCond_FirstUseEver);

    ImGui::Render();

    ImDrawData* drawData = ImGui::GetDrawData();
    if (!drawData) {
        return;
    }

    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(this->_window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    ImGui_ImplOpenGL3_RenderDrawData(drawData);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}
```

> ⚠️ **Strict ImGui rule**: only one `NewFrame()` / `Render()` pair per displayed frame, no matter how many windows (`Begin`/`End`) are opened in between. Calling `NewFrame()` multiple times per frame corrupts the internal input state (mouse, clicks, dragging), making widgets unclickable or undraggable.

---

## Positioning and Sizing a Window

The `renderWidgets` method takes four parameters: the title, the position, the size, and the condition under which they apply.

```cpp
void renderWidgets(const char *windowTitle, ImVec2 position, ImVec2 size, ImGuiCond condition);
```

### The `condition` Parameter (`ImGuiCond`)

Determines **when** the position/size is applied:

| Value | Behavior |
|---|---|
| `ImGuiCond_Always` | Forces the position/size on **every frame**; the user can no longer move or resize the window manually |
| `ImGuiCond_FirstUseEver` | Applied only on the very first appearance; the user can then freely move/resize it afterward |
| `ImGuiCond_Once` | Applied only once per program run |
| `ImGuiCond_Appearing` | Applied every time the window reappears after being closed |

### Example: free-floating window (movable/resizable after the first display)

```cpp
this->_context1->renderWidgets("Context 1",
                                ImVec2(50, 50), ImVec2(300, 150),
                                ImGuiCond_FirstUseEver);
```

### Example: fully locked window

To prevent the user from moving or resizing the window at all, combine `ImGuiCond_Always` with the appropriate flags on `ImGui::Begin` (to be added inside the `renderWidgets` implementation if this behavior is needed):

```cpp
ImGui::Begin(windowTitle, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
```

---

## Common Pitfalls

| Symptom | Likely Cause | Solution |
|---|---|---|
| A counter/slider on one interface affects another instance of the same interface | State variable declared as a `static` local inside the method instead of an instance member | Move the state into a private member of the class |
| Widgets on one of two displayed interfaces can't be clicked or moved | `ImGui::NewFrame()` / `ImGui::Render()` called more than once per frame | Only one `NewFrame`/`Render` pair per frame, inside `ImGUILayer::render()` only |
| The counter resets to zero every frame | The interface instance is recreated on every call to `render()` (local variable) instead of being stored as a member | Create the instance once in `init()`, store it as a class member |
| A new interface (`lib/`) is never used; the factory always falls back to `DEFAULT` | The interface's `.cpp` file isn't included in any compilation unit (missing from `CMakeLists.txt`), or the `AutoRegister` block is an instance member instead of a global variable | Check the `.cpp` is listed in `CMakeLists.txt`; make sure `AutoRegister` is declared inside an anonymous `namespace`, at file scope |
| Linker error: duplicate symbol `AutoRegister` | The `AutoRegister` block isn't protected by an anonymous `namespace` in one of the files | Wrap the `struct AutoRegister { ... } autoRegister;` block in `namespace { ... }` |
| Text overflows the window | `ImGui::Text` does not wrap automatically | Use `ImGui::TextWrapped` instead |

---

## Summary — Quick Checklist

To add a new interface to the system:

- Add the new type to the `templateType` enum (`TemplateType.hpp`)
- Create the class header in `lib/`, inheriting from `ATemplateContent`
- Create the corresponding `.cpp`, implementing `renderWidgets`
- Add the `AutoRegister` block inside an anonymous `namespace`, as a global variable in the `.cpp`
- Verify the `.cpp` is included in `CMakeLists.txt`
- Store the interface's internal state (counters, values, etc.) as **instance members**, never as local `static`
- In `ImGUILayer`, declare a `std::unique_ptr<ITemplateContent>` member for each instance to display
- Create the instance only once via `makeTemplateContent(type)`, inside `init()`
- Call `renderWidgets(title, position, size, condition)` inside `render()`, between a single `NewFrame`/`Render` pair