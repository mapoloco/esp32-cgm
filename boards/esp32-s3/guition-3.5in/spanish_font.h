/*
 * CGM Spanish glyph extension for LVGL 8.3.
 * Keeps LVGL's built-in Montserrat look, adding acute accents, diaeresis and ñ
 * at runtime so all Spanish glyphs render without squares.
 * Montserrat is distributed under the SIL Open Font License.
 */
#pragma once
#include <lvgl.h>

static bool cgm_es_map(uint32_t cp, uint32_t *base, uint8_t *mark) {
    *mark = 0;
    if (cp >= ' ' && cp <= '~') { *base = cp; return false; }
    switch (cp) {
        case 0x00E1: *base='a'; *mark=1; return true; // á
        case 0x00C1: *base='A'; *mark=1; return true; // Á
        case 0x00E9: *base='e'; *mark=1; return true;
        case 0x00C9: *base='E'; *mark=1; return true;
        case 0x00ED: *base='i'; *mark=1; return true;
        case 0x00CD: *base='I'; *mark=1; return true;
        case 0x00F3: *base='o'; *mark=1; return true;
        case 0x00D3: *base='O'; *mark=1; return true;
        case 0x00FA: *base='u'; *mark=1; return true;
        case 0x00DA: *base='U'; *mark=1; return true;
        case 0x00F1: *base='n'; *mark=2; return true; // ñ
        case 0x00D1: *base='N'; *mark=2; return true; // Ñ
        case 0x00FC: *base='u'; *mark=3; return true; // ü
        case 0x00DC: *base='U'; *mark=3; return true;
        case 0x00E0: *base='a'; *mark=1; return true; // Latin-1 accents
        case 0x00C0: *base='A'; *mark=1; return true;
        case 0x00E8: *base='e'; *mark=1; return true;
        case 0x00C8: *base='E'; *mark=1; return true;
        case 0x00EC: *base='i'; *mark=1; return true;
        case 0x00CC: *base='I'; *mark=1; return true;
        case 0x00F2: *base='o'; *mark=1; return true;
        case 0x00D2: *base='O'; *mark=1; return true;
        case 0x00F9: *base='u'; *mark=1; return true;
        case 0x00D9: *base='U'; *mark=1; return true;
        case 0x00E2: *base='a'; *mark=1; return true;
        case 0x00C2: *base='A'; *mark=1; return true;
        case 0x00EA: *base='e'; *mark=1; return true;
        case 0x00CA: *base='E'; *mark=1; return true;
        case 0x00EE: *base='i'; *mark=1; return true;
        case 0x00CE: *base='I'; *mark=1; return true;
        case 0x00F4: *base='o'; *mark=1; return true;
        case 0x00D4: *base='O'; *mark=1; return true;
        case 0x00FB: *base='u'; *mark=1; return true;
        case 0x00DB: *base='U'; *mark=1; return true;
        case 0x00E3: *base='a'; *mark=2; return true;
        case 0x00C3: *base='A'; *mark=2; return true;
        case 0x00F5: *base='o'; *mark=2; return true;
        case 0x00D5: *base='O'; *mark=2; return true;
        case 0x00E4: *base='a'; *mark=3; return true;
        case 0x00C4: *base='A'; *mark=3; return true;
        case 0x00EB: *base='e'; *mark=3; return true;
        case 0x00CB: *base='E'; *mark=3; return true;
        case 0x00EF: *base='i'; *mark=3; return true;
        case 0x00CF: *base='I'; *mark=3; return true;
        case 0x00F6: *base='o'; *mark=3; return true;
        case 0x00D6: *base='O'; *mark=3; return true;
        default: return false;
    }
}
static inline uint8_t cgm_es_get_px(const uint8_t *b, size_t p) {
    return (p & 1) ? (b[p >> 1] & 0x0F) : (b[p >> 1] >> 4);
}
static inline void cgm_es_set_px(uint8_t *b, size_t p, uint8_t v) {
    if (p & 1) b[p >> 1] = (b[p >> 1] & 0xF0) | (v & 0x0F);
    else b[p >> 1] = (b[p >> 1] & 0x0F) | ((v & 0x0F) << 4);
}
static bool cgm_es_get_dsc(const lv_font_t *font, lv_font_glyph_dsc_t *out,
                           uint32_t cp, uint32_t next) {
    uint32_t baseCp = 0; uint8_t mark = 0;
    if (!cgm_es_map(cp, &baseCp, &mark)) return false;
    const lv_font_t *baseFont = font->fallback;
    if (!baseFont) return false;
    lv_font_glyph_dsc_t baseDsc;
    if (!lv_font_get_glyph_dsc(baseFont, &baseDsc, baseCp, next)) return false;
    out->adv_w = baseDsc.adv_w;
    out->box_w = baseDsc.box_w + 2;
    out->box_h = baseDsc.box_h + 3;
    out->ofs_x = baseDsc.ofs_x - 1;
    out->ofs_y = baseDsc.ofs_y;
    out->bpp = baseDsc.bpp;
    out->is_placeholder = 0;
    return true;
}
static const uint8_t *cgm_es_get_bitmap(const lv_font_t *font, uint32_t cp) {
    uint32_t baseCp = 0; uint8_t mark = 0;
    if (!cgm_es_map(cp, &baseCp, &mark)) return nullptr;
    const lv_font_t *baseFont = font->fallback;
    if (!baseFont) return nullptr;
    lv_font_glyph_dsc_t d;
    if (!lv_font_get_glyph_dsc(baseFont, &d, baseCp, 0) || d.bpp != 4) return nullptr;
    const uint8_t *src = lv_font_get_glyph_bitmap(baseFont, baseCp);
    if (!src) return nullptr;
    const uint16_t w = d.box_w + 2, h = d.box_h + 3;
    static uint8_t buf[4096];
    const size_t pixels = (size_t)w * h;
    if (pixels > sizeof(buf) * 2) return nullptr;
    memset(buf, 0, (pixels + 1) / 2);
    for (uint16_t y = 0; y < d.box_h; ++y)
        for (uint16_t x = 0; x < d.box_w; ++x)
            cgm_es_set_px(buf, (size_t)(y + 3) * w + x + 1,
                          cgm_es_get_px(src, (size_t)y * d.box_w + x));
    auto px = [&](int x, int y, uint8_t value) {
        if (x >= 0 && x < w && y >= 0 && y < 3)
            cgm_es_set_px(buf, (size_t)y * w + x, value);
    };
    const int m = w / 2;
    if (mark == 1) {             // acute accent: rising diagonal
        px(m - 1, 2, 10); px(m, 1, 15); px(m + 1, 0, 12);
    } else if (mark == 2) {      // tilde: small wave for ñ
        px(m - 2, 1, 10); px(m - 1, 0, 15); px(m, 0, 15);
        px(m + 1, 1, 12); px(m + 2, 1, 10);
    } else if (mark == 3) {      // diaeresis
        px(m - 2, 0, 15); px(m - 2, 1, 15);
        px(m + 1, 0, 15); px(m + 1, 1, 15);
    }
    return buf;
}
#define CGM_ES_FONT(name, size) \
    static const lv_font_t name = { \
        .get_glyph_dsc = cgm_es_get_dsc, .get_glyph_bitmap = cgm_es_get_bitmap, \
        .line_height = lv_font_montserrat_##size.line_height, \
        .base_line = lv_font_montserrat_##size.base_line, .subpx = LV_FONT_SUBPX_NONE, \
        .underline_position = lv_font_montserrat_##size.underline_position, \
        .underline_thickness = lv_font_montserrat_##size.underline_thickness, \
        .dsc = NULL, .fallback = &lv_font_montserrat_##size \
    }
CGM_ES_FONT(cgm_font_es_10,10);
CGM_ES_FONT(cgm_font_es_12,12);
CGM_ES_FONT(cgm_font_es_14,14);
CGM_ES_FONT(cgm_font_es_16,16);
CGM_ES_FONT(cgm_font_es_18,18);
CGM_ES_FONT(cgm_font_es_20,20);
CGM_ES_FONT(cgm_font_es_22,22);
CGM_ES_FONT(cgm_font_es_28,28);
CGM_ES_FONT(cgm_font_es_48,48);
#undef CGM_ES_FONT
