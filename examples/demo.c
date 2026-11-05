#include "charter_gapi.h"

static HWND button;
static HWND edit;

static LRESULT CALLBACK demo_proc(HWND window, UINT message,
                                  WPARAM wparam, LPARAM lparam) {
    (void)lparam;
    switch (message) {
        case WM_CREATE:
            button = CreateWindowW(L"BUTTON", L"Search", WS_CHILD | WS_VISIBLE,
                                   0, 0, 120, 36, window, (HMENU)1, NULL, NULL);
            edit = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE |
                                 WS_BORDER | ES_AUTOHSCROLL,
                                 0, 0, 300, 36, window, (HMENU)2, NULL, NULL);
            return 0;
        case WM_SIZE: {
            int width = LOWORD(lparam);
            CGapiLayout layout;
            cgapi_layout_begin(&layout, window, 2);
            cgapi_layout_move(&layout, button, 16, 16, 120, 36);
            cgapi_layout_move(&layout, edit, 144, 16,
                              width > 160 ? width - 160 : 0, 36);
            cgapi_layout_end(&layout);
            return 0;
        }
        case WM_COMMAND:
            if (LOWORD(wparam) == 1) {
                cgapi_set_text(button, L"Clicked");
                return 0;
            }
            break;
        case WM_PAINT: {
            CGapiPaint frame;
            if (cgapi_paint_begin(&frame, window)) {
                RECT client;
                GetClientRect(window, &client);
                cgapi_fill_round_rect(cgapi_paint_dc(&frame), client, 8,
                                      RGB(32, 32, 32));
                cgapi_paint_end(&frame);
            }
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(window, message, wparam, lparam);
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE previous,
                    PWSTR command, int show) {
    (void)previous;
    (void)command;
    WNDCLASSW cls = {0};
    cls.lpfnWndProc = demo_proc;
    cls.hInstance = instance;
    cls.lpszClassName = L"CharterGapiDemo";
    cls.hCursor = LoadCursorW(NULL, (LPCWSTR)IDC_ARROW);
    if (!RegisterClassW(&cls)) return 1;
    HWND window = CreateWindowW(cls.lpszClassName, L"CharterGAPI demo",
                                WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                                CW_USEDEFAULT, CW_USEDEFAULT, 560, 180,
                                NULL, NULL, instance, NULL);
    if (!window) return 1;
    ShowWindow(window, show);
    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}
