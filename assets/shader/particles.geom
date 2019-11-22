#version 430 core

/** Transforms particles into a quad that always faces the cam's viewing direction */

layout (points) in;								// the particle points from the vertexShader
layout (triangle_strip, max_vertices = 4) out;	// the quads created from the particles

uniform mat4 projectionMatrix;

in VertexData {
	float TTL1;
} fromVert[];

out VertexData {
	vec2 uv;
	flat float TTL; // flat = value does not get interpolated
} fromGeom;


void main (void) {

	const vec2 particleSize = vec2(0.05, 0.05);			// defines how big the quad should be
	vec4 P = gl_in[0].gl_Position;						// particle position in view-space

	// a: left-bottom
	vec2 va = P.xy + vec2(-0.5, -0.5) * particleSize;	// gets	2D pos of vertex, expands to one corner direction * distance of particleSize
	gl_Position = projectionMatrix * vec4(va, P.zw);	// adds P.zw (same for all 4 vertices) to va and mulitplies with projectionMatrix
	fromGeom.uv = vec2(0.0, 0.0);						// sets UV or TexCoord based on corner position
	fromGeom.TTL = fromVert[0].TTL1;					// sets TTL value for vertex (same for all 4 vertices)
	EmitVertex();										// emits the vertex to the vertex stream (= add to quad)

	// d: right-bottom
	vec2 vd = P.xy + vec2(0.5, -0.5) * particleSize;
	gl_Position = projectionMatrix * vec4(vd, P.zw);
	fromGeom.uv = vec2(1.0, 0.0);
	fromGeom.TTL = fromVert[0].TTL1;
	EmitVertex();  

	// b: left-top
	vec2 vb = P.xy + vec2(-0.5, 0.5) * particleSize;
	gl_Position = projectionMatrix * vec4(vb, P.zw);
	fromGeom.uv = vec2(0.0, 1.0);
	fromGeom.TTL = fromVert[0].TTL1;
	EmitVertex();  
  
	// c: right-top
	vec2 vc = P.xy + vec2(0.5, 0.5) * particleSize;
	gl_Position = projectionMatrix * vec4(vc, P.zw);
	fromGeom.uv = vec2(1.0, 1.0);
	fromGeom.TTL = fromVert[0].TTL1;
	EmitVertex(); 

	EndPrimitive();		// completes the current output primitive on the first vertex stream (= finishes quad)
}