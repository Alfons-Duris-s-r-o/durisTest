#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

[[noreturn]]
int main() {
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    IMMDeviceEnumerator *deviceEnumerator;
    CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&deviceEnumerator));

    IMMDevice *device;
    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);

    IAudioEndpointVolume *endpointVolume;

    device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL,
                     reinterpret_cast<void **>(&endpointVolume));

    while (true) {
        endpointVolume->SetMasterVolumeLevelScalar(1., NULL);
        Beep(16000, 200);
        //Beep (3300,200);
        //Beep (4300,200);
    }
}
