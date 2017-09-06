#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

vec3 red = vec3(184.0, 35.0, 37.0) / 255.0;
vec3 yellow = vec3(252.0, 203.0, 47.0) / 255.0;
vec3 blue = vec3(0.0, 94.0, 155.5) / 255.0;
vec3 offwhite = vec3(250.0, 243.0, 225.0) / 255.0;

vec3 borders (in vec2 _st, in float _borderSize) {
  vec2 borders = vec2(_borderSize);

  // Each result will return 1.0 (white) or 0.0 (black).
  vec2 bottomLeft = step(borders, _st);
  // The multiplication of left*bottom will be similar to the logical AND.
  float pct = bottomLeft.x * bottomLeft.y;

  vec2 topRight = step(borders, 1.0 - _st);
  pct *= topRight.x * topRight.y;

  return vec3(pct);
}

vec3 rectangle (in vec2 st, in vec2 position, in vec2 dimensions, in vec2 smoothing, in vec3 color) {
  vec2 stepAmount = (vec2(1.0) - dimensions) * 0.5;

  vec2 stOffset = st + stepAmount - position;
  vec2 bottomLeft = smoothstep(stepAmount, stepAmount + smoothing, stOffset);
  vec2 topRight = smoothstep(stepAmount, stepAmount + smoothing, 1.0 - stOffset);
  float pct = bottomLeft.x * bottomLeft.y * topRight.x * topRight.y;

  return mix(vec3(0.0), color, pct);
}

void main() {
  vec2 st = gl_FragCoord.xy/u_resolution.xy;
  st.y = 1.0 - st.y;

  vec3 rectangle1 = rectangle(
    st,
    vec2(0.0, 0.0),
    vec2(0.05, 0.1),
    vec2(0.0, 0.0),
    red
  );

  vec3 rectangle2 = rectangle(
    st,
    vec2(0.075, 0.0),
    vec2(0.075, 0.1),
    vec2(0.0, 0.0),
    red
  );

  vec3 rectangle3 = rectangle(
    st,
    vec2(0.0, 0.12),
    vec2(0.15, 1.0 - 0.12),
    vec2(0.0, 0.0),
    offwhite
  );
  vec3 color = rectangle1 + rectangle2 + rectangle3;

  gl_FragColor = vec4(color, 1.0);
}
