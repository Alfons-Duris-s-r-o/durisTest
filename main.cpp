#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

[[noreturn]]
int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    IMMDeviceEnumerator *deviceEnumerator;
    CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&deviceEnumerator));

    IMMDevice *device;
    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);

    IAudioEndpointVolume *endpointVolume;

    device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr,
                     reinterpret_cast<void **>(&endpointVolume));

    while (true) {
        endpointVolume->SetMute(true, nullptr);
        endpointVolume->SetMasterVolumeLevelScalar(0.1, nullptr);
        Beep(1600, 200);
        //Beep (3300,200);
        //Beep (4300,200);
    }
}
