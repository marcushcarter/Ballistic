#include <drivers/windows/dialogs_win32.h>
#include <windows.h>
#include <commdlg.h>

namespace ballistic::drivers {

std::wstring save_file_dialog_win32(const wchar_t* p_filter, const wchar_t* p_default_ext)
{
    wchar_t path[MAX_PATH] = {};

    OPENFILENAMEW ofn{};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = GetActiveWindow();
    ofn.lpstrFilter = p_filter;
    ofn.lpstrFile = path;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrDefExt = p_default_ext;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;

    if (GetSaveFileNameW(&ofn)) {
        return std::wstring(path);
    }

    return {};
}

}