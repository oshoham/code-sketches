const path = require('path')
const webpack = require('webpack')

module.exports = {
  context: path.resolve(__dirname, './src'),
  entry: {
    app: ['./index.js'],
  },
  output: {
    path: path.resolve(__dirname, './dist'),
    publicPath: '/dist/',
    filename: '[name].bundle.js',
  },
  devServer: {
    contentBase: path.resolve(__dirname),
  },
  module: {
    loaders: [
      { test: /\.js?$/, loaders: ['babel-loader'], exclude: /node_modules/ },
      { test: /\.(glsl|frag|vert)$/, loaders: ['raw-loader'], exclude: /node_modules/ },
      { test: /\.(glsl|frag|vert)$/, loaders: ['glslify-loader'], exclude: /node_modules/ }
    ]
  }
}
