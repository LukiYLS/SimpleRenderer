
#version 330 core

layout(location = 0) in vec3 position;
uniform vec3 cameraPosition;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 v3LightPosition;
uniform vec3 v3InvWavelength;
uniform float fCameraHeight;
uniform float fCameraHeight2;
uniform float fCameraHeightGround;
uniform float fCameraHeight2Ground;
uniform float fOuterRadius;
uniform float fOuterRadius2;
uniform float fInnerRadius;
uniform float fInnerRadius2;
uniform float fKrESun;
uniform float fKmESun;
uniform float fKr4PI;
uniform float fKm4PI;
uniform float fScale;
uniform float fScaleDepth;
uniform float fScaleOverScaleDepth;
const int nSamples = 3;
const float fSamples = 3.0;
varying vec3 v3Direction;
varying vec3 rayleiColor;
varying vec3 mieColor;
float scale(float fCos) {
    float x = 1.0 - fCos;
    return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}
void main(void) {
    vec3 v3Ray = position - cameraPosition;
    float fFar = length(v3Ray);
    v3Ray /= fFar;
    float B = 2.0 * dot(cameraPosition, v3Ray);
    float C = fCameraHeight2 - fOuterRadius2;
    float fDet = max(0.0, B * B - 4.0 * C);
    float fNear = 0.5 * (-B - sqrt(fDet));
    vec3 v3Start = cameraPosition + v3Ray * fNear;
    fFar -= fNear;
    float fStartAngle = dot(v3Ray, v3Start) / fOuterRadius;
    float fStartDepth = exp(-1.0 / fScaleDepth);
    float fStartOffset = fStartDepth * scale(fStartAngle);
    float fSampleLength = fFar / fSamples;
    float fScaledLength = fSampleLength * fScale;
    vec3 v3SampleRay = v3Ray * fSampleLength;
    vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;
    vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);
    for(int i = 0; i < nSamples; i++) {
        float fHeight = length(v3SamplePoint);
        float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
        float fLightAngle = dot(v3LightPosition, v3SamplePoint) / fHeight;
        float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight;
        float fScatter = (fStartOffset + fDepth * (scale(fLightAngle) - scale(fCameraAngle)));
        vec3 v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + fKm4PI));
        v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
        v3SamplePoint += v3SampleRay;
    }
    gl_Position = projection * view * model * vec4(position, 1.0);
    rayleiColor = v3FrontColor * (v3InvWavelength * fKrESun);
    mieColor = v3FrontColor * fKmESun;
    v3Direction = cameraPosition - position;
}