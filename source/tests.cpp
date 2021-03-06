#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "box.hpp"
#include "sphere.hpp"
#include "color.hpp"
#include "shape.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "ray.hpp"
#include "material.hpp"
#include "scene.hpp"


/*TEST_CASE("get-Methode for Box", "[get]"){
  glm::vec3 min{20.5f, 15.5f, -10.0f};
  glm::vec3 max{30.0f, 20.0f, 5.0f};
  Color c{0.0f, 0.0f, 0.5f};
  Box b(min, max, "Box-1", c);
  REQUIRE(b.getMax().x == 30.0f);
  REQUIRE(b.getName() == "Box-1");
  REQUIRE(b.getColor().r == 0.0f);
}

TEST_CASE("get-Methode for Sphere", "[get]"){
  glm::vec3 mittel{32.0f, 15.5f, -25.0f};
  float radius = 23.0f;
  Color c{0.0f, 0.7f, 0.0f};
  Sphere s(mittel, radius, c);
  REQUIRE(s.getMittel().y == 15.5f);
  REQUIRE(s.getName() == "unknown");
}

TEST_CASE("calculate area of the Box", "[calculate]"){
  glm::vec3 min{20.5f, 15.5f, -10.0f};
  glm::vec3 max{30.0f, 20.0f, 5.0f};
  Color c{0.0f, 0.0f, 0.5f};
  Box b(min, max, "Box-1", c);
  REQUIRE(b.area() == 505.5f);
}
TEST_CASE("calculate volume of the Box", "[calculate]"){
  glm::vec3 min{20.5f, 15.5f, -10.0f};
  glm::vec3 max{30.0f, 20.0f, 5.0f};
  Color c{0.0f, 0.0f, 0.5f};
  Box b(min, max, "Box-1", c);
  REQUIRE(b.volumen() == 641.25f);
  std::cout<< b;
}

TEST_CASE("calculate area of the Sphere", "[calculate]"){
  glm::vec3 mittel{32.0f, 15.5f, -25.0f};
  float radius = 23.0f;
  Color c{0.0f, 0.7f, 0.0f};
  Sphere s(mittel, radius, c);
  REQUIRE(s.area() == Approx(6647.61f).epsilon(0.01));
}
TEST_CASE("calculate volume of the Sphere", "[calculate]"){
  glm::vec3 mittel{32.0f, 15.5f, -25.0f};
  float radius = 23.0f;
  Color c{0.0f, 0.7f, 0.0f};
  Sphere s(mittel, radius, c);
  REQUIRE(s.volumen() == Approx(50965.01).epsilon(0.01));
  std::cout<< s;
}

TEST_CASE("intersect_ray_sphere", "[intersect]"){
  // Ray
  glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
  // ray direction has to be normalized!
  // you can use:
  // v = glm::normalize(some_vector)
  glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};

  // Sphere
  glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
  float sphere_radius{1.0f};

  float distance; // from the ray_origin to the intersectPosition
  auto result = glm::intersectRaySphere(
    ray_origin, ray_direction,
    sphere_center, sphere_radius*sphere_radius, // squared radius
    distance);
  REQUIRE(distance == Approx(4.0f));
  REQUIRE(result == true);
}
TEST_CASE("intersect_ray_sphere 1.01", "[intersect]"){
  // Ray
  glm::vec3 ray_origin{2.0f, 3.0f, 0.0f};
  // ray direction has to be normalized!
  // you can use:
  // v = glm::normalize(some_vector)
  glm::vec3 ray_direction{-2.0f, 0.0f, 1.0f};
  glm::vec3 v = glm::normalize(ray_direction);

  // Sphere
  glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
  float sphere_radius{1.0f};

  float distance = 0.0f;
  auto result = glm::intersectRaySphere(
    ray_origin, v,
    sphere_center, sphere_radius*sphere_radius, // squared radius
    distance);
  REQUIRE(distance == Approx(0.0f));  // no intersection, so distance is 0
  REQUIRE(result == false);
  REQUIRE(v.x == Approx(-0.89f).epsilon(0.01));
  REQUIRE(v.y == 0.0f);
  REQUIRE(v.z == Approx(0.44f).epsilon(0.01));
}

// Aufgabe8:
TEST_CASE("test for destruction and konstruction"){
  std::cout<< "========================="<< std::endl;
  Color red{255, 0, 0};
  glm::vec3 position{0.0f, 0.0f, 0.0f};
  Sphere* s1 = new Sphere{position, 1.2f, "sphere0", red};
  Shape* s2 = new Sphere{position, 1.2f, "sphere1", red};

  s1->print(std::cout);
  s2->print(std::cout);

  delete s1;
  delete s2;
}*/

// Aufgabe6.3::
TEST_CASE("test ray_tracer mit Box 1.0", "[intersect]"){
  glm::vec3 origin{0, 0, 0};
  glm::vec3 direction{0, 0, 1};
  Ray r{origin, direction};
  glm::vec3 min{2.0f, 3.5f, 4.0f};
  glm::vec3 max{3.0f, 5.0f, 6.5f};
  Box b(min, max);
  float t;
  REQUIRE(b.intersect(r, t) == false);
  std::cout<< "End!";
}

TEST_CASE("test ray_tracer mit Box 2.0", "[intersect]"){
  glm::vec3 origin{0, 0, 0};
  glm::vec3 direction{1, 0, 0};
  Ray r{origin, direction};
  glm::vec3 min{2.0f, -3.5f, -4.0f};
  glm::vec3 max{3.0f, 5.0f, 6.5f};
  Box b(min, max);
  float t;
  REQUIRE(b.intersect(r, t) == true);
  std::cout<< "End!";
}

TEST_CASE("test ray_tracer mit Box 3.0", "[intersect]"){
  glm::vec3 origin{0, 0, 8.0};
  glm::vec3 direction{0, 0, -1};
  Ray r{origin, direction};
  glm::vec3 min{-1.5f, -7.6f, -7.0f};
  glm::vec3 max{4.5f, 6.7f, -1.5f};
  Box b(min, max);
  float t;
  REQUIRE(b.intersect(r, t) == true);
  std::cout<< "End!";
}

TEST_CASE("test ray_tracer mit Box 4.0", "[intersect]"){
  glm::vec3 origin{0, 0, 0};
  glm::vec3 direction{3, 0, -1};
  Ray r{origin, direction};
  glm::vec3 min{11.0f, -9.0f, -9.0f};
  glm::vec3 max{18.0f, 8.0f, -2.0f};
  Box b(min, max);
  float t;
  REQUIRE(b.intersect(r, t) == true);
  std::cout<< "End!";
}

// TEST_CASE("aufgabe5", "[scene]")
// {
//     Scene scene1;
//     load_sdf("scene.sdf");
//     findMaterialVector("green", scene1.material_vector);
//     // findMaterialMap("red", scene1.material_map);
//     // findMaterialSet("blue", scene1.material_set);
// }


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
