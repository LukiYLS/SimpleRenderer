#pragma once
#include "math/Matrix4D.h"
#include "math/Matrix3D.h"
#include "Texture.h"
#include "hardwarebuffer/ColorValue.h"
namespace SRE {
	//
	enum TextureFilterOptions
	{
		/// Equal to: min=FO_POINT, mag=FO_POINT, mip=FO_NONE
		TFO_NONE,
		/// Equal to: min=FO_LINEAR, mag=FO_LINEAR, mip=FO_POINT
		TFO_BILINEAR,
		/// Equal to: min=FO_LINEAR, mag=FO_LINEAR, mip=FO_LINEAR
		TFO_TRILINEAR,
		/// Equal to: min=FO_ANISOTROPIC, max=FO_ANISOTROPIC, mip=FO_LINEAR
		TFO_ANISOTROPIC
	};
	enum FilterType
	{
		/// The filter used when shrinking a texture
		FT_MIN,
		/// The filter used when magnifying a texture
		FT_MAG,
		/// The filter used when determining the mipmap
		FT_MIP
	};
	enum FilterOptions
	{
		/// No filtering, used for FT_MIP to turn off mipmapping
		FO_NONE,
		/// Use the closest pixel
		FO_POINT,
		/// Average of a 2x2 pixel area, denotes bilinear for MIN and MAG, trilinear for MIP
		FO_LINEAR,
		/// Similar to FO_LINEAR, but compensates for the angle of the texture plane
		FO_ANISOTROPIC
	};
	enum BindingType
	{
		/** Regular fragment processing unit - the default. */
		BT_FRAGMENT = 0,
		/** Vertex processing unit - indicates this unit will be used for
		a vertex texture fetch.
		*/
		BT_VERTEX = 1,
		/// Geometry processing unit        
		BT_GEOMETRY = 2,
		/// Tessellation control processing unit
		BT_TESSELLATION_HULL = 3,
		/// Tessellation evaluation processing unit
		BT_TESSELLATION_DOMAIN = 4,
		/// Compute processing unit
		BT_COMPUTE = 5
	};
	enum ContentType
	{
		/// Normal texture identified by name
		CONTENT_NAMED = 0,
		/// A shadow texture, automatically bound by engine
		CONTENT_SHADOW = 1,
		/// A compositor texture, automatically linked to active viewport's chain
		CONTENT_COMPOSITOR = 2
	};
	enum TextureAddressingMode
	{
		/// Texture wraps at values over 1.0.
		TAM_WRAP = GL_REPEAT,
		/// Texture mirrors (flips) at joins over 1.0.
		TAM_MIRROR = GL_MIRRORED_REPEAT,
		/// Texture clamps at 1.0.
		TAM_CLAMP = GL_CLAMP_TO_EDGE,
		/// Texture coordinates outside the range [0.0, 1.0] are set to the border colour.
		TAM_BORDER = GL_CLAMP_TO_BORDER,
		/// Unknown
		TAM_UNKNOWN = 99
	};
	enum TextureCubeFace
	{
		CUBE_FRONT = 0,
		CUBE_BACK = 1,
		CUBE_LEFT = 2,
		CUBE_RIGHT = 3,
		CUBE_UP = 4,
		CUBE_DOWN = 5
	};

	struct UVWAddressingMode
	{
		TextureAddressingMode u, v, w;
	};
	class TextureUnitState {
	public:
		typedef std::shared_ptr<TextureUnitState> ptr;
		TextureUnitState();
		~TextureUnitState();
		
		

		void setTexture(Texture::ptr texture);
		Texture::ptr getTexture()const;
		void setCubeTexture(Texture::ptr texture);

		
		void setBindingType(BindingType bt);	
		BindingType getBindingType(void) const;
		//
		
		void setContentType(ContentType ct);
		/** Get the type of content this TextureUnitState references. */
		ContentType getContentType(void) const;

		bool isCubic(void) const;
		void setTextureTransform(const Math::Matrix4D& xform);
		const Math::Matrix4D& getTextureTransform(void) const;
		
		void setTextureAddressingMode(TextureAddressingMode tam);
		void setTextureAddressingMode(TextureAddressingMode u, TextureAddressingMode v, TextureAddressingMode w);
		const UVWAddressingMode& getTextureAddressingMode(void) const;
		void setTextureBorderColour(const ColorValue& color);		
		const ColorValue& getTextureBorderColour(void) const;

		void setTextureFiltering(TextureFilterOptions filterType);
		void setTextureFiltering(FilterType ftype, FilterOptions opts);
		FilterOptions getTextureFiltering(FilterType ft) const;
		void setTextureFiltering(FilterOptions minFilter, FilterOptions magFilter, FilterOptions mipFilter);
		void setTextureAnisotropy(unsigned int maxAniso);
		/// Get this layer texture anisotropy level.
		unsigned int getTextureAnisotropy() const;

///		Matrix3D getUvTransfrom()const { return _uvTransform; }

	protected:
		ColorValue _borderColour;
		/// Texture filtering - minification.
		FilterOptions _minFilter;
		/// Texture filtering - magnification.
		FilterOptions _magFilter;
		/// Texture filtering - mipmapping.
		FilterOptions _mipFilter;


		bool _isDefaultFiltering;
		FilterOptions _defaultMinFilter;
		FilterOptions _defaultMagFilter;
		FilterOptions _defaultMipFilter;

		BindingType _bindingType;
		/// Content type of texture (normal loaded texture, auto-texture).
		ContentType _contentType;

		UVWAddressingMode _addressMode;
		Texture::ptr _texture;
		std::vector<Texture::ptr> _frameTextures;

//		Matrix3D _uvTransform;

	};
}