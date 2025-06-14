#include <iostream>
#include <string>
#include "../src/base.hpp"

class MyNotifiable : public base::Notifiable
{
public:
    static constexpr base::Int64 NOTIFICATION_GOOD = 666;

    void notify(base::Int64 notification) override
    {
        if (notification == NOTIFICATION_GOOD)
        {
            std::cout << this << ": Good!" << std::endl;
        }
    }
};

class MyProcessManager : public base::ProcessManager
{
protected:
    void _on_first_frame() override
    {
        std::cout << "first frame\t" << get_current_fps() << std::endl;
    }

    void _on_frame_updated(double delta) override
    {
        std::cout << "process\t\t" << delta << "\t" << get_current_fps() << std::endl;
    }

    void _on_first_physics_frame() override
    {
        std::cout << "first physics frame\t" << get_current_physics_fps() << std::endl;
    }

    void _on_physics_frame_updated(double delta) override
    {
        std::cout << "physics process\t" << delta << "\t" << get_current_physics_fps() << std::endl;
    }
};

class MyEventHandler : public base::EventHandler
{
protected:
    void _handle_event(const base::EventRef &event) override
    {
        event->set_handled();
        std::cout << "event received" << std::endl;
    }
};

int main()
{
    MyNotifiable noti;
    base::Notifiable *noti_ptr = &noti;
    noti_ptr->notify(MyNotifiable::NOTIFICATION_GOOD);

    std::cout << base::to_string("aaa: ", 666, "\n");

    MyProcessManager mpm;
    mpm.request_first_frame();

    mpm.set_unlimited_fps();
    mpm.set_unlimited_physics_fps();
    for (; mpm.get_total_elapsed() <= 0.01; mpm.update())
        ;
    mpm.set_target_fps(5);
    mpm.set_target_physics_fps(10);
    for (; mpm.get_total_elapsed() <= 1.01; mpm.update())
        ;

    base::EventRef e = std::make_shared<base::Event>();
    MyEventHandler meh;
    std::cout << "event is handled: " << e->is_handled() << std::endl;
    meh.request_handle_event(e);
    std::cout << "event is handled: " << e->is_handled() << std::endl;

    return 0;
}
