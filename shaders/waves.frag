#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

void main() {
  vec3 blue = vec3(22.0, 47.0, 127.0) / 255.0;
  vec3 white = vec3(255.0, 255.0, 255.0) / 255.0;
  float pct = mod((sin(gl_FragCoord.x + u_time * 0.01) * gl_FragCoord.y * (u_time * 0.05)), 255.0) / 255.0;
  vec3 color = mix(blue, white, pct);
  gl_FragColor = vec4(color, 1.0);
}
