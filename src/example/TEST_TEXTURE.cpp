#include <iostream>
#include "texture/Texture.h"
#include "texture/TextureManager.h"
using namespace SRE;

int main() {

    Texture::ptr earthTex = TextureManager::Inst()->loadTexture("earth", "data/texture/grass.jpg");
}