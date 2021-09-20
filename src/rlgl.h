#include <rlgl.h>

static Janet cfun_EnableDepthTest(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlEnableDepthTest();
    return janet_wrap_nil();
}

static Janet cfun_DisableDepthTest(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlDisableDepthTest();
    return janet_wrap_nil();
}

static Janet cfun_EnableBackfaceCulling(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlEnableBackfaceCulling();
    return janet_wrap_nil();
}

static Janet cfun_DisableBackfaceCulling(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlDisableBackfaceCulling();
    return janet_wrap_nil();
}

static Janet cfun_EnableDepthMask(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlEnableDepthMask();
    return janet_wrap_nil();
}

static Janet cfun_DisableDepthMask(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlDisableDepthMask();
    return janet_wrap_nil();
}

static Janet cfun_SetReverseWinding(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    SetReverseWinding(janet_getboolean(argv, 0));
    return janet_wrap_nil();
}


#include <OpenGL/gl.h>
static int getBlendFactor(const uint8_t *kw) {
    if (!janet_cstrcmp(kw, "zero")) {
        return GL_ZERO;
    } else if (!janet_cstrcmp(kw, "one")) {
        return GL_ONE;
    } else if (!janet_cstrcmp(kw, "src-color")) {
        return GL_SRC_COLOR;
    } else if (!janet_cstrcmp(kw, "one-minus-src-color")) {
        return GL_ONE_MINUS_SRC_COLOR;
    } else if (!janet_cstrcmp(kw, "dst-color")) {
        return GL_DST_COLOR;
    } else if (!janet_cstrcmp(kw, "one-minus-dst-color")) {
        return GL_ONE_MINUS_DST_COLOR;
    } else if (!janet_cstrcmp(kw, "src-alpha")) {
        return GL_SRC_ALPHA;
    } else if (!janet_cstrcmp(kw, "one-minus-src-alpha")) {
        return GL_ONE_MINUS_SRC_ALPHA;
    } else if (!janet_cstrcmp(kw, "dst-alpha")) {
        return GL_DST_ALPHA;
    } else if (!janet_cstrcmp(kw, "one-minus-dst-alpha")) {
        return GL_ONE_MINUS_DST_ALPHA;
    } else if (!janet_cstrcmp(kw, "constant-color")) {
        return GL_CONSTANT_COLOR;
    } else if (!janet_cstrcmp(kw, "one-minus-constant-color")) {
        return GL_ONE_MINUS_CONSTANT_COLOR;
    } else if (!janet_cstrcmp(kw, "constant-alpha")) {
        return GL_CONSTANT_ALPHA;
    } else if (!janet_cstrcmp(kw, "one-minus-constant-alpha")) {
        return GL_ONE_MINUS_CONSTANT_ALPHA;
    } else if (!janet_cstrcmp(kw, "src-alpha-saturate")) {
        return GL_SRC_ALPHA_SATURATE;
    } else {
        janet_panicf("unknown blend factor :%s", kw);
    }
}

// TODO: these are not actually valid for separate blend factors
static int getBlendFunction(const uint8_t *kw) {
    if (!janet_cstrcmp(kw, "add")) {
        return GL_FUNC_ADD;
    } else if (!janet_cstrcmp(kw, "subtract")) {
        return GL_FUNC_SUBTRACT;
    } else if (!janet_cstrcmp(kw, "reverse-subract")) {
        return GL_FUNC_REVERSE_SUBTRACT;
    } else if (!janet_cstrcmp(kw, "min")) {
        return GL_MIN;
    } else if (!janet_cstrcmp(kw, "max")) {
        return GL_MAX;
    } else {
        janet_panicf("unknown blend function :%s", kw);
    }
}

static Janet cfun_SetBlendFactors(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    int source_factor = getBlendFactor(janet_getkeyword(argv, 0));
    int dest_factor = getBlendFactor(janet_getkeyword(argv, 1));
    int function = getBlendFunction(janet_getkeyword(argv, 2));
    SetBlendFactors(source_factor, dest_factor, function);
    return janet_wrap_nil();
}

static Janet cfun_SetBlendFactorsSeparate(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    int source_factor_rgb = getBlendFactor(janet_getkeyword(argv, 0));
    int source_factor_alpha = getBlendFactor(janet_getkeyword(argv, 1));
    int dest_factor_rgb = getBlendFactor(janet_getkeyword(argv, 2));
    int dest_factor_alpha = getBlendFactor(janet_getkeyword(argv, 3));
    int function_rgb = getBlendFunction(janet_getkeyword(argv, 4));
    int function_alpha = getBlendFunction(janet_getkeyword(argv, 5));
    SetBlendFactorsSeparate(source_factor_rgb, source_factor_alpha, dest_factor_rgb, dest_factor_alpha, function_rgb, function_alpha);
    return janet_wrap_nil();
}

static JanetReg rlgl_cfuns[] = {
    {"enable-depth-test", cfun_EnableDepthTest, NULL},
    {"disable-depth-test", cfun_DisableDepthTest, NULL},
    {"enable-backface-culling", cfun_EnableBackfaceCulling, NULL},
    {"disable-backface-culling", cfun_DisableBackfaceCulling, NULL},
    {"enable-depth-mask", cfun_EnableDepthMask, NULL},
    {"disable-depth-mask", cfun_DisableDepthMask, NULL},
    {"set-blend-factors", cfun_SetBlendFactors, NULL},
    {"set-blend-factors-separate", cfun_SetBlendFactorsSeparate, NULL},
    {"set-reverse-winding", cfun_SetReverseWinding, NULL},
    {NULL, NULL, NULL}
};
