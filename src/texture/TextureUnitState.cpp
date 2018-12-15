#include "TextureUnitState.h"

namespace SRE {

	TextureUnitState::TextureUnitState():
		_defaultMinFilter(FO_NONE),
		_defaultMagFilter(FO_NONE),
		_defaultMipFilter(FO_NONE)
		
	{
			_addressMode.u = _addressMode.v = _addressMode.w = TAM_WRAP;

	}
	TextureUnitState::~TextureUnitState()
	{
		
	}

	void TextureUnitState::setTexture(Texture::ptr texture)
	{
		_texture = texture;
	}
	Texture::ptr TextureUnitState::getTexture()const
	{
		return _texture;
	}
	void TextureUnitState::setCubeTexture(Texture::ptr texuter)
	{

	}
	void TextureUnitState::setBindingType(BindingType bt)
	{
		_bindingType = bt;
	}
	BindingType TextureUnitState::getBindingType(void) const
	{
		return _bindingType;
	}
	void TextureUnitState::setContentType(ContentType ct)
	{
		_contentType = ct;
	}
	
	ContentType TextureUnitState::getContentType(void) const
	{
		return _contentType;
	}

	bool TextureUnitState::isCubic(void) const
	{
		return false;
	}
	void TextureUnitState::setTextureTransform(const Math::Matrix4D& xform)
	{

	}
	const Math::Matrix4D& TextureUnitState::getTextureTransform(void) const
	{
		return Math::Matrix4D::Identity;
	}

	void TextureUnitState::setTextureAddressingMode(TextureAddressingMode tam)
	{
		_addressMode.u = tam;
		_addressMode.v = tam;
		_addressMode.w = tam;
	}
	void TextureUnitState::setTextureAddressingMode(
		TextureAddressingMode u,
		TextureAddressingMode v,
		TextureAddressingMode w)
	{
		_addressMode.u = u;
		_addressMode.v = v;
		_addressMode.w = w;
	}
	const UVWAddressingMode& TextureUnitState::getTextureAddressingMode(void) const
	{
		return _addressMode;
	}
	void TextureUnitState::setTextureBorderColour(const ColorValue& color)
	{
		_borderColour = color;
	}
	const ColorValue& TextureUnitState::getTextureBorderColour(void) const
	{
		return _borderColour;
	}

	void TextureUnitState::setTextureFiltering(TextureFilterOptions filterType)
	{
		switch (filterType)
		{
		case TFO_NONE:
			setTextureFiltering(FO_POINT, FO_POINT, FO_NONE);
			break;
		case TFO_BILINEAR:
			setTextureFiltering(FO_LINEAR, FO_LINEAR, FO_POINT);
			break;
		case TFO_TRILINEAR:
			setTextureFiltering(FO_LINEAR, FO_LINEAR, FO_LINEAR);
			break;
		case TFO_ANISOTROPIC:
			setTextureFiltering(FO_ANISOTROPIC, FO_ANISOTROPIC, FO_ANISOTROPIC);
			break;
		}
		_isDefaultFiltering = false;
	}
	void TextureUnitState::setTextureFiltering(FilterType ft, FilterOptions opts)
	{
		switch (ft)
		{
		case FT_MIN:
			_minFilter = opts;
			break;
		case FT_MAG:
			_magFilter = opts;
			break;
		case FT_MIP:
			_mipFilter = opts;
			break;
		}
		_isDefaultFiltering = false;
	}
	void TextureUnitState::setTextureFiltering(FilterOptions minFilter,
		FilterOptions magFilter, FilterOptions mipFilter)
	{
		_minFilter = minFilter;
		_magFilter = magFilter;
		_mipFilter = mipFilter;
		_isDefaultFiltering = false;
	}
	FilterOptions TextureUnitState::getTextureFiltering(FilterType ft) const
	{

		switch (ft)
		{
		case FT_MIN:
			//return _minFilter;
			return _isDefaultFiltering ?_defaultMinFilter : _minFilter;
		case FT_MAG:
			return _isDefaultFiltering ? _defaultMagFilter : _magFilter;
		case FT_MIP:
			return _isDefaultFiltering ? _defaultMagFilter : _mipFilter;
		}
		
		return _minFilter;
	}
	void TextureUnitState::setTextureAnisotropy(unsigned int maxAniso)
	{

	}
	
	unsigned int TextureUnitState::getTextureAnisotropy() const
	{
		return 0;
	}

	
}