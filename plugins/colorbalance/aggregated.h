#ifndef COLORBALANCE_AGGREGATED
#define COLORBALANCE_AGGREGATED

static char *colorbalance_get_pixel1 =
	"vec4 colorbalance_get_pixel()\n"
	"{\n"
	"	return gl_FragColor;\n"
	"}\n";

static char *colorbalance_get_pixel2 =
	"uniform sampler2D tex;\n"
	"vec4 colorbalance_get_pixel()\n"
	"{\n"
	"	return texture2D(tex, gl_TexCoord[0].st);\n"
	"}\n";


static char *colorbalance_rgb_shader = 
	"uniform vec3 colorbalance_scale;\n"
	"void main()\n"
	"{\n"
	"	gl_FragColor = colorbalance_get_pixel();\n"
	"	gl_FragColor.rgb *= colorbalance_scale;\n"
	"}\n";

static char *colorbalance_yuv_shader = 
	"uniform vec3 colorbalance_scale;\n"
	"void main()\n"
	"{\n"
	"	gl_FragColor = colorbalance_get_pixel();\n"
	YUV_TO_RGB_FRAG("gl_FragColor")
	"	gl_FragColor.rgb *= colorbalance_scale;\n"
	RGB_TO_YUV_FRAG("gl_FragColor")
	"}\n";

static char *colorbalance_yuv_preserve_shader = 
	"uniform vec3 colorbalance_scale;\n"
	"void main()\n"
	"{\n"
	"	gl_FragColor = colorbalance_get_pixel();\n"
	"	float y = gl_FragColor.r;\n"
	YUV_TO_RGB_FRAG("gl_FragColor")
	"	gl_FragColor.rgb *= colorbalance_scale.rgb;\n"
	RGB_TO_YUV_FRAG("gl_FragColor")
	"	gl_FragColor.r = y;\n"
	"}\n";

#define COLORBALANCE_UNIFORMS(shader) \
	glUniform3f(glGetUniformLocation(shader, "colorbalance_scale"),  \
		get_output()->get_params()->get("COLORBALANCE_CYAN", (float)1), \
		get_output()->get_params()->get("COLORBALANCE_MAGENTA", (float)1), \
		get_output()->get_params()->get("COLORBALANCE_YELLOW", (float)1));

#endif

