#include <editor/editor_application.h>
#include <windows.h>
#include <cstdio>
#include <shlobj.h>
#include <filesystem>

std::filesystem::path get_editor_config_path()
{
    PWSTR roaming = nullptr;
    SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &roaming);
    std::filesystem::path dir = roaming;
    CoTaskMemFree(roaming);
    dir /= L"Ballistic";
    dir /= L"Ballistic Engine";
    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    return dir / L"editor_config.ini";
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    bool has_console = AttachConsole(ATTACH_PARENT_PROCESS) != 0;
    
    FILE* dummy;
    if (has_console) {
        freopen_s(&dummy, "CONOUT$", "w", stdout);
        freopen_s(&dummy, "CONOUT$", "w", stderr);
        freopen_s(&dummy, "CONIN$", "r", stdin);
    } else {
        freopen_s(&dummy, "NUL", "w", stdout);
        freopen_s(&dummy, "NUL", "w", stderr);
        freopen_s(&dummy, "NUL", "r", stdin);
    }

    std::string ini_path = get_editor_config_path().string();

    ballistic::ApplicationCreateInfo info;
    info.window_title = "Ballistic Editor";
    info.width = 1280;
    info.height = 720;
    info.ini_path = ini_path.c_str();

    ballistic::EditorApplication app;
    app.create(info);
    return app.run();
}