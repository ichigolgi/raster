#pragma once
#include "Scene.h"
#include "Texture.h"

class CEngine {
   public:
    //
    struct InitializeContext {
        HWND hwnd;
    };
    //
    struct UpdateContext {};
    //
    struct DrawContext {};

   public:
    CEngine() {}
    ~CEngine() {}

    //
    void Initialize(InitializeContext &initialize_context);
    //
    void Finalize();
    //
    void Update(UpdateContext &update_context);
    //
    void Draw(DrawContext &draw_context);

   private:
    //
    void UpdateWindowRequest(UpdateContext &update_context);
    //
    void DrawModel(DrawContext &draw_context);
    //
    void DrawBackbuffer(DrawContext &draw_context);

   private:
    CTexture m_backbuffer_texture;
    HBITMAP m_hbitmap;
    BITMAPINFO *m_pbitmapinfo{};
    HWND m_hwnd;
    bool m_is_initialized{false};
    CScene m_scene{};
};