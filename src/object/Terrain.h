#pragma once

namespace SRE {

	class Terrain {

	public:
		friend class TerrainTile;
		unsigned int getMaxLevel()const { return _maxLevel; }

	protected:

		unsigned int _maxLevel;

		size_t _size;

		TerrainTile* _root;

	};
}