#include "Display.h"


Display::Display() {
    // Get resolution of primary monitor
    int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
    int desktopHeight = GetSystemMetrics(SM_CYSCREEN);

    this->window = SDL_CreateWindow("SDL Transparent Window",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          desktopWidth, desktopHeight, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);


    // Set background color to magenta and clear screen
    SDL_SetRenderDrawColor(this->renderer, 255, 0, 255, 255);
    SDL_RenderClear(this->renderer);

    // Draw blue square in top-left corner
    SDL_Rect rect1 = { 0, 0, 100, 100 };
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(this->renderer, &rect1);

    // Draw red square in center of the screen
    SDL_Rect rect2 = { (desktopWidth - 100) / 2, (desktopHeight - 100) / 2, 100, 100 };
    SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(this->renderer, &rect2);

    // Add window transparency (Magenta will be see-through)
    // Get window handle (https://stackoverflow.com/a/24118145/3357935)
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);  // Initialize wmInfo
    SDL_GetWindowWMInfo(this->window, &wmInfo);
    HWND hWnd = wmInfo.info.win.window;

    // Change window type to layered (https://stackoverflow.com/a/3970218/3357935)
    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    // Set transparency color
    SetLayeredWindowAttributes(hWnd, RGB(255,0,255), 0, LWA_COLORKEY);

    // Render the square to the screen
    SDL_RenderPresent(this->renderer);
}

Display::~Display() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}
