#pragma once
#include "math/Vector2D.h"
#include "math/Vector3D.h"
#include "object/TerrainTile.h"
#define GRIDSIZE 0x100
#define GRIDSIZE_DATA GRIDSIZE*2+2
using Math::Vector2D;
using Math::Vector3D;
namespace SRE {

	class PerlinNoiseTerrainBuilder {

	public:
	
		PerlinNoiseTerrainBuilder(const float& alpha = 3.3, const float& beta = 2.2, int iterationNum = 10, const float& cycle = 128, const float& heightScale = 4);
		void exportToTerrainTile(TerrainTile* terrain);
		float noise2D(const Vector2D& vec);
		float produceHeight(const Vector2D& vec);

	protected:
		void setup(const float &target, int& b0, int& b1, float& r0, float& r1);
		inline float sCurve(const float& t) const { return t * t * (3 - 2 * t); }
		inline float lerp(const float& t, const float& a, const float& b) const { return a + t*(b - a); }
		float _alpha;
		float _beta;
		int _numLayers;
		float _cycle;
		float _heightScale;

		int p[GRIDSIZE_DATA];
		Vector3D greed3[GRIDSIZE_DATA];
		Vector2D greed2[GRIDSIZE_DATA];
		float greed1[GRIDSIZE_DATA];
	};
}