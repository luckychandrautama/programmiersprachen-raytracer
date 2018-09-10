#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "color.hpp"
#include <ostream>
#include "material.hpp"
#include "ray.hpp"
#include "glm/vec3.hpp"
#include "Hit.hpp"
#include <memory>

class Shape{
    public:
        Shape();
        /*Shape(std::string const& name);
        Shape(std::shared_ptr<Material> material);*/
        Shape(std::string const& name, std::shared_ptr<Material> const& material);
        Shape(std::string const& name, std::shared_ptr<Material> const& material, glm::mat4 worldTransform);
        virtual ~Shape();

        std::string getName() const;
        Color getColor() const;
        std::shared_ptr<Material> getMaterial() const;
        virtual glm::mat4 getWorldMat() const;
        virtual glm::mat4 getWorldMatInv() const;

        virtual float area() const = 0;
        virtual float volumen() const = 0;
        
        virtual bool intersect(Ray const& r, float& t) = 0;
        virtual Hit intersectHit(Ray const& ray, float& t) = 0;

        virtual glm::mat4 translate(glm::vec3 const& p);
        virtual glm::mat4 scale(glm::vec3 const& s) const;
        virtual glm::mat4 rotate(float fi, glm::vec3 const& roVec);
        virtual void transform();
        
        virtual std::ostream& print(std::ostream& os) const;

        glm::vec3 scaling_;
        glm::vec3 translation_;
        glm::vec3 rotation_;
        float rotation_angle_;


    protected:
        std::string name_;
        std::shared_ptr<Material> material_;

        glm::mat4 world_transformation_{1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 1};
        
        glm::mat4 world_transformation_inv_{1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 1};

};

std::ostream& operator<<(std::ostream&os, Shape const& s);

#endif  //SHAPE_HPP