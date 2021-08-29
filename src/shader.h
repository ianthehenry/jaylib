static Janet cfun_LoadShader(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    const char *vertexShaderFileName;
    if (janet_checktype(argv[0], JANET_NIL)) {
        vertexShaderFileName = NULL;
    } else {
        vertexShaderFileName = janet_getcstring(argv, 0);
    }
    const char *fragmentShaderFileName;
    if (janet_checktype(argv[1], JANET_NIL)) {
        fragmentShaderFileName = NULL;
    } else {
        fragmentShaderFileName = janet_getcstring(argv, 1);
    }
    Shader *shader = janet_abstract(&AT_Shader, sizeof(Shader));
    *shader = LoadShader(vertexShaderFileName, fragmentShaderFileName);
    return janet_wrap_abstract(shader);
}

static Janet cfun_UnloadShader(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Shader shader = *jaylib_getshader(argv, 0);
    UnloadShader(shader);
    return janet_wrap_nil();
}

static Janet cfun_BeginShaderMode(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Shader *shader = jaylib_getshader(argv, 0);
    BeginShaderMode(*shader);
    return janet_wrap_nil();
}

static Janet cfun_EndShaderMode(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    EndShaderMode();
    return janet_wrap_nil();
}

static const JanetReg shader_cfuns[] = {
    {"load-shader", cfun_LoadShader, NULL},
    {"unload-shader", cfun_UnloadShader, NULL},
    {"begin-shader-mode", cfun_BeginShaderMode, NULL},
    {"end-shader-mode", cfun_EndShaderMode, NULL},
    {NULL, NULL, NULL}
};
