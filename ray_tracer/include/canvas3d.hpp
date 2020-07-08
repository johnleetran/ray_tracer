#include <vector>
#include "../include/color3d.hpp"
#include <stdlib.h>
#include <stdio.h>

#pragma once
namespace Ray_Tracer
{
    namespace Canvas3d{
        class Canvas3d{
            public:
            int width;
            int height;
            const int color_clamp = 255;
            //std::vector<Ray_Tracer::Color3D::Color3D<float>> colors;
            std::vector<std::vector<Ray_Tracer::Color3D::Color3D<float>>> colors;
            Canvas3d(int width, int height) : width(width), height(height)
            {
                for(int i = 0; i < width; i++){
                    colors.push_back(std::vector<Ray_Tracer::Color3D::Color3D<float>>{});
                    for (int j = 0; j < height; j++)
                    {
                        colors[i].push_back(Ray_Tracer::Color3D::Color3D<float>(0.f, 0.f, 0.f));
                    }
                }
            }

            void write_pixels(int x, int y, Ray_Tracer::Color3D::Color3D<float> color){
                //colors[x][height - y] = color;
                colors[x][y] = color;
            }

            Ray_Tracer::Color3D::Color3D<float> getPixel(int x, int y)
            {
                //return colors[x][height - y];
                return colors[x][y];
            }

            int toInt(double x)
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
                FILE *f = fopen("image.ppm", "w"); // Write image to PPM file.
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
}