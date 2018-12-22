#version 400 
const float PackUpscale = 256. / 255.;const float UnpackDownscale = 255. / 256.;
const vec3 PackFactors = vec3( 256. * 256. * 256., 256. * 256.,  256. );
const vec4 UnpackFactors = UnpackDownscale / vec4( PackFactors, 1. );
const float ShiftRight8 = 1. / 256.;
vec4 packDepthToRGBA( const in float v ) {
	vec4 r = vec4( fract( v * PackFactors ), v );
	r.yzw -= r.xyz * ShiftRight8;	return r * PackUpscale;
}



void main() {
		
	gl_FragColor = vec4(gl_FragCoord.z);
	//gl_FragDepth = gl_FragCoord.z;
	///vec4 diffuseColor = vec4( 1.0 );
	//#if DEPTH_PACKING == 3200
	//	diffuseColor.a = opacity;
	//#endif
	//#if DEPTH_PACKING == 3200
	//gl_FragColor = vec4( vec3( gl_FragCoord.z ), opacity );
	//#elif DEPTH_PACKING == 3201
	gl_FragColor = packDepthToRGBA( gl_FragCoord.z );
	//#endif
}
