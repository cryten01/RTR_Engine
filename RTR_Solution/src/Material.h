#pragma once

#include "Utils.h"
#include "Shader.h"
#include "Texture.h"


/**
* Base material
**/

enum MaterialState	// Reference to param.state in color.frag
{
	REFLECTIVE = 0,
	REFRACTIVE = 1,
	TEXTURE = 2,
	DIFFUSE = 3		// Default state
};

class Material
{
protected:
	std::shared_ptr<Shader> _shader;

	glm::vec3 _color;
	glm::vec3 _lightCoefficients; // Reflection constants x = ambient, y = diffuse, z = specular
	float _alpha;


public:
	MaterialState _state;

	Material(std::shared_ptr<Shader> shader, glm::vec3 lightCoefficients, float specularCoefficient, glm::vec3 color);
	virtual ~Material();

	Shader* getShader();
	virtual void setUniforms();
};

class TextureMaterial : public Material
{
protected:
	std::vector<Texture> _textures;

public:
	TextureMaterial(std::shared_ptr<Shader> shader, glm::vec3 lightCoefficients, float specularCoefficient, Texture texture);
	TextureMaterial(std::shared_ptr<Shader> shader, glm::vec3 lightCoefficients, float specularCoefficient, std::vector<Texture> textures);
	virtual ~TextureMaterial();

	virtual void setUniforms();
};

