#include <Game.h>

static bool flip;

Game::Game() :
	window(VideoMode(800, 600), "OpenGL Cube Texturing"),
	m_rotations{ 0.0f, 0.0f, 0.0f },
	m_scale{ 50.0f }
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

const int NUMBER_OF_POINTS{ 24 };

typedef struct
{
	float coordinate[3];
	float color[4];
	float texel[2];
} Vertex;

Vertex baseVertices[NUMBER_OF_POINTS]; // Cube corner positions and data
Vertex vertices[NUMBER_OF_POINTS];
GLubyte triangles[36] // Triangle indices
{
	0, 1, 2, // Front
	2, 3, 0,
	16, 17, 18, // Top
	18, 19, 16,
	20, 21, 22, // Bottom
	22, 23, 20,
	8, 9, 10, // Right
	10, 11, 8,
	12, 13, 14, // Left
	14, 15, 12,
	4, 7, 6, // Back
	6, 5, 4
};

/* Variable to hold the VBO identifier and shader data */
GLuint	index,		//Index to draw
		vsid,		//Vertex Shader ID
		fsid,		//Fragment Shader ID
		progID,		//Program ID
		vao = 0,	//Vertex Array ID
		vbo[1],		// Vertex Buffer ID
		positionID, //Position ID
		colorID,	// Color ID
		to,			// Texture ID 1 to 32
		textureID,	//Texture ID
		texelID;	// Texel ID

//const string filename = "texture.tga";
//const string filename = "cube.tga";

const string filename = "cube.tga";

int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA

unsigned char* img_data;

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	glEnable(GL_CULL_FACE);

	/* Vertices counter-clockwise winding */
	// Coordinate
	baseVertices[0].coordinate[0] = -1.0f;
	baseVertices[0].coordinate[1] = -1.0f;
	baseVertices[0].coordinate[2] = 1.0f;

	baseVertices[1].coordinate[0] = 1.0f;
	baseVertices[1].coordinate[1] = -1.0f;
	baseVertices[1].coordinate[2] = 1.0f;

	baseVertices[2].coordinate[0] = 1.0f;
	baseVertices[2].coordinate[1] = 1.0f;
	baseVertices[2].coordinate[2] = 1.0f;

	baseVertices[3].coordinate[0] = -1.0f;
	baseVertices[3].coordinate[1] = 1.0f;
	baseVertices[3].coordinate[2] = 1.0f;

	baseVertices[4].coordinate[0] = -1.0f;
	baseVertices[4].coordinate[1] = -1.0f;
	baseVertices[4].coordinate[2] = -1.0f;

	baseVertices[5].coordinate[0] = 1.0f;
	baseVertices[5].coordinate[1] = -1.0f;
	baseVertices[5].coordinate[2] = -1.0f;

	baseVertices[6].coordinate[0] = 1.0f;
	baseVertices[6].coordinate[1] = 1.0f;
	baseVertices[6].coordinate[2] = -1.0f;

	baseVertices[7].coordinate[0] = -1.0f;
	baseVertices[7].coordinate[1] = 1.0f;
	baseVertices[7].coordinate[2] = -1.0f;

	// Right
	baseVertices[8].coordinate[0] = baseVertices[2].coordinate[0];
	baseVertices[8].coordinate[1] = baseVertices[2].coordinate[1];
	baseVertices[8].coordinate[2] = baseVertices[2].coordinate[2];

	baseVertices[9].coordinate[0] = baseVertices[1].coordinate[0];
	baseVertices[9].coordinate[1] = baseVertices[1].coordinate[1];
	baseVertices[9].coordinate[2] = baseVertices[1].coordinate[2];

	baseVertices[10].coordinate[0] = baseVertices[5].coordinate[0];
	baseVertices[10].coordinate[1] = baseVertices[5].coordinate[1];
	baseVertices[10].coordinate[2] = baseVertices[5].coordinate[2];

	baseVertices[11].coordinate[0] = baseVertices[6].coordinate[0];
	baseVertices[11].coordinate[1] = baseVertices[6].coordinate[1];
	baseVertices[11].coordinate[2] = baseVertices[6].coordinate[2];

	baseVertices[8].color[0] = 1.0f;
	baseVertices[8].color[1] = 0.0f;
	baseVertices[8].color[2] = 1.0f;
	baseVertices[8].color[3] = 1.0f;

	baseVertices[9].color[0] = 0.0f;
	baseVertices[9].color[1] = 1.0f;
	baseVertices[9].color[2] = 1.0f;
	baseVertices[9].color[3] = 1.0f;

	baseVertices[10].color[0] = 0.0f;
	baseVertices[10].color[1] = 0.5f;
	baseVertices[10].color[2] = 0.5f;
	baseVertices[10].color[3] = 1.0f;

	baseVertices[11].color[0] = 0.5f;
	baseVertices[11].color[1] = 0.5f;
	baseVertices[11].color[2] = 0.5f;
	baseVertices[11].color[3] = 1.0f;

	baseVertices[8].texel[0] = 0.50f;
	baseVertices[8].texel[1] = 0.25f;

	baseVertices[9].texel[0] = 0.50f;
	baseVertices[9].texel[1] = 0.50f;

	baseVertices[10].texel[0] = 0.75f;
	baseVertices[10].texel[1] = 0.50f;

	baseVertices[11].texel[0] = 0.75f;
	baseVertices[11].texel[1] = 0.25f;

	// Left
	baseVertices[12].coordinate[0] = baseVertices[0].coordinate[0];
	baseVertices[12].coordinate[1] = baseVertices[0].coordinate[1];
	baseVertices[12].coordinate[2] = baseVertices[0].coordinate[2];

	baseVertices[13].coordinate[0] = baseVertices[3].coordinate[0];
	baseVertices[13].coordinate[1] = baseVertices[3].coordinate[1];
	baseVertices[13].coordinate[2] = baseVertices[3].coordinate[2];

	baseVertices[14].coordinate[0] = baseVertices[7].coordinate[0];
	baseVertices[14].coordinate[1] = baseVertices[7].coordinate[1];
	baseVertices[14].coordinate[2] = baseVertices[7].coordinate[2];

	baseVertices[15].coordinate[0] = baseVertices[4].coordinate[0];
	baseVertices[15].coordinate[1] = baseVertices[4].coordinate[1];
	baseVertices[15].coordinate[2] = baseVertices[4].coordinate[2];

	baseVertices[12].color[0] = 1.0f;
	baseVertices[12].color[1] = 0.0f;
	baseVertices[12].color[2] = 1.0f;
	baseVertices[12].color[3] = 1.0f;

	baseVertices[13].color[0] = 0.0f;
	baseVertices[13].color[1] = 1.0f;
	baseVertices[13].color[2] = 1.0f;
	baseVertices[13].color[3] = 1.0f;

	baseVertices[14].color[0] = 0.0f;
	baseVertices[14].color[1] = 0.5f;
	baseVertices[14].color[2] = 0.5f;
	baseVertices[14].color[3] = 1.0f;

	baseVertices[15].color[0] = 0.5f;
	baseVertices[15].color[1] = 0.5f;
	baseVertices[15].color[2] = 0.5f;
	baseVertices[15].color[3] = 1.0f;

	baseVertices[12].texel[0] = 0.25f;
	baseVertices[12].texel[1] = 0.50f;

	baseVertices[13].texel[0] = 0.25f;
	baseVertices[13].texel[1] = 0.25f;

	baseVertices[14].texel[0] = 0.0f;
	baseVertices[14].texel[1] = 0.25f;

	baseVertices[15].texel[0] = 0.0f;
	baseVertices[15].texel[1] = 0.50f;

	// Top
	baseVertices[16].coordinate[0] = baseVertices[3].coordinate[0];
	baseVertices[16].coordinate[1] = baseVertices[3].coordinate[1];
	baseVertices[16].coordinate[2] = baseVertices[3].coordinate[2];

	baseVertices[17].coordinate[0] = baseVertices[2].coordinate[0];
	baseVertices[17].coordinate[1] = baseVertices[2].coordinate[1];
	baseVertices[17].coordinate[2] = baseVertices[2].coordinate[2];

	baseVertices[18].coordinate[0] = baseVertices[6].coordinate[0];
	baseVertices[18].coordinate[1] = baseVertices[6].coordinate[1];
	baseVertices[18].coordinate[2] = baseVertices[6].coordinate[2];

	baseVertices[19].coordinate[0] = baseVertices[7].coordinate[0];
	baseVertices[19].coordinate[1] = baseVertices[7].coordinate[1];
	baseVertices[19].coordinate[2] = baseVertices[7].coordinate[2];

	baseVertices[16].color[0] = 1.0f;
	baseVertices[16].color[1] = 0.0f;
	baseVertices[16].color[2] = 1.0f;
	baseVertices[16].color[3] = 1.0f;

	baseVertices[17].color[0] = 0.0f;
	baseVertices[17].color[1] = 1.0f;
	baseVertices[17].color[2] = 1.0f;
	baseVertices[17].color[3] = 1.0f;

	baseVertices[18].color[0] = 0.0f;
	baseVertices[18].color[1] = 0.5f;
	baseVertices[18].color[2] = 0.5f;
	baseVertices[18].color[3] = 1.0f;

	baseVertices[19].color[0] = 0.5f;
	baseVertices[19].color[1] = 0.5f;
	baseVertices[19].color[2] = 0.5f;
	baseVertices[19].color[3] = 1.0f;

	baseVertices[16].texel[0] = 0.25f;
	baseVertices[16].texel[1] = 0.25f;

	baseVertices[17].texel[0] = 0.50f;
	baseVertices[17].texel[1] = 0.25f;

	baseVertices[18].texel[0] = 0.50f;
	baseVertices[18].texel[1] = 0.0f;

	baseVertices[19].texel[0] = 0.25f;
	baseVertices[19].texel[1] = 0.0f;

	// Bottom
	baseVertices[20].coordinate[0] = baseVertices[1].coordinate[0];
	baseVertices[20].coordinate[1] = baseVertices[1].coordinate[1];
	baseVertices[20].coordinate[2] = baseVertices[1].coordinate[2];

	baseVertices[21].coordinate[0] = baseVertices[0].coordinate[0];
	baseVertices[21].coordinate[1] = baseVertices[0].coordinate[1];
	baseVertices[21].coordinate[2] = baseVertices[0].coordinate[2];

	baseVertices[22].coordinate[0] = baseVertices[4].coordinate[0];
	baseVertices[22].coordinate[1] = baseVertices[4].coordinate[1];
	baseVertices[22].coordinate[2] = baseVertices[4].coordinate[2];

	baseVertices[23].coordinate[0] = baseVertices[5].coordinate[0];
	baseVertices[23].coordinate[1] = baseVertices[5].coordinate[1];
	baseVertices[23].coordinate[2] = baseVertices[5].coordinate[2];

	baseVertices[20].color[0] = 1.0f;
	baseVertices[20].color[1] = 0.0f;
	baseVertices[20].color[2] = 1.0f;
	baseVertices[20].color[3] = 1.0f;

	baseVertices[21].color[0] = 0.0f;
	baseVertices[21].color[1] = 1.0f;
	baseVertices[21].color[2] = 1.0f;
	baseVertices[21].color[3] = 1.0f;

	baseVertices[22].color[0] = 0.0f;
	baseVertices[22].color[1] = 0.5f;
	baseVertices[22].color[2] = 0.5f;
	baseVertices[22].color[3] = 1.0f;

	baseVertices[23].color[0] = 0.5f;
	baseVertices[23].color[1] = 0.5f;
	baseVertices[23].color[2] = 0.5f;
	baseVertices[23].color[3] = 1.0f;

	baseVertices[20].texel[0] = 0.50f;
	baseVertices[20].texel[1] = 0.50f;

	baseVertices[21].texel[0] = 0.25f;
	baseVertices[21].texel[1] = 0.50f;

	baseVertices[22].texel[0] = 0.25f;
	baseVertices[22].texel[1] = 0.75f;

	baseVertices[23].texel[0] = 0.50f;
	baseVertices[23].texel[1] = 0.75f;

	// Colours
	baseVertices[0].color[0] = 1.0f;
	baseVertices[0].color[1] = 0.0f;
	baseVertices[0].color[2] = 0.0f;
	baseVertices[0].color[3] = 1.0f;

	baseVertices[1].color[0] = 0.0f;
	baseVertices[1].color[1] = 1.0f;
	baseVertices[1].color[2] = 0.0f;
	baseVertices[1].color[3] = 1.0f;

	baseVertices[2].color[0] = 0.0f;
	baseVertices[2].color[1] = 0.0f;
	baseVertices[2].color[2] = 1.0f;
	baseVertices[2].color[3] = 1.0f;

	baseVertices[3].color[0] = 1.0f;
	baseVertices[3].color[1] = 1.0f;
	baseVertices[3].color[2] = 0.0f;
	baseVertices[3].color[3] = 1.0f;

	baseVertices[4].color[0] = 1.0f;
	baseVertices[4].color[1] = 0.0f;
	baseVertices[4].color[2] = 1.0f;
	baseVertices[4].color[3] = 1.0f;

	baseVertices[5].color[0] = 0.0f;
	baseVertices[5].color[1] = 1.0f;
	baseVertices[5].color[2] = 1.0f;
	baseVertices[5].color[3] = 1.0f;

	baseVertices[6].color[0] = 0.0f;
	baseVertices[6].color[1] = 0.5f;
	baseVertices[6].color[2] = 0.5f;
	baseVertices[6].color[3] = 1.0f;

	baseVertices[7].color[0] = 0.5f;
	baseVertices[7].color[1] = 0.5f;
	baseVertices[7].color[2] = 0.5f;
	baseVertices[7].color[3] = 1.0f;

	// Texels
	baseVertices[0].texel[0] = 0.25f;
	baseVertices[0].texel[1] = 0.50f;

	baseVertices[1].texel[0] = 0.25f;
	baseVertices[1].texel[1] = 0.25f;

	baseVertices[2].texel[0] = 0.50f;
	baseVertices[2].texel[1] = 0.25f;

	baseVertices[3].texel[0] = 0.50f;
	baseVertices[3].texel[1] = 0.50f;

	baseVertices[4].texel[0] = 0.75f;
	baseVertices[4].texel[1] = 0.50f;

	baseVertices[5].texel[0] = 1.0f;
	baseVertices[5].texel[1] = 0.50f;

	baseVertices[6].texel[0] = 1.0f;
	baseVertices[6].texel[1] = 0.25f;

	baseVertices[7].texel[0] = 0.75f;
	baseVertices[7].texel[1] = 0.25f;


	for (int i = 0; i < NUMBER_OF_POINTS; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vertices[i].coordinate[j] = baseVertices[i].coordinate[j];
			vertices[i].color[j] = baseVertices[i].color[j];
			vertices[i].texel[j] = baseVertices[i].texel[j];
		}
	}

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	std::string shader = ShaderReader::readFile("VertexShader.txt");
	const char* vs_src = shader.c_str(); //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	shader = ShaderReader::readFile("FragmentShader.txt");
	const char* fs_src = shader.c_str(); //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, img_data);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f / 60.0f)
	{
		clock.restart();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			m_scale += 10.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			m_scale -= 10.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			m_rotations.x += 0.8f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			m_rotations.y += 0.8f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			m_rotations.z += 0.8f;
		}

		cube::Matrix3f transformationMatrix{ 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		transformationMatrix = transformationMatrix * cube::Matrix3f::Scale3D(m_scale);

		transformationMatrix = transformationMatrix * cube::Matrix3f::RotationX(m_rotations.x);
		transformationMatrix = transformationMatrix * cube::Matrix3f::RotationY(m_rotations.y);
		transformationMatrix = transformationMatrix * cube::Matrix3f::RotationZ(m_rotations.z);

		for (int i = 0; i < NUMBER_OF_POINTS; i++)
		{
			cube::Vector3f vector{ baseVertices[i].coordinate[0], baseVertices[i].coordinate[1], baseVertices[i].coordinate[2] };

			vector = transformationMatrix * vector;

			vertices[i].coordinate[0] = vector.x;
			vertices[i].coordinate[1] = vector.y;
			vertices[i].coordinate[2] = vector.z;
		}

	}

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertices, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
	stbi_image_free(img_data); //Free image
}

