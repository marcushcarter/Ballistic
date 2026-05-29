#pragma once
#include "pch.h"
#include <core/application.h>

struct GameApplication : Application
{
    void OnInit() override;
    void OnUpdate() override;
    void OnShutdown() override;
    void OnProjectOpened(const std::filesystem::path& path) override;
    void OnProjectClosed() override;
};