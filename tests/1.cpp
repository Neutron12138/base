#include <iostream>
#define BASE_DEFINE_FLOAT_TYPE
#include "../base/base.hpp"
#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#include <glm/ext.hpp>

class MyProcessManager : public base::ProcessManager
{
public:
    ~MyProcessManager() override = default;

protected:
    void _on_first_frame() override
    {
        std::cout << "[idle frame]\ttime: " << get_total_elapsed()
                  << "\tframe: " << get_frame_count() << std::endl;
    }

    void _on_first_physics_frame() override
    {
        std::cout << "[physics frame]\ttime: " << get_total_elapsed()
                  << "\tframe: " << get_physics_frame_count() << std::endl;
    }

    void _on_frame_updated(double delta) override
    {
        std::cout << "[idle frame]\ttime: " << get_total_elapsed()
                  << "\tframe: " << get_frame_count()
                  << "\tdelta: " << delta << std::endl;
    }

    void _on_physics_frame_updated(double delta) override
    {
        std::cout << "[physics frame]\ttime: " << get_total_elapsed()
                  << "\tframe: " << get_physics_frame_count()
                  << "\tdelta: " << delta << std::endl;
    }
};

class MyNotifiable : public base::Notifiable
{
public:
    void notification(base::Enum what) override
    {
        std::cout << "notification received: " << what << std::endl;
    }
};

class MyMainLoop : public base::MainLoop
{
public:
    ~MyMainLoop() override = default;

protected:
    void _on_initialize() override {}
    void _on_update() override { request_quit(); }
    void _on_shutdown() override {}
};

int main()
{
    std::cout << "Float32: " << sizeof(base::Float32) << std::endl
              << "Float64: " << sizeof(base::Float64) << std::endl
              << "Float128: " << sizeof(base::Float128) << std::endl;

    auto manager = std::make_shared<MyProcessManager>();
    manager->set_target_fps(5);
    manager->set_target_physics_fps(10);
    manager->request_first_frame();
    for (; manager->get_physics_frame_count() <= 10; manager->update())
        ;

    auto notifiable = std::make_shared<MyNotifiable>();
    base::notify(notifiable, 114);

    MyMainLoop main_loop;
    main_loop.run();
    std::cout << "exit code: " << main_loop.get_exit_code() << std::endl;

    glm::vec3 p = {1, 0, 0};

    float angle = M_PI / 2.0f;
    glm::vec3 axis = {1, 0, 1};
    axis= glm::normalize(axis);
    axis = float(sin(angle)) * axis;
    glm::quat q;
    q.w = cos(angle);
    q.x = axis.x;
    q.y = axis.y;
    q.z = axis.z;
    q = glm::normalize(q);

    glm::vec3 v = q * p * glm::conjugate(q);

    std::cout << v.x << "," << v.y << "," << v.z << std::endl;

    return 0;
}
