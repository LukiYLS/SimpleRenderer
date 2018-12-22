uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
uniform vec3 cameraPosition;

layout (location = 0)in vec3 position;
layout (location = 1)in vec3 normal;
layout (location = 2)in vec2 uv;
#ifdef USE_COLOR
layout (location = 3)in vec3 color;
#endif
#if defined( USE_LIGHTMAP ) || defined( USE_AOMAP )	
layout (location = 4)in vec2 uv2;
#endif

#define PHONG
varying vec3 vViewPosition;
varying vec3 vWorldPosition;
#ifndef FLAT_SHADED
	varying vec3 vNormal;
#endif
#define PI 3.14159265359
#define EPSILON 1e-6


vec3 inverseTransformDirection( in vec3 dir, in mat4 matrix ) {
	return normalize( ( vec4( dir, 0.0 ) * matrix ).xyz );
}


#if defined( USE_MAP ) || defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( USE_SPECULARMAP ) || defined( USE_ALPHAMAP )
	varying vec2 vUv;
	uniform mat3 uvTransform;
#endif

#if defined( USE_LIGHTMAP ) || defined( USE_AOMAP )	
	varying vec2 vUv2;
#endif
#ifdef USE_DISPLACEMENTMAP
	uniform sampler2D displacementMap;
	uniform float displacementScale;
	uniform float displacementBias;
#endif

#ifdef USE_ENVMAP
	#if defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( PHONG )
		varying vec3 vWorldPosition;
	#else
		varying vec3 vReflect;
		uniform float refractionRatio;
	#endif
#endif

#ifdef USE_COLOR
	varying vec3 vColor;
#endif
#ifdef USE_FOG
  varying float fogDepth;
#endif

#ifdef USE_SHADOWMAP
	#if NUM_DIR_LIGHTS > 0
		uniform mat4 directionalShadowMatrix[ NUM_DIR_LIGHTS ];
		varying vec4 vDirectionalShadowCoord[ NUM_DIR_LIGHTS ];
	#endif
	#if NUM_SPOT_LIGHTS > 0
		uniform mat4 spotShadowMatrix[ NUM_SPOT_LIGHTS ];
		varying vec4 vSpotShadowCoord[ NUM_SPOT_LIGHTS ];
	#endif
	#if NUM_POINT_LIGHTS > 0
		//uniform mat4 pointShadowMatrix[ NUM_POINT_LIGHTS ];
		//varying vec4 vPointShadowCoord[ NUM_POINT_LIGHTS ];
	#endif
#endif


//#if NUM_CLIPPING_PLANES > 0 && ! defined( PHYSICAL ) && ! defined( PHONG )
//	varying vec3 vViewPosition;
//#endif

void main() {
#if defined( USE_MAP ) || defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( USE_SPECULARMAP ) || defined( USE_ALPHAMAP ) 
	vUv = ( uvTransform * vec3( uv, 1 ) ).xy;
#endif
#if defined( USE_LIGHTMAP ) || defined( USE_AOMAP )
	vUv2 = uv2;
#endif
#ifdef USE_COLOR
	vColor.xyz = color.xyz;
#endif

vec3 objectNormal = vec3( normal );
vec3 transformedNormal = normalMatrix * objectNormal;
#ifdef FLIP_SIDED
	transformedNormal = - transformedNormal;
#endif

#ifndef FLAT_SHADED
	vNormal = normalize( transformedNormal );
#endif

vec3 transformed = vec3( position );

#ifdef USE_DISPLACEMENTMAP
	transformed += normalize( objectNormal ) * ( texture2D( displacementMap, uv ).x * displacementScale + displacementBias );
#endif

vec4 mvPosition = modelMatrix * vec4( transformed, 1.0 );
vWorldPosition = mvPosition.xyz;
vec4 viewPosition = modelMatrix * viewMatrix * vec4( transformed, 1.0 );
vViewPosition = -viewPosition.xyz;
gl_Position = projectionMatrix * viewMatrix * mvPosition;

//#if NUM_CLIPPING_PLANES > 0 && ! defined( PHYSICAL ) && ! defined( PHONG )
//	vViewPosition =  mvPosition.xyz;
//#endif

//vViewPosition =  mvPosition.xyz;
#if defined( USE_ENVMAP ) || defined( DISTANCE ) || defined ( USE_SHADOWMAP )
	vec4 worldPosition = modelMatrix * vec4( transformed, 1.0 );
#endif

#ifdef USE_ENVMAP
	#if defined( USE_BUMPMAP ) || defined( USE_NORMALMAP ) || defined( PHONG )
		vWorldPosition = worldPosition.xyz;
	#else
		vec3 cameraToVertex = normalize( worldPosition.xyz - cameraPosition );
		vec3 worldNormal = inverseTransformDirection( transformedNormal, viewMatrix );
		#ifdef ENVMAP_MODE_REFLECTION
			vReflect = reflect( cameraToVertex, worldNormal );
		#else
			vReflect = refract( cameraToVertex, worldNormal, refractionRatio );
		#endif
	#endif
#endif

#ifdef USE_SHADOWMAP

	#if NUM_DIR_LIGHTS > 0

	for ( int i = 0; i < NUM_DIR_LIGHTS; i ++ ) {

		vDirectionalShadowCoord[ i ] = directionalShadowMatrix[ i ] * worldPosition;
		//vDirectionalShadowCoord[ i ] = vDirectionalShadowCoord[ i ] * 0.5 + 0.5;
	}

	#endif

	#if NUM_SPOT_LIGHTS > 0

	for ( int i = 0; i < NUM_SPOT_LIGHTS; i ++ ) {

		vSpotShadowCoord[ i ] = spotShadowMatrix[ i ] * worldPosition;

	}

	#endif

	#if NUM_POINT_LIGHTS > 0

	for ( int i = 0; i < NUM_POINT_LIGHTS; i ++ ) {

		//vPointShadowCoord[ i ] = pointShadowMatrix[ i ] * worldPosition;

	}

	#endif
	

#endif

#ifdef USE_FOG
fogDepth = -mvPosition.z;
#endif
}
