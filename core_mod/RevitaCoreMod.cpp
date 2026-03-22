
#include <YYToolkit/YYTK_Shared.hpp>
#include <d3d11.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>

YYTK::YYTKInterface* yytk;

bool imguiInitialized = false;

// ReSharper disable once CppDFAConstantFunctionResult
void frameCallback(YYTK::FWFrame& frame) {
    const auto [swapChain, syncInterval, flags] = frame.Arguments();

    DXGI_SWAP_CHAIN_DESC desc;
    ID3D11Device* device = nullptr;
    if (FAILED(swapChain->GetDesc(&desc)) || FAILED(swapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device))))
        return;

    ID3D11DeviceContext* context = nullptr;
    device->GetImmediateContext(&context);

    if (!imguiInitialized) {
        ImGui_ImplWin32_EnableDpiAwareness();
        const float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGuiStyle &style = ImGui::GetStyle();
        style.WindowRounding = 3.0f;
        style.FontScaleDpi = main_scale;

        imguiInitialized = true;
        ImGui_ImplWin32_Init(desc.OutputWindow);
        ImGui_ImplDX11_Init(device, context);
    }

    ID3D11Texture2D* backBuffer = nullptr;
    if (FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
        return;

    // 2. Create a new render target view
    ID3D11RenderTargetView* rtv = nullptr;
    if (FAILED(device->CreateRenderTargetView(backBuffer, nullptr, &rtv))) {
        backBuffer->Release();
        return;
    }
    backBuffer->Release();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGui::Render();

    context->OMSetRenderTargets(1, &rtv, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    rtv->Release();
}

EXPORTED Aurie::AurieStatus ModuleInitialize(IN Aurie::AurieModule* module, IN const std::filesystem::path&) {
    // Do YYTK stuff
    yytk = YYTK::GetInterface();
    if (!yytk)
        return Aurie::AURIE_MODULE_DEPENDENCY_NOT_RESOLVED;

    yytk->CreateCallback(module, YYTK::EVENT_FRAME, frameCallback, 0);

    yytk->PrintInfo("Revita Core Mod successfully initialized!");
    return Aurie::AURIE_SUCCESS;
}
