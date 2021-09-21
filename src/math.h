#import <raymath.h>

static Janet cfun_MatrixIdentity(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    Matrix *matrix = janet_abstract(&AT_Matrix, sizeof(Matrix));
    *matrix = MatrixIdentity();
    return janet_wrap_abstract(matrix);
}

static Janet cfun_MatrixTranslateV(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Vector3 vec = jaylib_getvec3(argv, 0);
    Matrix *matrix = janet_abstract(&AT_Matrix, sizeof(Matrix));
    *matrix = MatrixTranslate(vec.x, vec.y, vec.z);
    return janet_wrap_abstract(matrix);
}

static Janet cfun_MatrixTranslateScale(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Vector3 translate = jaylib_getvec3(argv, 0);
    Vector3 scale = jaylib_getvec3(argv, 1);
    Matrix *matrix = janet_abstract(&AT_Matrix, sizeof(Matrix));
    *matrix = MatrixMultiply(MatrixScale(scale.x, scale.y, scale.z), MatrixTranslate(translate.x, translate.y, translate.z));
    return janet_wrap_abstract(matrix);
}

static Janet cfun_MatrixTranslateScaleRotate(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Vector3 translate = jaylib_getvec3(argv, 0);
    Vector3 scale = jaylib_getvec3(argv, 1);
    Vector3 axis = jaylib_getvec3(argv, 2);
    float rotate = janet_getnumber(argv, 3);

    Matrix m_rotate = rotate == 0 ? MatrixIdentity() : MatrixRotate(axis, rotate);
    Matrix m_scale = MatrixScale(scale.x, scale.y, scale.z);
    Matrix m_translate = MatrixTranslate(translate.x, translate.y, translate.z);

    Matrix *matrix = janet_abstract(&AT_Matrix, sizeof(Matrix));
    *matrix = MatrixMultiply(MatrixMultiply(m_scale, m_rotate), m_translate);
    return janet_wrap_abstract(matrix);
}

static JanetReg math_cfuns[] = {
    {"matrix-identity", cfun_MatrixIdentity, NULL},
    //{"matrix-translate", cfun_MatrixTranslate, NULL},
    {"matrix-translate-v", cfun_MatrixTranslateV, NULL},
    {"matrix-translate-scale", cfun_MatrixTranslateScale, NULL},
    {"matrix-translate-scale-rotate", cfun_MatrixTranslateScaleRotate, NULL},
//    {"matrix-rotate-x", cfun_MatrixRotateX, NULL},
//    {"matrix-rotate-y", cfun_MatrixRotateY, NULL},
//    {"matrix-rotate-z", cfun_MatrixRotateZ, NULL},
    {NULL, NULL, NULL}
};
