// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "hit.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "light.hpp"
// #include "sphere.hpp"
#include "scene.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <cmath>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);

  // void render();
  void render(Scene const& scene);
  Color trace(Scene const& scene, Ray const& ray, int depth);
  Color shade(Scene const& scene, Ray const& ray, int closest, int depth);
  Color toneMapping(Color const& color);
  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
