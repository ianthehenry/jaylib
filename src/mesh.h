#import <raymath.h>

static Janet cfun_UploadMesh(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Mesh *mesh = jaylib_getmesh(argv, 0);
    bool dynamic = janet_getboolean(argv, 1);
    UploadMesh(mesh, dynamic);
    return janet_wrap_nil();
}

static Janet cfun_DrawMesh(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Mesh *mesh = jaylib_getmesh(argv, 0);
    Material *material = jaylib_getmaterial(argv, 1);
    Matrix *transform = jaylib_getmatrix(argv, 2);
    DrawMesh(*mesh, *material, *transform);
    return janet_wrap_nil();
}

static Janet cfun_MeshTangents(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Mesh *mesh = jaylib_getmesh(argv, 0);
    MeshTangents(mesh);
    return janet_wrap_nil();
}

static Janet cfun_LoadMaterialDefault(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    (void) argv;
    Material *material = janet_abstract(&AT_Material, sizeof(Material));
    *material = LoadMaterialDefault();
    return janet_wrap_abstract(material);
}

static Janet cfun_SetMaterialTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Material *material = jaylib_getmaterial(argv, 0);
    // TODO: this should be a keyword
    int mapType = janet_getinteger(argv, 1);
    Texture2D *texture = jaylib_gettexture2d(argv, 2);
    SetMaterialTexture(material, mapType, *texture);
    return janet_wrap_nil();
}

static Janet cfun_GenMeshCube(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    float width = janet_getnumber(argv, 0);
    float height = janet_getnumber(argv, 1);
    float length = janet_getnumber(argv, 2);

    Mesh *mesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *mesh = GenMeshCube(width, height, length);
    return janet_wrap_abstract(mesh);
}

static JanetReg mesh_cfuns[] = {
    {"load-material-default", cfun_LoadMaterialDefault, NULL},
    {"set-material-texture", cfun_SetMaterialTexture, NULL},
    {"upload-mesh", cfun_UploadMesh, NULL},
    {"mesh-tangents", cfun_MeshTangents, NULL},
    {"draw-mesh", cfun_DrawMesh, NULL},
    {"gen-mesh-cube", cfun_GenMeshCube, NULL},
    {"matrix-identity", cfun_MatrixIdentity, NULL},
    {NULL, NULL, NULL}
};
