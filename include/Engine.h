#pragma once
#include <ScypLib/Graphics.h>
#include <ScypLib/Audio.h>
#include <ScypLib/Window.h>
#include <ScypLib/Mouse.h>
#include <ScypLib/Keyboard.h>
#include <ScypLib/EventDispatcher.h>
#include <ScypLib/EntityComponentSystem.h>
#include <ScypLib/FrameTimer.h>
#include <memory>
#include <string>

#undef min
#undef max
#undef DrawText

namespace se
{
    class Game
    {
    public:
        Game() = default;
        virtual ~Game() = default;
        virtual void OnBegin() {}
        virtual void OnUpdate(float dt) {}
        virtual void OnEnd() {}
    };

    class Engine
    {
    public:
        static inline void Init(int windowWidth, int windowHeight, const std::string& windowTitle)
        {
            window = new sl::Window(windowTitle.c_str(), windowWidth, windowHeight, 0);
            graphics = new sl::Graphics(window);
            audio = new sl::Audio;
            mouse = new sl::Mouse;
            keyboard = new sl::Keyboard;
            ed = new sl::EventDispatcher(keyboard, mouse, window);
            ed->SetupCallbacks(window->GetGLFWWindow());
            ecs = new sl::EntityComponentSystem;

            game->OnBegin();
            running = true;
        }

        template<typename TGame>
        static inline void CreateGame()
        {
            game = std::make_unique<TGame>();
        }

        static inline void Shutdown()
        {
            game->OnEnd();
            game.reset();

            delete graphics; graphics = nullptr;
            delete audio;    audio = nullptr;
            delete window;   window = nullptr;
            delete mouse;    mouse = nullptr;
            delete keyboard; keyboard = nullptr;
            delete ed;       ed = nullptr;
            delete ecs;      ecs = nullptr;
        }

        static inline void Run()
        {
            while (running && window->IsRunning())
            {
                float dt = frameTimer.Mark();
                ed->PollEvents();

                graphics->BeginFrame();
                game->OnUpdate(dt);
                ecs->GetCurrentScene()->RunSystems(dt);
                graphics->EndFrame();
            }
        }

        static inline sl::Graphics& GetGraphics() { return *graphics; }
        static inline sl::Audio& GetAudio() { return *audio; }
        static inline sl::Window& GetWindow() { return *window; }
        static inline sl::Mouse& GetMouse() { return *mouse; }
        static inline sl::Keyboard& GetKeyboard() { return *keyboard; }
        static inline sl::EntityComponentSystem& GetECS() { return *ecs; }
        static inline void PollEvents() { ed->PollEvents(); }

    private:
        static inline sl::Graphics* graphics = nullptr;
        static inline sl::Audio* audio = nullptr;
        static inline sl::Window* window = nullptr;
        static inline sl::Mouse* mouse = nullptr;
        static inline sl::Keyboard* keyboard = nullptr;
        static inline sl::EventDispatcher* ed = nullptr;
        static inline sl::EntityComponentSystem* ecs = nullptr;
        static inline sl::FrameTimer frameTimer{};
        static inline std::unique_ptr<Game> game = nullptr;
        static inline bool running = false;
    };
}
