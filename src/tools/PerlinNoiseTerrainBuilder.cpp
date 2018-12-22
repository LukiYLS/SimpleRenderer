#include "PerlinNoiseTerrainBuilder.h"

#define BM 0xff
#define N 0x1000
#define NP 12   /* 2^N */
#define NM 0xfff
namespace SRE {

	PerlinNoiseTerrainBuilder::PerlinNoiseTerrainBuilder(const float& alpha, const float& beta, int numLayers, const float& cycle, const float& heightScale)
	:_alpha(alpha),
	 _beta(beta),
	 _numLayers(numLayers),
	 _cycle(cycle),
	 _heightScale(heightScale){

		//生成1D,2D,3D随机种子

		for (int i = 0; i < GRIDSIZE; i++)
		{
			p[i] = i;
			greed1[i] = 2.0f * rand() - 1.0f;

			greed2[i] = Vector2D(2.0f * rand() - 1.0f, 2.0f * rand() - 1.0f);
			greed2[i].normalize();

			greed3[i] = Vector3D(2.0f * rand() - 1.0f, 2.0f * rand() - 1.0f, 2.0f * rand() - 1.0f);
			greed3[i].normalize();
		}

		for (int i = 0; i < GRIDSIZE; i++) {
			int j = (int)GRIDSIZE * rand();

			int k = p[i];
			p[i] = p[j];
			p[j] = k;
		}

		for (int i = 0; i < GRIDSIZE + 2; i++) {
			p[GRIDSIZE + i] = p[i];
			greed1[GRIDSIZE + i] = greed1[i];
			greed2[GRIDSIZE + i] = greed2[i];
			greed3[GRIDSIZE + i] = greed3[i];
		}

	}

	void PerlinNoiseTerrainBuilder::exportToTerrainTile(TerrainTile* tile)
	{
	
		unsigned int width = tile->getWidth();
		unsigned int height = tile->getHeight();
		Code code = tile->getCode();
		float* heightMap = new float[width * height];
		
		Vector2D worldOffset(float(code.x*(width - 1)), float(code.y*(height - 1)));
		Vector2D revisedValuePoint;
		for (unsigned int i = 0; i<height; i++)
			for (unsigned int j = 0; j<width; j++)
			{
				revisedValuePoint = (worldOffset + Vector2D(j, i)) / _cycle;
				heightMap[i*width + j] = produceHeight(revisedValuePoint) * _heightScale;
			}
		tile->importHeightMap(heightMap);
	}

	float PerlinNoiseTerrainBuilder::produceHeight(const Vector2D& vec)
	{
		Vector2D tempVec(vec);
		float sum = 0;
		float scale = 1;

		for (int i = 0; i<_numLayers; i++)
		{
			sum += noise2D(tempVec) / scale;
			scale *= _alpha;
			tempVec = tempVec * _beta;
		}
		return sum;
	}

	float PerlinNoiseTerrainBuilder::noise2D(const Vector2D& vec)
	{
		int bx0, bx1, by0, by1, b00, b10, b01, b11;
		float rx0, rx1, ry0, ry1, sx, sy, a, b, u, v;

		setup(vec.x, bx0, bx1, rx0, rx1);
		setup(vec.y, by0, by1, ry0, ry1);

		int i = p[bx0];
		int j = p[bx1];

		b00 = p[i + by0];
		b10 = p[j + by0];
		b01 = p[i + by1];
		b11 = p[j + by1];

		sx = sCurve(rx0);
		sy = sCurve(ry0);

		u = greed2[b00] * (Vector2D(rx0, ry0));
		v = greed2[b10] * (Vector2D(rx1, ry0));
		a = lerp(sx, u, v);

		u = greed2[b01] * (Vector2D(rx0, ry1));
		v = greed2[b11] * (Vector2D(rx1, ry1));
		b = lerp(sx, u, v);

		return lerp(sy, a, b);
	}

	void PerlinNoiseTerrainBuilder::setup(const float &target, int& b0, int& b1, float& r0, float& r1)
	{
		float t = target + N;
		b0 = ((int)t) & BM;
		b1 = (b0 + 1) & BM;
		r0 = t - (int)t;
		r1 = r0 - 1;
	}
}