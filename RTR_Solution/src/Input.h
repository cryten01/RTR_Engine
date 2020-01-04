#pragma once
#include "Utils.h"

namespace RTREngine
{
	/**
	*	Note all callback functions and variables must be global or static in order to be C compatible
	*	For further information see: https://gamedev.stackexchange.com/questions/58541/how-can-i-associate-a-key-callback-with-a-wrapper-class-instance
	**/
	class Input
	{
	private:
		// Mouse controls
		static double mouse_x, mouse_y;

		// Camera controls
		static bool _wireframe;
		static bool _culling;
		static bool _dragging;
		static bool _strafing;
		static float _zoom;
		static float _height;
		static bool _freezeScene;

		// Post processing controls
		static bool _hdr;
		static float _exposure;

	public:
		Input(GLFWwindow* window);
		~Input();

		static double& get_mouse_x();
		static double& get_mouse_y();

		static void update(GLFWwindow* window);

		static void key_polling(GLFWwindow* window, float deltaTime);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}
