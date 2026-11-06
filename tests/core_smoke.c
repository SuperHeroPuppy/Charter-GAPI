#include "charter_gapi_core.h"
#include <assert.h>

int main(void) {
    CGapiPalette palette = cgapi_palette_default_dark();
    assert(cgapi_color_argb32(palette.accent) == 0xfff5a60cU);
    assert(cgapi_metrics_for_width(400).sidebar_width == 0);
    assert(cgapi_metrics_for_width(800).sidebar_width == 260);
    assert(cgapi_metrics_for_width(1200).sidebar_width == 300);
    CGapiColor mixed = cgapi_color_blend((CGapiColor){0, 0, 0, 255},
                                         (CGapiColor){200, 100, 50, 255}, 50);
    assert(mixed.red == 100 && mixed.green == 50 && mixed.blue == 25);
    return 0;
}
