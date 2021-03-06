#version 330 core

in vec3 frag_normal;
in vec3 frag_position;

layout(location = 0) out vec4 color;

uniform float ambient_strength = 0.1;

uniform vec3 light_position = vec3(100.0, 0.0, 100.0);
uniform vec3 light_color = vec3(1.0);
uniform vec3 object_color;

vec3 transformation(vec3 v)
{
	return vec3(v.y, v.z, v.x);
}

void main()
{
	// ambient
	vec3 ambient = ambient_strength * light_color;

	// diffuse
	vec3 normal = normalize(frag_normal);
	vec3 light_dir = normalize(transformation(light_position) - frag_position);
	float diff = max(dot(normal, light_dir), 0.0);
	vec3 diffuse = diff * light_color;

	vec3 result = (ambient + diffuse) * object_color;

	color = vec4(result, 1.0);
}