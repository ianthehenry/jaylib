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

static Janet cfun_LoadShaderFromMemory(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    const char *vertexShader;
    if (janet_checktype(argv[0], JANET_NIL)) {
        vertexShader = NULL;
    } else {
        vertexShader = janet_getcstring(argv, 0);
    }
    const char *fragmentShader;
    if (janet_checktype(argv[1], JANET_NIL)) {
        fragmentShader = NULL;
    } else {
        fragmentShader = janet_getcstring(argv, 1);
    }
    Shader *shader = janet_abstract(&AT_Shader, sizeof(Shader));
    *shader = LoadShaderFromMemory(vertexShader, fragmentShader);
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

static Janet cfun_SetShaderValueTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Shader shader = *jaylib_getshader(argv, 0);
    const char *uniform = janet_getcstring(argv, 1);
    int location = GetShaderLocation(shader, uniform);
    Texture2D *texture = jaylib_gettexture2d(argv, 2);
    SetShaderValueTexture(shader, location, *texture);
    return janet_wrap_nil();
}

static Janet cfun_SetShaderValueVec2(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Shader shader = *jaylib_getshader(argv, 0);
    const char *uniform = janet_getcstring(argv, 1);
    int location = GetShaderLocation(shader, uniform);
    Vector2 vec = jaylib_getvec2(argv, 2);
    SetShaderValue(shader, location, &vec, SHADER_UNIFORM_VEC2);
    return janet_wrap_nil();
}

static Janet cfun_SetShaderValueInt(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Shader shader = *jaylib_getshader(argv, 0);
    const char *uniform = janet_getcstring(argv, 1);
    int location = GetShaderLocation(shader, uniform);
    int value = janet_getinteger(argv, 2);
    SetShaderValue(shader, location, &value, SHADER_UNIFORM_INT);
    return janet_wrap_nil();
}

static Janet cfun_SetShaderValueFloat(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Shader shader = *jaylib_getshader(argv, 0);
    const char *uniform = janet_getcstring(argv, 1);
    int location = GetShaderLocation(shader, uniform);
    float value = janet_getnumber(argv, 2);
    SetShaderValue(shader, location, &value, SHADER_UNIFORM_FLOAT);
    return janet_wrap_nil();
}

static Janet cfun_SetShaderValueVVec2(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Shader shader = *jaylib_getshader(argv, 0);
    const char *uniform = janet_getcstring(argv, 1);
    int location = GetShaderLocation(shader, uniform);
    int length = 0;
    Vector2 *vecs = jaylib_getvec2s(argv, 2, &length);
    SetShaderValueV(shader, location, vecs, SHADER_UNIFORM_VEC2, length);
    return janet_wrap_nil();
}

static Janet cfun_SetShaderValueVVec3(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Shader shader = *jaylib_getshader(argv, 0);
    const char *uniform = janet_getcstring(argv, 1);
    int location = GetShaderLocation(shader, uniform);
    int length = 0;
    Vector3 *vecs = jaylib_getvec3s(argv, 2, &length);
    SetShaderValueV(shader, location, vecs, SHADER_UNIFORM_VEC3, length);
    return janet_wrap_nil();
}

static Janet cfun_SetShaderValueVVec4(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Shader shader = *jaylib_getshader(argv, 0);
    const char *uniform = janet_getcstring(argv, 1);
    int location = GetShaderLocation(shader, uniform);
    int length = 0;
    Vector4 *vecs = jaylib_getvec4s(argv, 2, &length);
    SetShaderValueV(shader, location, vecs, SHADER_UNIFORM_VEC4, length);
    return janet_wrap_nil();
}

static Janet cfun_SetShaderValueVFloat(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Shader shader = *jaylib_getshader(argv, 0);
    const char *uniform = janet_getcstring(argv, 1);
    int location = GetShaderLocation(shader, uniform);
    int length = 0;
    float *floats = jaylib_getfloats(argv, 2, &length);
    SetShaderValueV(shader, location, floats, SHADER_UNIFORM_FLOAT, length);
    return janet_wrap_nil();
}

static const JanetReg shader_cfuns[] = {
    {"load-shader", cfun_LoadShader, NULL},
    {"load-shader-from-memory", cfun_LoadShaderFromMemory, NULL},
    {"unload-shader", cfun_UnloadShader, NULL},
    {"begin-shader-mode", cfun_BeginShaderMode, NULL},
    {"end-shader-mode", cfun_EndShaderMode, NULL},
    {"set-shader-value-texture", cfun_SetShaderValueTexture, NULL},
    {"set-shader-value-vec2", cfun_SetShaderValueVec2, NULL},
    {"set-shader-value-v-vec2", cfun_SetShaderValueVVec2, NULL},
    {"set-shader-value-v-vec3", cfun_SetShaderValueVVec3, NULL},
    {"set-shader-value-v-vec4", cfun_SetShaderValueVVec4, NULL},
    {"set-shader-value-int", cfun_SetShaderValueInt, NULL},
    {"set-shader-value-float", cfun_SetShaderValueFloat, NULL},
    {"set-shader-value-v-float", cfun_SetShaderValueVFloat, NULL},
    {NULL, NULL, NULL}
};
