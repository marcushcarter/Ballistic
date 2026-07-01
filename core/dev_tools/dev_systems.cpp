#include <core/dev_tools/dev_systems.h>

namespace ballistic {

Error DevSystems::create(Renderer& r_renderer, drivers::RenderingDeviceDriverVulkan& r_device_driver)
{
    renderer = &r_renderer;
    device_driver = &r_device_driver;
    texture_cache.create(r_device_driver);
    return Error::Ok;
}

void DevSystems::destroy()
{
    texture_cache.destroy();
}

void DevSystems::new_frame(float p_dt)
{
    (void)p_dt;
}

}