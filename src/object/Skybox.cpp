#include "Skybox.h"
#include "tools/GeometryFactory.h"

namespace SRE {
	Skybox::Skybox()
	{
		_skyboxShader = std::make_shared<Shader>("../../../src/Data/shader/skybox.vs", "../../../src/Data/shader/skybox.fs");
		_skybox = RenderObject::ptr(GeometryFactory::MakeBox(1.0, 1.0, 1.0));
	}
	Skybox::Skybox(std::vector<std::string> fileNames)
	{		
		/*glGenTextures(1, &_textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib(0);
		unsigned int width(0), height(0);
		for (int i = 0; i < fileNames.size(); i++)
		{
			std::string filename = fileNames[i];
			fif = FreeImage_GetFileType(filename.c_str(), 0);
			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(filename.c_str());
			if (fif == FIF_UNKNOWN)
				return;

			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, filename.c_str());
			if (!dib)
				return;
			dib = FreeImage_ConvertTo24Bits(dib);
			BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);
			width = FreeImage_GetWidth(dib);
			height = FreeImage_GetHeight(dib);
			if ((pixels == 0) || (width == 0) || (height == 0))
				return;
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels
			);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);		*/
	}

	Skybox::~Skybox()
	{

	}

	void Skybox::render(Camera* camera)
	{
		_skyboxShader->use();
		_skyboxShader->setMat3("viewRotation", camera->getViewMatrix().getMatrix3x3());
		_skyboxShader->setMat4("projection", camera->getProjectionMatrix());
		_cubeMap->bindTextureUnit(0);
		_skyboxShader->setInt("skybox", 0);
		glDisable(GL_CULL_FACE);
		_skybox->drawPrimitive();
		//glEnable(GL_CULL_FACE);
		_skyboxShader->unUse();
//		Shader::ptr skybox = std::make_shared<Shader>("../../../src/Data/shader/skybox.vs", "../../../src/Data/shader/skybox.fs");
//		Mesh::ptr mesh = (Mesh::ptr)GeometryFactory::MakeBox(1.0, 1.0, 1.0);

//		skybox->setMat4("veiw", camera->getViewMatrix().getMatrix3x3());
//		skybox->setMat4("projection", camera->getProjectionMatrix());

	/*	glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
		glDepthFunc(GL_LEQUAL);*/
//		mesh->draw(skybox.get());
	}
}