precision mediump float;

uniform sampler2D u_prevState;
uniform vec2 u_resolution;

void main() {
  gl_FragColor = texture2D(u_prevState, gl_FragCoord.xy / u_resolution);
}
