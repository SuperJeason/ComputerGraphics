#pragma once
#include "CGObject.h"
#include <vector>
#include <map>

class CGCamera;
class CGRenderContext;

//OpenGL视为状态机，有一系列开关量（渲染模式）、属性（渲染属性）。如当前深度测试、颜色等。用于Node，包括实例节点与模型

typedef enum
{
    RS_VertexAttrib,
    RS_VertexAttrib0 = RS_VertexAttrib,
    RS_VertexAttrib1,
    RS_VertexAttrib2,
    RS_VertexAttrib3,
    RS_VertexAttrib4,
    RS_VertexAttrib5,
    RS_VertexAttrib6,
    RS_VertexAttrib7,

    RS_AlphaFunc,
    RS_BlendColor,
    RS_BlendEquation,
    RS_BlendFunc,
    RS_Color,
    RS_ColorMask,
    RS_CullFace,
    RS_DepthFunc,
    RS_DepthMask,
    RS_DepthRange,
    RS_Fog,
    RS_FrontFace,
    RS_PolygonMode,
    RS_Hint,
    RS_LightModel,
    RS_LineStipple,
    RS_LineWidth,
    RS_LogicOp,
    RS_Material,
    RS_Normal,
    RS_PixelTransfer,
    RS_PointParameter,
    RS_PointSize,
    RS_PolygonOffset,
    RS_PolygonStipple,
    RS_SampleCoverage,
    RS_SecondaryColor,
    RS_ShadeModel,
    RS_StencilFunc,
    RS_StencilMask,
    RS_StencilOp,
    RS_GLSLProgram,

    RS_Light,
    RS_Light0 = RS_Light,
    RS_Light1,
    RS_Light2,
    RS_Light3,
    RS_Light4,
    RS_Light5,
    RS_Light6,
    RS_Light7,

    RS_ClipPlane,
    RS_ClipPlane0 = RS_ClipPlane,
    RS_ClipPlane1,
    RS_ClipPlane2,
    RS_ClipPlane3,
    RS_ClipPlane4,
    RS_ClipPlane5,

    RS_TextureImageUnit,
    RS_TextureImageUnit0 = RS_TextureImageUnit + 0,
    RS_TextureImageUnit1 = RS_TextureImageUnit + 1,
    RS_TextureImageUnit2 = RS_TextureImageUnit + 2,
    RS_TextureImageUnit3 = RS_TextureImageUnit + 3,
    RS_TextureImageUnit4 = RS_TextureImageUnit + 4,
    RS_TextureImageUnit5 = RS_TextureImageUnit + 5,
    RS_TextureImageUnit6 = RS_TextureImageUnit + 6,
    RS_TextureImageUnit7 = RS_TextureImageUnit + 7,
    RS_TextureImageUnit8 = RS_TextureImageUnit + 8,
    RS_TextureImageUnit9 = RS_TextureImageUnit + 9,
    RS_TextureImageUnit10 = RS_TextureImageUnit + 10,
    RS_TextureImageUnit11 = RS_TextureImageUnit + 11,
    RS_TextureImageUnit12 = RS_TextureImageUnit + 12,
    RS_TextureImageUnit13 = RS_TextureImageUnit + 13,
    RS_TextureImageUnit14 = RS_TextureImageUnit + 14,
    RS_TextureImageUnit15 = RS_TextureImageUnit + 15,
    /* ... */

    RS_TexGen = RS_TextureImageUnit + 32,
    RS_TexGen0 = RS_TexGen + 0,
    RS_TexGen1 = RS_TexGen + 1,
    RS_TexGen2 = RS_TexGen + 2,
    RS_TexGen3 = RS_TexGen + 3,
    RS_TexGen4 = RS_TexGen + 4,
    RS_TexGen5 = RS_TexGen + 5,
    RS_TexGen6 = RS_TexGen + 6,
    RS_TexGen7 = RS_TexGen + 7,
    RS_TexGen8 = RS_TexGen + 8,
    RS_TexGen9 = RS_TexGen + 9,
    RS_TexGen10 = RS_TexGen + 10,
    RS_TexGen11 = RS_TexGen + 11,
    RS_TexGen12 = RS_TexGen + 12,
    RS_TexGen13 = RS_TexGen + 13,
    RS_TexGen14 = RS_TexGen + 14,
    RS_TexGen15 = RS_TexGen + 15,
    /* ... */

    RS_TexEnv = RS_TexGen + 8,
    RS_TexEnv0 = RS_TexEnv + 0,
    RS_TexEnv1 = RS_TexEnv + 1,
    RS_TexEnv2 = RS_TexEnv + 2,
    RS_TexEnv3 = RS_TexEnv + 3,
    RS_TexEnv4 = RS_TexEnv + 4,
    RS_TexEnv5 = RS_TexEnv + 5,
    RS_TexEnv6 = RS_TexEnv + 6,
    RS_TexEnv7 = RS_TexEnv + 7,
    RS_TexEnv8 = RS_TexEnv + 8,
    RS_TexEnv9 = RS_TexEnv + 9,
    RS_TexEnv10 = RS_TexEnv + 10,
    RS_TexEnv11 = RS_TexEnv + 11,
    RS_TexEnv12 = RS_TexEnv + 12,
    RS_TexEnv13 = RS_TexEnv + 13,
    RS_TexEnv14 = RS_TexEnv + 14,
    RS_TexEnv15 = RS_TexEnv + 15,
    /* ... */

    RS_TextureMatrix = RS_TexEnv + 8,
    RS_TextureMatrix0 = RS_TextureMatrix + 0,
    RS_TextureMatrix1 = RS_TextureMatrix + 1,
    RS_TextureMatrix2 = RS_TextureMatrix + 2,
    RS_TextureMatrix3 = RS_TextureMatrix + 3,
    RS_TextureMatrix4 = RS_TextureMatrix + 4,
    RS_TextureMatrix5 = RS_TextureMatrix + 5,
    RS_TextureMatrix6 = RS_TextureMatrix + 6,
    RS_TextureMatrix7 = RS_TextureMatrix + 7,
    RS_TextureMatrix8 = RS_TextureMatrix + 8,
    RS_TextureMatrix9 = RS_TextureMatrix + 9,
    RS_TextureMatrix10 = RS_TextureMatrix + 10,
    RS_TextureMatrix11 = RS_TextureMatrix + 11,
    RS_TextureMatrix12 = RS_TextureMatrix + 12,
    RS_TextureMatrix13 = RS_TextureMatrix + 13,
    RS_TextureMatrix14 = RS_TextureMatrix + 14,
    RS_TextureMatrix15 = RS_TextureMatrix + 15,
    /* ... */

    RS_RenderStateCount = RS_TextureMatrix + 8,

    RS_NONE
} ERenderState;
//开关量
typedef enum
{
    // Common ones
    EN_BLEND = GL_BLEND,
    EN_CULL_FACE = GL_CULL_FACE,
    EN_DEPTH_TEST = GL_DEPTH_TEST,
    EN_STENCIL_TEST = GL_STENCIL_TEST,
    EN_DITHER = GL_DITHER,
    EN_POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL,
    EN_POLYGON_OFFSET_LINE = GL_POLYGON_OFFSET_LINE,
    EN_POLYGON_OFFSET_POINT = GL_POLYGON_OFFSET_POINT,
    EN_COLOR_LOGIC_OP = GL_COLOR_LOGIC_OP,
    EN_MULTISAMPLE = GL_MULTISAMPLE,

    // Smoothing
    EN_POINT_SMOOTH = GL_POINT_SMOOTH,
    EN_LINE_SMOOTH = GL_LINE_SMOOTH,
    EN_POLYGON_SMOOTH = GL_POLYGON_SMOOTH,

    // Stippling
    EN_LINE_STIPPLE = GL_LINE_STIPPLE,
    EN_POLYGON_STIPPLE = GL_POLYGON_STIPPLE,

    // Point sprites
    EN_POINT_SPRITE = GL_POINT_SPRITE,
    EN_PROGRAM_POINT_SIZE = GL_PROGRAM_POINT_SIZE,

    // 管线固定功能
    EN_ALPHA_TEST = GL_ALPHA_TEST,
    EN_LIGHTING = GL_LIGHTING,
    EN_COLOR_SUM = GL_COLOR_SUM,
    EN_FOG = GL_FOG,
    EN_NORMALIZE = GL_NORMALIZE,
    EN_RESCALE_NORMAL = GL_RESCALE_NORMAL,

    // OpenGL 2.x
    EN_VERTEX_PROGRAM_TWO_SIDE = GL_VERTEX_PROGRAM_TWO_SIDE,

    // OpenGL 3.2
    EN_TEXTURE_CUBE_MAP_SEAMLESS = GL_TEXTURE_CUBE_MAP_SEAMLESS,

    // OpenGL 3.0
    EN_CLIP_DISTANCE0 = GL_CLIP_DISTANCE0,
    EN_CLIP_DISTANCE1 = GL_CLIP_DISTANCE1,
    EN_CLIP_DISTANCE2 = GL_CLIP_DISTANCE2,
    EN_CLIP_DISTANCE3 = GL_CLIP_DISTANCE3,
    EN_CLIP_DISTANCE4 = GL_CLIP_DISTANCE4,
    EN_CLIP_DISTANCE5 = GL_CLIP_DISTANCE5,
    EN_CLIP_DISTANCE6 = GL_CLIP_DISTANCE6,
    EN_CLIP_DISTANCE7 = GL_CLIP_DISTANCE7,

    // Multisampling
    EN_SAMPLE_ALPHA_TO_COVERAGE = GL_SAMPLE_ALPHA_TO_COVERAGE,
    EN_SAMPLE_ALPHA_TO_ONE = GL_SAMPLE_ALPHA_TO_ONE,
    EN_SAMPLE_COVERAGE = GL_SAMPLE_COVERAGE,

    EN_EnableCount,

    EN_UnknownEnable
} EEnable;

typedef enum
{
    PF_FRONT = GL_FRONT,
    PF_BACK = GL_BACK,
    PF_FRONT_AND_BACK = GL_FRONT_AND_BACK
} EPolygonFace;

typedef enum
{
    CM_EMISSION = GL_EMISSION,
    CM_AMBIENT = GL_AMBIENT,
    CM_DIFFUSE = GL_DIFFUSE,
    CM_SPECULAR = GL_SPECULAR,
    CM_AMBIENT_AND_DIFFUSE = GL_AMBIENT_AND_DIFFUSE
} EColorMaterial;

typedef enum
{
    PM_FILL = GL_FILL,
    PM_LINE = GL_LINE,
    PM_POINT = GL_POINT
} EPolygonMode;

typedef enum
{
    SM_FLAT = GL_FLAT,
    SM_SMOOTH = GL_SMOOTH
} EShadeModel;

typedef enum
{
    FF_CW = GL_CW,
    FF_CCW = GL_CCW
} EFrontFace;


class CGRenderState : public CGObject
{
public:
    CGRenderState() {}
    virtual ~CGRenderState() = default;
    virtual ERenderState type() const { return RS_NONE; }
    //需重写的虚函数,index用于多属性比如多光源
    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const = 0;
};

//颜色属性
class CGColor : public CGRenderState
{
public:
    CGColor() : mColor(1, 1, 1, 1) {}
    virtual ~CGColor() = default;
    virtual ERenderState type() const { return RS_Color; }
    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const;

    void setValue(const glm::vec4& color) { mColor = color; }
    const glm::vec4& value() const { return mColor; }

protected:
    glm::vec4 mColor;
};

class CGPointSize : public CGRenderState
{
public:
    CGPointSize(float pointsize = 1.0f) : mPointSize(pointsize) {}
    virtual ~CGPointSize() = default;
    virtual ERenderState type() const { return RS_PointSize; }
    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const;

    void set(float pointsize) { mPointSize = pointsize; }
    float pointSize() const { return mPointSize; }

protected:
    float mPointSize;
};

class CGLineWidth : public CGRenderState
{
public:
    CGLineWidth(float linewidth = 1.0f) : mLineWidth(linewidth) {}
    virtual ~CGLineWidth() = default;
    virtual ERenderState type() const { return RS_LineWidth; }
    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const;

    void set(float linewidth) { mLineWidth = linewidth; }
    float lineWidth() const { return mLineWidth; }

protected:
    float mLineWidth;
};

class CGLineStipple : public CGRenderState
{
public:
    CGLineStipple(int factor = 1, GLushort pattern = ~(GLushort)0) : mFactor(factor), mPattern(pattern) {}
    virtual ~CGLineStipple() = default;
    virtual ERenderState type() const { return RS_LineStipple; }
    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const;

    void set(int factor, GLushort pattern) { mFactor = factor; mPattern = pattern; }
    void setFactor(int factor) { mFactor = factor; }
    void setPattern(GLushort pattern) { mPattern = pattern; }
    int factor() const { return mFactor; }
    GLushort pattern() const { return mPattern; }
protected:
    int mFactor;
    GLushort mPattern;
};

class CGPolygonMode : public CGRenderState
{
public:
    CGPolygonMode(EPolygonMode frontface = PM_FILL, EPolygonMode backface = PM_FILL) : mFrontFace(frontface), mBackFace(backface) {}
    virtual ~CGPolygonMode() = default;
    virtual ERenderState type() const { return RS_PolygonMode; }
    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const;

    void set(EPolygonMode frontface, EPolygonMode backface) { mFrontFace = frontface; mBackFace = backface; }
    void setFrontFace(EPolygonMode frontface) { mFrontFace = frontface; }
    void setBackFace(EPolygonMode backface) { mBackFace = backface; }
    EPolygonMode frontFace() const { return mFrontFace; }
    EPolygonMode backFace() const { return mBackFace; }
protected:
    EPolygonMode mFrontFace;
    EPolygonMode mBackFace;
};

class CGEnableSet : public CGObject
{
public:
    CGEnableSet() {
        mEnables.push_back(EN_DITHER);
        mEnables.push_back(EN_MULTISAMPLE);
    }
    void enable(EEnable capability)
    {
        mModes[capability] = true;
        //for (unsigned i = 0; i < mEnables.size(); ++i)
        //    if (mEnables[i] == capability)
        //        return;
        //mEnables.push_back(capability);
    }
    void disable(EEnable capability)
    {
        mModes[capability] = false;

        //for (unsigned i = 0; i < mEnables.size(); ++i) {
        //    if (mEnables[i] == capability) {
        //        mEnables.erase(mEnables.begin() + i);
        //        return;
        //    }
        //}
    }
    const std::vector<EEnable>& enables() const { return mEnables; }
    bool isEnabled(EEnable capability) const
    {
        auto f = mModes.find(capability);
        if (f != mModes.end()) {
            return mModes.at(capability);
        }
        return false;
        //for (unsigned i = 0; i < mEnables.size(); ++i)
        //    if (mEnables[i] == capability)
        //        return true;
        //return false;
    }
    void disableAll() { mModes.clear();  mEnables.clear(); }
protected:
    std::vector<EEnable> mEnables;

    std::map<EEnable, bool> mModes;
};

//多属性比如光源、纹理等
struct CGRenderStateSlot
{
    CGRenderStateSlot() : mRS(NULL), mIndex(-1) {}
    CGRenderStateSlot(std::shared_ptr<CGRenderState> rs, int index) : mRS(rs), mIndex(index) {}
    virtual ~CGRenderStateSlot() {}
    virtual void apply(const CGCamera* camera, CGRenderContext* ctx) const { mRS->apply(camera, ctx, mIndex); }
    ERenderState type() const
    {
        if (mIndex > 0)
            return (ERenderState)(GLenum(mRS->type()) + mIndex);
        else
            return mRS->type();
    }
    std::shared_ptr<CGRenderState> mRS;
    int mIndex;
};

class CGRenderStateSet : public CGObject
{
public:
    CGRenderStateSet() {}
    void apply(const CGCamera* camera, CGRenderContext* ctx);
    void setRenderState(std::shared_ptr<CGRenderState> renderstate, int index);
    CGRenderState* renderState(ERenderState type, int index = -1);
    const CGRenderState* renderState(ERenderState type, int index = -1) const;
    size_t renderStatesCount() const { return mRenderStates.size(); }
    const CGRenderStateSlot* renderStates() const { if (mRenderStates.empty()) return NULL; else return &mRenderStates[0]; }
    CGRenderStateSlot* renderStates() { if (mRenderStates.empty()) return NULL; else return &mRenderStates[0]; }
    void eraseRenderState(ERenderState type, int index);
    void eraseAllRenderStates() { mRenderStates.clear(); mModes.clear(); }
    void enable(EEnable capability) { mModes[capability] = true; }
    void disable(EEnable capability) { mModes[capability] = false; }

protected:
    std::vector<CGRenderStateSlot> mRenderStates;
    std::map<EEnable, bool> mModes; //模式，true=开启，off等于关闭
};
