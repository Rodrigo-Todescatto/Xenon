// Copyright 2025 Xenon Emulator Project

#include <iostream>

#include "XGPU.h"
#include "XGPUConfig.h"
#include "XenosRegisters.h"

#include "Base/Config.h"
#include "Base/Version.h"

Xe::Xenos::XGPU::XGPU(RAM *ram) {
  // Assign RAM Pointer
  ramPtr = ram;

  memset(&xgpuConfigSpace.data, 0xf, sizeof(GENRAL_PCI_DEVICE_CONFIG_SPACE));
  // Setup config space as per dump taken from a Jasper console.
  // Located at config address 0xD0010000.
  u8 i = 0;
  for (u16 idx = 0; idx < 256; idx += 4) {
    memcpy(&xgpuConfigSpace.data[idx], &xgpuConfigMap[i], 4);
    i++;
  }

  xenosState.Regs = new u8[0xFFFFF];
  memset(xenosState.Regs, 0, 0xFFFFF);

  // Set Clocks speeds.
  u32 reg = 0x09000000;
  memcpy(&xenosState.Regs[REG_GPU_CLK], &reg, 4);
  reg = 0x11000c00;
  memcpy(&xenosState.Regs[REG_EDRAM_CLK], &reg, 4);
  reg = 0x1a000001;
  memcpy(&xenosState.Regs[REG_FSB_CLK], &reg, 4);
  reg = 0x19100000;
  memcpy(&xenosState.Regs[REG_MEM_CLK], &reg, 4);

  if (Config::gpuThreadEnabled()) {
    renderThread = std::thread(&XGPU::XenosThread, this);
  }
}

bool Xe::Xenos::XGPU::Read(u64 readAddress, u64 *data, u8 byteCount) {
  if (isAddressMappedInBAR(static_cast<u32>(readAddress))) {
    // std::cout << "Xenos Read Addr = 0x" << readAddress << std::endl;
    const u32 regIndex = (readAddress & 0xFFFFF) / 4;

    bool hit = 0;

    XeRegister reg = static_cast<XeRegister>(regIndex);

    memcpy(data, &xenosState.Regs[regIndex * 4], byteCount);
    if (regIndex == 0x00000a07)
      *data = 0x2000000;

    if (regIndex == 0x00001928)
      *data = 0x2000000;

    if (regIndex == 0x00001e54)
      *data = 0;

    return true;
  }

  return false;
}

bool Xe::Xenos::XGPU::Write(u64 writeAddress, u64 data, u8 byteCount) {
  if (isAddressMappedInBAR(static_cast<u32>(writeAddress))) {
    // std::cout << "Xenos Write Addr = 0x" << writeAddress << " data = 0x" <<
    // _byteswap_ulong(static_cast<u32>(data)) << std::endl;

    const u32 regIndex = (writeAddress & 0xFFFFF) / 4;

    bool hit = 0;

    XeRegister reg = static_cast<XeRegister>(regIndex);

    memcpy(&xenosState.Regs[regIndex * 4], &data, byteCount);
    return true;
  }

  return false;
}

void Xe::Xenos::XGPU::ConfigRead(u64 readAddress, u64 *data, u8 byteCount) {
  memcpy(data, &xgpuConfigSpace.data[readAddress & 0xFF], byteCount);
  return;
}

void Xe::Xenos::XGPU::ConfigWrite(u64 writeAddress, u64 data, u8 byteCount) {
  memcpy(&xgpuConfigSpace.data[writeAddress & 0xFF], &data, byteCount);
  return;
}

bool Xe::Xenos::XGPU::isAddressMappedInBAR(u32 address) {
  u32 bar0 = xgpuConfigSpace.configSpaceHeader.BAR0;
  u32 bar1 = xgpuConfigSpace.configSpaceHeader.BAR1;
  u32 bar2 = xgpuConfigSpace.configSpaceHeader.BAR2;
  u32 bar3 = xgpuConfigSpace.configSpaceHeader.BAR3;
  u32 bar4 = xgpuConfigSpace.configSpaceHeader.BAR4;
  u32 bar5 = xgpuConfigSpace.configSpaceHeader.BAR5;

  if (address >= bar0 && address <= bar0 + XGPU_DEVICE_SIZE ||
      address >= bar1 && address <= bar1 + XGPU_DEVICE_SIZE ||
      address >= bar2 && address <= bar2 + XGPU_DEVICE_SIZE ||
      address >= bar3 && address <= bar3 + XGPU_DEVICE_SIZE ||
      address >= bar4 && address <= bar4 + XGPU_DEVICE_SIZE ||
      address >= bar5 && address <= bar5 + XGPU_DEVICE_SIZE) {
    return true;
  }

  return false;
}

static inline int xeFbConvert(const int resWidth, const int addr) {
  const int y = addr / (resWidth * 4);
  const int x = addr % (resWidth * 4) / 4;
  const u64 offset =
      ((((y & ~31) * resWidth) + (x & ~31) * 32) +
       (((x & 3) + ((y & 1) << 2) + ((x & 28) << 1) + ((y & 30) << 5)) ^
        ((y & 8) << 2))) *
      4;
  return offset;
}

#define XE_PIXEL_TO_STD_ADDR(x, y) (y * resWidth + x) * 4
#define XE_PIXEL_TO_XE_ADDR(x, y)                                              \
  xeFbConvert(resWidth, XE_PIXEL_TO_STD_ADDR(x, y))

void Xe::Xenos::XGPU::XenosThread() {
  // TODO(bitsh1ft3r):
  // Change resolution/window size according to current AVPACK, that is
  // according to corresponding registers inside Xenos.

  // TODO(Xphalnos):
  // Find a way to change the internal resolution without crashing the display.
  // Window Resolution.
  const u32 resWidth = 1280;
  const u32 resHeight = 720;

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cout << "Failed to initialize SDL video subsystem: " << SDL_GetError()
              << std::endl;
  }

  //	Set the title.
  std::string TITLE = "Xenon " + std::string(Base::VERSION);

  //	SDL3 window properties.
  SDL_PropertiesID props = SDL_CreateProperties();
  SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING,
                        std::string(TITLE).c_str());
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER,
                        SDL_WINDOWPOS_CENTERED);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER,
                        SDL_WINDOWPOS_CENTERED);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER,
                        Config::windowWidth());
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER,
                        Config::windowHeight());
  //	Only putting this back when a Vulkan implementation is done.
  //	SDL_SetNumberProperty(props, "flags", SDL_WINDOW_VULKAN);
  SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);
  mainWindow = SDL_CreateWindowWithProperties(props);
  SDL_DestroyProperties(props);

  SDL_SetWindowMinimumSize(mainWindow, 640, 480);

  renderer = SDL_CreateRenderer(mainWindow, nullptr);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRX32,
                              SDL_TEXTUREACCESS_STREAMING, resWidth, resHeight);

  // Pixel Data pointer.
  u8 *pixels;
  // Texture Pitch.
  int pitch = resWidth * resHeight * 4;
  // Framebuffer pointer from main memory.
  u8 *fbPointer = ramPtr->getPointerToAddress(XE_FB_BASE);
  // Rendering Mode.
  bool rendering = true;
  // VSYNC Mode.
  bool VSYNC = true;
  // Set VSYNC mode to default.
  SDL_SetRenderVSync(renderer, VSYNC);
  // Fullscreen Mode.
  SDL_SetWindowFullscreen(mainWindow, Config::fullscreenMode());

  while (rendering) {
    // Process events.
    while (SDL_PollEvent(&windowEvent)) {
      switch (windowEvent.type) {
      case SDL_EVENT_QUIT:
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(mainWindow);
        rendering = false;
        break;
      case SDL_EVENT_KEY_DOWN:
        if (windowEvent.key.key == SDLK_F5) {
          SDL_SetRenderVSync(renderer, !VSYNC);
          VSYNC = !VSYNC;
        }
        if (windowEvent.key.key == SDLK_F11) {
          SDL_WindowFlags flag = SDL_GetWindowFlags(mainWindow);
          bool fullscreenMode = flag & SDL_WINDOW_FULLSCREEN;
          SDL_SetWindowFullscreen(mainWindow, !fullscreenMode);
        }
        break;
      default:
        break;
      }
    }

    // Lock the texture to write our pixels on.
    SDL_LockTexture(texture, nullptr, (void **)&pixels, &pitch);
    // Clear the backbuffer.
    SDL_RenderClear(renderer);
    // Copy the pixels.
    int stdPixPos = 0;
    int xePixPos = 0;
    for (int x = 0; x < resWidth; x++) {
      for (int y = 0; y < resHeight; y++) {
        stdPixPos = XE_PIXEL_TO_STD_ADDR(x, y);
        xePixPos = XE_PIXEL_TO_XE_ADDR(x, y);
        memcpy(pixels + stdPixPos, fbPointer + xePixPos, 4);
      }
    }
    // Unlock the texture.
    SDL_UnlockTexture(texture);
    // Render the texture to out backbuffer.
    SDL_RenderTexture(renderer, texture, nullptr, nullptr);
    // Present the new frame.
    SDL_RenderPresent(renderer);
  }
}
