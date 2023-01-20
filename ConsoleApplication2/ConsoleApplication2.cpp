// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"

#include "rtweekend.h"

#include <iostream>
#include <fstream>

#include "camera.h"

#include <string>
#include <cstdlib>
bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

double hit_sphere_normal(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0 ;
    }
    else {
        return ((-b - sqrt(discriminant)) / (2.0 * a));
    }

}

color ray_color(const ray& r,const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);//why 0.5? : because unit_direction.y() is from 
    //-1 to 1 , and we want t from 0 to 1, then we need to +1 and then *0.5
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);

}
color ray_color_normal(const ray& r) {
    auto t = hit_sphere_normal(point3(0, 0, -1), 0.5, r);
    if ( t > 0.0 ) {
        vec3 uni_dir = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(uni_dir.x() + 1, uni_dir.y() + 1, uni_dir.z() + 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);//why 0.5? : because unit_direction.y() is from 
    //-1 to 1 , and we want t from 0 to 1, then we need to +1 and then *0.5
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);

}
int main()
{
    //Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;

    std::string oldName, newName, address, filename;
    address = "D:\\tsinghua_me\\raytracing in one week\\program\\ConsoleApplication2\\ConsoleApplication2\\";
	filename = "image_tot";
    ofstream outfile;
    oldName = address + filename + ".txt";
	newName = address + filename + ".ppm";
    outfile.open(oldName);

    //wolrd
    hittable_list world;
    //world.add(make_shared<sphere>(point3(0, -100.5, 0), 100));
    world.add(make_shared<sphere>(point3(0.5, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(-0.5, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    //Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    camera cam;

    //Render

  

    outfile << "P3\n" << image_width << " " << image_height << "\n255\n";

    
    for (int j = image_height - 1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }
            write_color(outfile, pixel_color, samples_per_pixel);


        }

    }

    outfile.close();
    
    

    //change the txt to ppm file
	if (!rename(oldName.c_str(), newName.c_str()))
	{
		std::cerr << "rename success "<< std::endl;
	}
	else
	{
		std::cerr << "\nrename error "<< std::endl;
	}
 


    std::cerr << "\nDone,\n";

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
