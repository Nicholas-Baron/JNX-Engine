#ifndef _JNX_ENGINE
#define _JNX_ENGINE

#include "util/Vec3d.h"
#include "rendering/Shader.h"
#include "rendering/Renderer.h"
#include "Input.h"
#include "GameObject.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

/*
* Purpose: Central include for JNX engine
* @author Nicholas Baron
*
*/
enum class ProjectionMode { ORTHO, PERSPECTIVE };

class JNX_Engine {
private:
	static constexpr auto Z_NEAR = 0.1f, Z_FAR = 100.0f;

	GLFWwindow* window;
	Shader* shader;

	std::vector<GameObject*> gameObjects;

	unsigned width, height;

	bool loaded;
	glm::mat4 proj, trans;

	ProjectionMode projMode;

	//Frame counting variables
	double lastPrint = time(), lastDelta = time();
	unsigned numFrames, lastFPS;
	unsigned long totalFrames;
	bool printFrameTime = true;
public:
	JNX_Engine(unsigned wide, unsigned high, bool vsync, bool initNow = true);
	~JNX_Engine();
	bool init(bool vsync = true);

	inline bool isLoaded() const { return loaded; }
	inline bool running() const { return !glfwWindowShouldClose(window); }
	inline unsigned long totalFrameCount() const { return totalFrames; }
	inline void cleanBuffers() const { Renderer::clear(); }
	inline static double time() { return glfwGetTime(); }
	inline ProjectionMode currentProjection() const { return projMode; }
	inline glm::mat4 viewProjection() const { return proj * trans; }
	inline float aspectRatio() const { return static_cast<float>(width) / height; }
	inline std::string version() const { return "0.1a"; }
	inline void setPrintFrameTime(bool val) { printFrameTime = val; }

	void renderGameObject(GameObject* go) const;
	void renderGameObjects() const;
	void updateGameObjects();

	void setProjectionOrtho(float left, float right, float up, float down);
	void setOrthoCoordsFromCenter(float height);
	void setOrthoCoordsFromTopLeft(float height);
	//FOV needs to be in radians
	inline void setProjectionPerspective(float fov) { setProjectionPerspective(fov, aspectRatio()); }
	//FOV needs to be in radians
	void setProjectionPerspective(float fov, float aspectRatio, float near = Z_NEAR, float far = Z_FAR);
	void setCameraTranslate(const Vec3d& pos);
	void loadShader(const std::string& file);
	void swapBuffers();
	void registerGameObject(GameObject* go) { gameObjects.push_back(go); }
	void cleanRegisteredGOs(bool deleteCall = true);
};

#endif
