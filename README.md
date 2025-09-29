# 🚀 ScypEngine

A lightweight **header-only 2D engine framework** built on top of [ScypLib](https://github.com/youruser/ScypLib).  
No complex build system required — just drop in the header and start coding.

---

## ✨ Features
- 🖼️ **Graphics**, 🎵 **Audio**, 🎮 **Input**, and 🪟 **Window** management
- 🧩 **Entity Component System (ECS)** for flexible game logic
- 📦 Simple `Game` lifecycle (`OnBegin`, `OnUpdate`, `OnEnd`)
- ⚡ **Single-header include** — minimal setup

---

## 📥 Installation

Clone or download the [ScypLib](https://github.com/youruser/ScypLib)
 repository and follow its installation instructions.
Once ScypLib is set up, you can include the ScypEngine header in your project:

```cpp
#include <ScypEngine/ScypEngine.h>
```
---
## 🕹️ How to use
```cpp
#include <ScypEngine/ScypEngine.h>

class MyGame : public se::Game
{
public:
    void OnBegin() override
    {
        // Initialize ECS, load assets, etc.
    }

    void OnUpdate(float dt) override
    {
        // Game loop logic here
    }

    void OnEnd() override
    {
        // Cleanup
    }
};

int main()
{
    se::Engine::CreateGame<MyGame>();
    se::Engine::Init(600, 800, "My Game");
    se::Engine::Run();
    se::Engine::Shutdown();
}
```
