// port of http://nullprogram.com/blog/2014/06/10/ to regl

const regl = require('regl')()
const mouse = require('mouse-change')()

const golShader = require('./gol.frag')
const copyShader = require('./copy.frag')
const vertexShader = require('./shader.vert')

const WIDTH = window.innerWidth * 2
const HEIGHT = window.innerHeight * 2
const INITIAL_CONDITIONS = (Array(WIDTH * HEIGHT * 4)).fill(0).map(
  () => Math.random() > 0.5 ? 255 : 0)
// const INITIAL_CONDITIONS = new Array(WIDTH * HEIGHT)
//   .fill(0)
//   .map(x => Math.random() > 0.5 ? [255, 255, 255, 255] : [0, 0, 0, 255])
//   .reduce((a, b) => a.concat(b), [])

const state = (Array(2)).fill().map(() =>
  regl.framebuffer({
    color: regl.texture({
      width: WIDTH,
      height: HEIGHT,
      data: INITIAL_CONDITIONS,
      min: 'nearest',
      mag: 'nearest',
      format: 'rgba',
      type: 'uint8'
    }),
    depthStencil: false
  }))

const updateLife = regl({
  frag: golShader,
  framebuffer: ({ tick }) => state[(tick + 1) % 2],
})

const setupQuad = regl({
  frag: copyShader,
  vert: vertexShader,
  attributes: {
    position: [-1, -1, 1, -1, -1, 1, 1, 1]
    // position: [-4, -4, 4, -4, 0, 4]
  },
  uniforms: {
    u_resolution: [WIDTH, HEIGHT],
    u_prevState: ({ tick }) => state[tick % 2],
    u_mouse: ({ pixelRatio, viewportHeight }) => [
      mouse.x * pixelRatio,
      viewportHeight - mouse.y * pixelRatio
    ],
  },
  depth: { enable: false },
  count: 4,
  primitive: 'triangle strip'
})


regl.frame(() => {
  setupQuad(() => {
    regl.draw()
    updateLife()
  })
})
