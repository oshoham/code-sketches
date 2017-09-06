precision mediump float;

uniform sampler2D u_prevState;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

int get(int x, int y) {
  // use fract() to loop coordinates in the range 0.0 - 1.0
  vec2 texCoord = fract((gl_FragCoord.xy + vec2(x, y)) / u_resolution);
  return int(texture2D(u_prevState, texCoord).r);
}

void main() {
  int sum = get(-1, -1) +
            get(-1,  0) +
            get(-1,  1) +
            get( 0, -1) +
            get( 0,  1) +
            get( 1, -1) +
            get( 1,  0) +
            get( 1,  1);

  if (sum == 3) {
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
  } else if (sum == 2) {
    float current = float(get(0, 0));
    gl_FragColor = vec4(current, current, current, 1.0);
  } else {
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
  }
}
