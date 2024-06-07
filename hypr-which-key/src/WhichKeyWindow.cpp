#include "./WhichKeyWindow.hpp"
#include <hyprland/src/render/Renderer.hpp>
#include <hyprland/src/Compositor.hpp>
#define private public
#include <hyprland/src/render/OpenGL.hpp>
#undef private

static void damageMonitor(void*) {
    g_pWhichKeyWindow->damage();
}

static void removeOverview(void*) {
    g_pWhichKeyWindow.reset();
}

CWhichKeyWindow::~CWhichKeyWindow() {
    g_pHyprRenderer->makeEGLCurrent();
    // images.clear(); // otherwise we get a vram leak
    // g_pInputManager->unsetCursorImage();
    g_pHyprOpenGL->markBlurDirtyForMonitor(pMonitor);
}

CWhichKeyWindow::CWhichKeyWindow(PHLWORKSPACE startedOn_) {
    const auto PMONITOR = g_pCompositor->m_pLastMonitor.get();
    pMonitor            = PMONITOR;

    // SIDE_LENGTH =
    // GAP_WIDTH   =
    // BG_COLOR    =
}

void CWhichKeyWindow::render() {
    const auto GAPSIZE = (closing ? (1.0 - size.getPercent()) : size.getPercent()) * GAP_WIDTH;

    Vector2D   SIZE = size.value();

    Vector2D   tileSize       = (SIZE / SIDE_LENGTH);
    Vector2D   tileRenderSize = (SIZE - Vector2D{GAPSIZE, GAPSIZE} * (SIDE_LENGTH - 1)) / SIDE_LENGTH;

    g_pHyprOpenGL->clear(BG_COLOR.stripA());

    for (size_t y = 0; y < SIDE_LENGTH; ++y) {
        for (size_t x = 0; x < SIDE_LENGTH; ++x) {
            CBox texbox = {x * tileRenderSize.x + x * GAPSIZE, y * tileRenderSize.y + y * GAPSIZE, tileRenderSize.x, tileRenderSize.y};
            texbox.scale(pMonitor->scale).translate(pos.value());
            texbox.round();
            CRegion damage{0, 0, INT16_MAX, INT16_MAX};
            g_pHyprOpenGL->renderTextureInternalWithDamage(images[x + y * SIDE_LENGTH].fb.m_cTex, &texbox, 1.0, &damage);
        }
    }
}
