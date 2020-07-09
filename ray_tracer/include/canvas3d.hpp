#include "../include/camera3d.hpp"
#include "../include/color3d.hpp"
#include "../include/ray_for_pixel3d.hpp"
#include "../include/world3d.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <vector>

#pragma once
using namespace Ray_Tracer;
namespace Ray_Tracer
{
    template <typename T>
    class Canvas3D{
        public:
        int width;
        int height;
        const int color_clamp = 255;
        //std::vector<Ray_Tracer::Color3D<float>> colors;
        std::vector<std::vector<Ray_Tracer::Color3D<T>>> colors;
        Canvas3D(T width, T height) : width(width), height(height)
        {
            for(int i = 0; i < width; i++){
                colors.push_back(std::vector<Ray_Tracer::Color3D<T>>{});
                for (int j = 0; j < height; j++)
                {
                    colors[i].push_back(Ray_Tracer::Color3D<T>(0.f, 0.f, 0.f));
                }
            }
        }

        void write_pixels(int x, int y, Ray_Tracer::Color3D<T> color){
            //colors[x][height - y] = color;
            colors[x][y] = color;
        }

        std::vector<std::vector<Color3D<T>>> render(Camera3D<T> camera, World3D<T> world){
            for(int y = 0; y < camera.vsize; y++){
                for(int x =0; x < camera.hsize; x++){
                    Ray3D<T> ray = RayForPixel3D<T>::ray_for_pixel(camera, x, y);
                    Color3D<T> c = world.color_at(ray);
                    write_pixels(x, y, c);
                    std::cout << "x: " << x << " y: " << y << std::endl;
                }
            }
            return colors;
        }

        Ray_Tracer::Color3D<T> getPixel(int x, int y)
        {
            //return colors[x][height - y];
            return colors[x][y];
        }

        int toInt(T x)
        {
            int val = std::floor(x * 255);
            if(val > color_clamp){
                val = color_clamp;
            }
            else if(val < 0)
            {
                val = 0;
            }
            return val;
        }

        void canvas_to_ppm(std::string filename)
        {
            FILE *f = fopen(filename.c_str(), "w"); // Write image to PPM file.
            fprintf(f, "P3\n%d %d\n%d\n", width, height, color_clamp);

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {

                    fprintf(f, "%d %d %d ", toInt(colors[j][i].r), toInt(colors[j][i].g), toInt(colors[j][i].b));
                }
                fprintf(f, "\n");
            }
            fclose(f);
        }
    };
}