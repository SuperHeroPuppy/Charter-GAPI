#include "charter_gapi.h"
#include <stdio.h>
#include <wchar.h>

int main(void) {
    HINSTANCE instance = GetModuleHandleW(NULL);
    WNDCLASSW cls = {0};
    cls.lpfnWndProc = DefWindowProcW;
    cls.hInstance = instance;
    cls.lpszClassName = L"CharterGapiSmokeWindow";
    if (!RegisterClassW(&cls)) return 1;
    HWND parent = CreateWindowW(cls.lpszClassName, L"Smoke", WS_OVERLAPPEDWINDOW,
                                0, 0, 500, 300, NULL, NULL, instance, NULL);
    HWND child = CreateWindowW(L"STATIC", L"Old", WS_CHILD | WS_VISIBLE,
                               0, 0, 40, 20, parent, NULL, instance, NULL);
    if (!parent || !child) return 2;

    CGapiLayout layout;
    cgapi_layout_begin(&layout, parent, 1);
    if (!cgapi_layout_move(&layout, child, 20, 30, 150, 40) ||
        !cgapi_layout_end(&layout)) return 3;
    RECT actual;
    GetWindowRect(child, &actual);
    MapWindowPoints(HWND_DESKTOP, parent, (POINT *)&actual, 2);
    if (actual.left != 20 || actual.top != 30 ||
        actual.right - actual.left != 150 ||
        actual.bottom - actual.top != 40) return 4;

    if (!cgapi_set_text(child, L"Ready")) return 5;
    wchar_t label[32];
    GetWindowTextW(child, label, 32);
    if (wcscmp(label, L"Ready") != 0 || cgapi_set_text(child, L"Ready"))
        return 6;
    if (!cgapi_set_visible(child, FALSE) ||
        (GetWindowLongPtrW(child, GWL_STYLE) & WS_VISIBLE)) return 7;
    if (cgapi_set_visible(child, FALSE) || !cgapi_set_visible(child, TRUE))
        return 8;
    DestroyWindow(parent);
    puts("CharterGAPI smoke test passed");
    return 0;
}
