#pragma once

#define WLR_USE_UNSTABLE

#include "globals.hpp"

class CMonitor;

class CWhichKeyWindow {
  public:
    CWhichKeyWindow(PHLWORKSPACE startedOn_);
    ~CWhichKeyWindow();

    void render();
    void damage();
    void onDamageReported();
    void onPreRender();

    // close without a selection
    void      close();

    bool      blockOverviewRendering = false;
    bool      blockDamageReporting   = false;

    CMonitor* pMonitor = nullptr;

  private:
    int          SIDE_LENGTH = 3;
    int          GAP_WIDTH   = 5;
    CColor       BG_COLOR    = CColor{0.1, 0.1, 0.1, 1.0};

    bool         damageDirty = false;

    int          openedID  = -1;
    int          closeOnID = -1;

    PHLWORKSPACE startedOn;

    bool         closing = false;
};

inline std::unique_ptr<CWhichKeyWindow> g_pWhichKeyWindow;
