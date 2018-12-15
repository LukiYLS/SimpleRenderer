#include <iostream>
#include "texture/Texture.h"
#include "texture/TextureManager.h"
using namespace SRE;

int main() {

    Texture::ptr earthTex = TextureManager::Inst()->loadTexture("earth", "/media/hdd1/myproject/SimpleRenderEngine/src/Data/texture/grass.jpg");
}