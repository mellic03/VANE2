#pragma once

namespace vane
{
    class VaneObject;

    class TextureImage;
    class RenderImage;
    class Renderer;
}


class vane::TextureImage
{
private:
    int mW, mH;

public:
    TextureImage() {  }
    int W() { return mW; }
    int H() { return mH; }
};


class vane::Renderer
{
public:
    void renderTexture(vane::TextureImage&);

private:


};

