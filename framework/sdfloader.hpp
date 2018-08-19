#ifndef SDFLOADER_HPP
#define SDFLOADER_HPP

#include "findmaterial.hpp"
#include "Scene.hpp"

void load_sdf(std::string filename, Scene &scene)
{

    std::ifstream ifs;
    std::string dir = "../sdf/" + filename;
    ifs.open(dir);

    if (ifs)
    {
        std::cout << "Sdf file loaded from: " << dir << endl;
        std::string line_buffer;

        while (std::getline(ifs, line_buffer))
        {

            std::stringstream current_line_stream(line_buffer);

            std::string first_symbol;

            current_line_stream >> first_symbol;

            if ("define" == first_symbol)
            {

                std::string variable_name;
                current_line_stream >> variable_name;

                if ("material" == variable_name)
                {
                    std::string mat_name;
                    current_line_stream >> mat_name;

                    float material_koof[10];

                    for (int i = 0; i < 10; i++)
                    {
                        current_line_stream >> material_koof[i];
                    }

                    std::shared_ptr<Material> neu_material = std::make_shared<Material>(mat_name,
                                                                                        Color{material_koof[0], material_koof[1], material_koof[2]},
                                                                                        Color{material_koof[3], material_koof[4], material_koof[5]},
                                                                                        Color{material_koof[6], material_koof[7], material_koof[8]},
                                                                                        material_koof[9]);

                    scene.material_vector.push_back(neu_material);
/*                     scene.material_map.insert(make_pair(neu_material->name_, neu_material));
                    scene.material_set.insert(neu_material); */
                }

                else if ("shape" == variable_name)
                {
                    std::string shape_type;
                    current_line_stream >> shape_type;

                    if ("box" == shape_type)
                    {

                        std::string shape_name;
                        current_line_stream >> shape_name;

                        float shape_points[6];

                        for (int i = 0; i < 6; i++)
                        {
                            current_line_stream >> shape_points[i];
                        }

                        std::string mat_name;
                        current_line_stream >> mat_name;

                        std::shared_ptr<Shape> neu_box = std::make_shared<Box>(vec3(shape_points[0], shape_points[1], shape_points[2]),
                                                                               vec3(shape_points[3], shape_points[4], shape_points[5]),
                                                                               shape_name,
                                                                               findMaterialVector(mat_name, scene.material_vector));

                        scene.shape_vector.push_back(neu_box);
                    }

                    else if ("sphere" == shape_type)
                    {
                        std::string shape_name;
                        current_line_stream >> shape_name;

                        float shape_points[4];

                        for (int i = 0; i < 4; i++)
                        {
                            current_line_stream >> shape_points[i];
                        }

                        std::string mat_name;
                        current_line_stream >> mat_name;

                        std::shared_ptr<Shape> neu_sphere = std::make_shared<Sphere>(vec3(shape_points[0], shape_points[1], shape_points[2]),
                                                                                     shape_points[3],
                                                                                     findMaterialVector(mat_name, scene.material_vector),
                                                                                     shape_name);

                        scene.shape_vector.push_back(neu_sphere);
                    }
                }

                else if ("light" == variable_name)
                {
                    std::string light_name;
                    current_line_stream >> light_name;

                    float light_att[7];

                    for (int i = 0; i < 4; i++)
                    {
                        current_line_stream >> light_att[i];
                    }

                    std::shared_ptr<Light> neu_light = std::make_shared<Light>(light_name,
                                                                               vec3(light_att[0], light_att[1], light_att[2]),
                                                                               Color(light_att[3], light_att[4], light_att[5]),
                                                                               light_att[6]);

                    scene.light_vector.push_back(neu_light);
                }

                else if ("camera" == variable_name){
                    Camera temp;
                    std::string camera_name;

                    current_line_stream >> temp._name;
                    current_line_stream >> temp._fov_x;

                    scene._camera = temp;

                }
            }
        }

        scene._name = filename.substr(0,5);
    }

    else
    {
        cout << "file not found" << endl;
    }

    ifs.close();
};

#endif