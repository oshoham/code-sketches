#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

vec3 circle(in vec2 st, in vec2 centerPos, in float radius, in vec3 color) {
  vec2 stOffset = st - centerPos;
  float pct = step(radius, 1.0 - distance(st, centerPos));
  return mix(vec3(0.0), color, pct);
}

void main() {
  vec2 st = gl_FragCoord.xy/u_resolution.xy;
  st.y = 1.0 - st.y;

  float pct = 0.0;

  // a. The DISTANCE from the pixel to the center
  pct = smoothstep(0.9, 0.9, 1.0 - distance(st, vec2(0.5, 0.5)));

  // vec3 circle1 = circle(
  //   st,
  //   vec2(0.5, 0.5),
  //   sin(u_time * 2.0),
  //   vec3(0.23, 0.6665, 1.0)
  // );

  // vec3 circle2 = circle(
  //   st,
  //   vec2(0.1, 0.1),
  //   cos(u_time * 0.667),
  //   vec3(0.5, 0.5, 0.5)
  // );

  // vec3 color = circle1 + circle2;

  // pct = max(distance(st,vec2(0.4)),distance(st,vec2(0.6)));
  pct = pow(distance(st,vec2(0.4)),distance(st,vec2(0.6)));
  vec3 color = mix(vec3(0.0), vec3(1.0), pct);

  gl_FragColor = vec4(color, 1.0);
}
