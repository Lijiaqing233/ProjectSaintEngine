/*
 * Vulkan entry points
 *
 * Platform specific macros for the example main entry points
 * 
 * Copyright (C) 2024 by Sascha Willems - www.saschawillems.de
 *
 * This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
 */

#if defined(_WIN32)
/*
 * Windows
 */
#define __MAIN__()																		\
Renderer *renderer;																		\
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)						\
{																									\
	if (renderer != NULL)																		\
	{																								\
		renderer->handleMessages(hWnd, uMsg, wParam, lParam);									\
	}																								\
	return (DefWindowProc(hWnd, uMsg, wParam, lParam));												\
}																									\
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)									\
{																									\
	for (int32_t i = 0; i < __argc; i++) { Renderer::args.push_back(__argv[i]); };  			\
	renderer = new Renderer();															\
	renderer->initVulkan();																	\
	renderer->setupWindow(hInstance, WndProc);													\
	renderer->prepare();																		\
	renderer->renderLoop();																	\
	delete(renderer);																			\
	return 0;																						\
}

#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
/*
 * Android
 */
#define VULKAN_EXAMPLE_MAIN()																		\
Renderer *renderer;																		\
void android_main(android_app* state)																\
{																									\
	renderer = new Renderer();															\
	state->userData = renderer;																\
	state->onAppCmd = Renderer::handleAppCommand;												\
	state->onInputEvent = Renderer::handleAppInput;											\
	androidApp = state;																				\
	vks::android::getDeviceConfig();																\
	renderer->renderLoop();																	\
	delete(renderer);																			\
}

#elif defined(_DIRECT2DISPLAY)
/*
 * Direct-to-display
 */
#define VULKAN_EXAMPLE_MAIN()																		\
Renderer *renderer;																		\
static void handleEvent()                                											\
{																									\
}																									\
int main(const int argc, const char *argv[])													    \
{																									\
	for (size_t i = 0; i < argc; i++) { Renderer::args.push_back(argv[i]); };  				\
	renderer = new Renderer();															\
	renderer->initVulkan();																	\
	renderer->prepare();																		\
	renderer->renderLoop();																	\
	delete(renderer);																			\
	return 0;																						\
}

#elif defined(VK_USE_PLATFORM_DIRECTFB_EXT)
/*
 * Direct FB
 */
#define VULKAN_EXAMPLE_MAIN()																		\
Renderer *renderer;																		\
static void handleEvent(const DFBWindowEvent *event)												\
{																									\
	if (renderer != NULL)																		\
	{																								\
		renderer->handleEvent(event);															\
	}																								\
}																									\
int main(const int argc, const char *argv[])													    \
{																									\
	for (size_t i = 0; i < argc; i++) { Renderer::args.push_back(argv[i]); };  				\
	renderer = new Renderer();															\
	renderer->initVulkan();																	\
	renderer->setupWindow();					 												\
	renderer->prepare();																		\
	renderer->renderLoop();																	\
	delete(renderer);																			\
	return 0;																						\
}

#elif (defined(VK_USE_PLATFORM_WAYLAND_KHR) || defined(VK_USE_PLATFORM_HEADLESS_EXT))
 /*
  * Wayland / headless
  */
#define VULKAN_EXAMPLE_MAIN()																		\
Renderer *renderer;																		\
int main(const int argc, const char *argv[])													    \
{																									\
	for (size_t i = 0; i < argc; i++) { Renderer::args.push_back(argv[i]); };  				\
	renderer = new Renderer();															\
	renderer->initVulkan();																	\
	renderer->setupWindow();					 												\
	renderer->prepare();																		\
	renderer->renderLoop();																	\
	delete(renderer);																			\
	return 0;																						\
}

#elif defined(VK_USE_PLATFORM_XCB_KHR)
/*
 * X11 Xcb
 */
#define VULKAN_EXAMPLE_MAIN()																		\
Renderer *renderer;																		\
static void handleEvent(const xcb_generic_event_t *event)											\
{																									\
	if (renderer != NULL)																		\
	{																								\
		renderer->handleEvent(event);															\
	}																								\
}																									\
int main(const int argc, const char *argv[])													    \
{																									\
	for (size_t i = 0; i < argc; i++) { Renderer::args.push_back(argv[i]); };  				\
	renderer = new Renderer();															\
	renderer->initVulkan();																	\
	renderer->setupWindow();					 												\
	renderer->prepare();																		\
	renderer->renderLoop();																	\
	delete(renderer);																			\
	return 0;																						\
}

#elif (defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK) || defined(VK_USE_PLATFORM_METAL_EXT))
/*
 * iOS and macOS (using MoltenVK)
 */
#if defined(VK_EXAMPLE_XCODE_GENERATED)
#define VULKAN_EXAMPLE_MAIN()																		\
Renderer *renderer;																		\
int main(const int argc, const char *argv[])														\
{																									\
	@autoreleasepool																				\
	{																								\
		for (size_t i = 0; i < argc; i++) { Renderer::args.push_back(argv[i]); };				\
		renderer = new Renderer();														\
		renderer->initVulkan();																\
		renderer->setupWindow(nullptr);														\
		renderer->prepare();																	\
		renderer->renderLoop();																\
		delete(renderer);																		\
	}																								\
	return 0;																						\
}
#else
#define VULKAN_EXAMPLE_MAIN()
#endif

#elif defined(VK_USE_PLATFORM_SCREEN_QNX)
/*
 * QNX Screen
 */
#define VULKAN_EXAMPLE_MAIN()																		\
Renderer *renderer;																		\
int main(const int argc, const char *argv[])														\
{																									\
	for (int i = 0; i < argc; i++) { Renderer::args.push_back(argv[i]); };						\
	renderer = new Renderer();															\
	renderer->initVulkan();																	\
	renderer->setupWindow();																	\
	renderer->prepare();																		\
	renderer->renderLoop();																	\
	delete(renderer);																			\
	return 0;																						\
}
#endif
