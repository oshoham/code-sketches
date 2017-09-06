#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359
#define NUM_COLORS 9

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

vec3 colorA = vec3(0.149,0.141,0.912);
vec3 colorB = vec3(1.000,0.833,0.224);
vec3 peach = vec3(252.0, 243.0, 185.0) / 255.0;
vec3 gold = vec3(251.0, 221.0, 91.0) / 255.0;
vec3 yellowOrange = vec3(229.0, 145.0, 61.0) / 255.0;
vec3 burntOrange = vec3(211.0,83.0,11.0) / 255.0;
vec3 brickRed = vec3(198.0, 52.0, 9.0) / 255.0;
vec3 paleRed = vec3(184.0, 92.0, 92.0) / 255.0;
vec3 lavender = vec3(164.0, 127.0, 142.0) / 255.0;
vec3 purple = vec3(85.0, 85.0, 135.0) / 255.0;
vec3 black = vec3(0.0);
vec3 colors[NUM_COLORS];

float map(float value, float inMin, float inMax, float outMin, float outMax) {
  return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

vec2 map(vec2 value, vec2 inMin, vec2 inMax, vec2 outMin, vec2 outMax) {
  return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

vec3 map(vec3 value, vec3 inMin, vec3 inMax, vec3 outMin, vec3 outMax) {
  return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

vec4 map(vec4 value, vec4 inMin, vec4 inMax, vec4 outMin, vec4 outMax) {
  return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

void main() {
  colors[0] = peach;
  colors[1] = gold;
  colors[2] = yellowOrange;
  colors[3] = burntOrange;
  colors[4] = brickRed;
  colors[5] = paleRed;
  colors[6] = lavender;
  colors[7] = purple;
  colors[8] = black;

  float totalAnimationTime = 20.0;
  float totalTransitionTime = 2.5;
  float animationTime = mod(u_time, totalAnimationTime);
  float transitionTime = mod(u_time, totalTransitionTime);
  int colorIndex = int(floor(map(animationTime, 0.0, totalAnimationTime, 0.0, 8.0)));
  int nextColorIndex = int(mod(float(colorIndex + 1), float(NUM_COLORS - 1)));
  vec3 currentColor = colors[colorIndex];
  vec3 nextColor = colors[nextColorIndex];

  vec3 pct = vec3(transitionTime / totalTransitionTime);
  vec3 color = mix(currentColor, nextColor, pct);
  gl_FragColor = vec4(color, 1.0);
}
