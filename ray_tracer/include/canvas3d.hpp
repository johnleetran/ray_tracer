#include "../include/camera3d.hpp"
#include "../include/color3d.hpp"
#include "../include/ray_for_pixel3d.hpp"
#include "../include/world3d.hpp"

#include <atomic>
#include <future>
#include <unordered_map>
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

        // std::vector<std::vector<Color3D<T>>> render(Camera3D<T> camera, World3D<T> world){
        //     for(int y = 0; y < camera.vsize; y++){
        //         for(int x =0; x < camera.hsize; x++){
        //             Ray3D<T> ray = RayForPixel3D<T>::ray_for_pixel(camera, x, y);
        //             Color3D<T> c = world.color_at(ray);
        //             write_pixels(x, y, c);
        //             std::cout << "x: " << x << " y: " << y << std::endl;
        //             if(x == 0){
        //                 canvas_to_ppm("./preview.ppm");
        //             }
        //         }
        //     }
        //     return colors;
        // }

        std::mutex mtx;
        std::vector<std::vector<Color3D<T>>> render(Camera3D<T> &camera, World3D<T> &world){
            int offset = camera.vsize / 4;

            auto h1 = std::async(std::launch::async, [&] {
                render_helper(camera, world, 0, camera.hsize, 0, offset);
            });

            auto h2 = std::async(std::launch::async, [&] {
                render_helper(camera, world, 0, camera.hsize, offset, offset*2);
            });

            auto h3 = std::async(std::launch::async, [&] {
                render_helper(camera, world, 0, camera.hsize, offset * 2, offset * 3);
            });

            auto h4 = std::async(std::launch::async, [&] {
                render_helper(camera, world, 0, camera.hsize, offset * 3, camera.vsize);
            });

            h1.get();
            h2.get();
            h3.get();
            h4.get();


            return colors;
        }

        std::vector<std::vector<Color3D<T>>> render_helper(Camera3D<T> &camera, World3D<T> &world, int from_x, int to_x, int from_y, int to_y)
        {
            for (int y = from_y; y < to_y; y++)
            {
                for (int x = from_x; x < to_x; x++)
                {
                    Ray3D<T> ray = RayForPixel3D<T>::ray_for_pixel(camera, x, y);
                    Color3D<T> c = world.color_at(ray);
                    write_pixels(x, y, c);
                    std::cout << "x: " << x << " y: " << y << std::endl;
                    if (x == to_x - 1)
                    {
                        mtx.lock();
                        canvas_to_ppm("./preview.ppm");
                        mtx.unlock();
                    }
                }
            }
            canvas_to_ppm("./image.ppm");
            return colors;
        }

        // std::vector<std::vector<Color3D<T>>> render_helper(Camera3D<T> &camera, World3D<T> &world, int seed)
        // {
        //     int min_x = 0;
        //     int max_x = camera.hsize;
        //     int min_y = 0;
        //     int max_y = camera.vsize;
        //     std::atomic<int> total_count = 0;
        //     float max_count = max_x * max_y;
        //     float precentage_done = 0.0;
        //     std::unordered_map<std::string, bool> has_seen{};
        //     srand(seed);

        //     while (precentage_done < 1.0)
        //     {
        //         int x = rand() % (max_x - min_x) + min_x;
        //         int y = rand() % (max_y - min_y) + min_y;
        //         //std::cout << "x: " << x << " y: " << y << std::endl;
        //         std::string s = std::to_string(x) + "," + std::to_string(y);
        //         if (has_seen.find(s) == has_seen.end())
        //         {
        //             //std::cout << total_count << std::endl;
        //             has_seen[s] = true;
        //             Ray3D<T> ray = RayForPixel3D<T>::ray_for_pixel(camera, x, y);
        //             Color3D<T> c = world.color_at(ray);
        //             write_pixels(x, y, c);

        //             if (total_count%500 == 0 && seed == 1)
        //             {
        //                 mtx.lock();
        //                 canvas_to_ppm("./preview.ppm");
        //                 mtx.unlock();
        //             }
        //             total_count++;
        //         }else{
        //             std::cout << "skipping because it has been seen " << s << std::endl;
        //         }
        //         precentage_done = total_count / max_count;
        //         std::cout << precentage_done << std::endl;
        //     }
        //     return colors;
        // }

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