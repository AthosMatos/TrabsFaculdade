#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <texture.hpp>
#include <glm.hpp>

#include "objloader.hpp"

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide : 
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);
		out_normals .push_back(normal);
	
	}
	fclose(file);
	return true;
}

bool loadObj2(std::string filename,
    bool isRHCoordSys,
    bool computeNormals,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
    )
{
    std::wifstream fileIn(filename.c_str());    //Open file
    std::wstring meshMatLib;                    //String to hold our obj material library filename

    std::vector<std::wstring> meshMaterials;

    //Vertex definition indices
    std::vector<int> vertPosIndex;
    std::vector<int> vertNormIndex;
    std::vector<int> vertTCIndex;

    std::vector<int> indices;

    //Make sure we have a default if no tex coords or normals are defined
    bool hasTexCoord = false;
    bool hasNorm = false;

    //Temp variables to store into vectors
    std::wstring meshMaterialsTemp;
    int vertPosIndexTemp;
    int vertNormIndexTemp;
    int vertTCIndexTemp;

    wchar_t checkChar;        //The variable we will use to store one char from file at a time
    std::wstring face;        //Holds the string containing our face vertices
    int vIndex = 0;            //Keep track of our vertex index count
    int triangleCount = 0;    //Total Triangles
    int totalVerts = 0;
    int meshTriangles = 0;

    int meshSubsets = 0;
    std::vector<int> subsetIndexStart;
    std::vector<int> subsetMaterialArray;
    
    std::vector<GLuint> meshSRV;
    std::vector<std::wstring> textureNameArray;
    std::vector<SurfaceMaterial> material;

    //Check to see if the file was opened
    if (fileIn)
    {
        while (fileIn)
        {
            checkChar = fileIn.get();    //Get next char

            switch (checkChar)
            {
            case '#':
                checkChar = fileIn.get();
                while (checkChar != '\n')
                    checkChar = fileIn.get();
                break;
            case 'v':    //Get Vertex Descriptions
                checkChar = fileIn.get();
                if (checkChar == ' ')    //v - vert position
                {
                    float vz, vy, vx;
                    fileIn >> vx >> vy >> vz;    //Store the next three types

                    if (isRHCoordSys)    //If model is from an RH Coord System
                        out_vertices.push_back(glm::vec3(vx, vy, vz * -1.0f));    //Invert the Z axis
                    else
                        out_vertices.push_back(glm::vec3(vx, vy, vz));
                }
                if (checkChar == 't')    //vt - vert tex coords
                {
                    float vtcu, vtcv;
                    fileIn >> vtcu >> vtcv;        //Store next two types

                    if (isRHCoordSys)    //If model is from an RH Coord System
                        out_uvs.push_back(glm::vec2(vtcu, 1.0f - vtcv));    //Reverse the "v" axis
                    else
                        out_uvs.push_back(glm::vec2(vtcu, vtcv));

                    hasTexCoord = true;    //We know the model uses texture coords
                }
                //Since we compute the normals later, we don't need to check for normals
                //In the file, but i'll do it here anyway
                if (checkChar == 'n')    //vn - vert normal
                {
                    float vnx, vny, vnz;
                    fileIn >> vnx >> vny >> vnz;    //Store next three types

                    if (isRHCoordSys)    //If model is from an RH Coord System
                        out_normals.push_back(glm::vec3(vnx, vny, vnz * -1.0f));    //Invert the Z axis
                    else
                        out_normals.push_back(glm::vec3(vnx, vny, vnz));

                    hasNorm = true;    //We know the model defines normals
                }
                break;

                //New group (Subset)
            case 'g':    //g - defines a group
                checkChar = fileIn.get();
                if (checkChar == ' ')
                {
                    subsetIndexStart.push_back(vIndex);        //Start index for this subset
                    meshSubsets++;
                }
                break;

                //Get Face Index
            case 'f':    //f - defines the faces
                checkChar = fileIn.get();
                if (checkChar == ' ')
                {
                    face = L"";
                    std::wstring VertDef;    //Holds one vertex definition at a time
                    triangleCount = 0;

                    checkChar = fileIn.get();
                    while (checkChar != '\n')
                    {
                        face += checkChar;            //Add the char to our face string
                        checkChar = fileIn.get();    //Get the next Character
                        if (checkChar == ' ')        //If its a space...
                            triangleCount++;        //Increase our triangle count
                    }

                    //Check for space at the end of our face string
                    if (face[face.length() - 1] == ' ')
                        triangleCount--;    //Each space adds to our triangle count

                    triangleCount -= 1;        //Ever vertex in the face AFTER the first two are new faces

                    std::wstringstream ss(face);

                    if (face.length() > 0)
                    {
                        int firstVIndex, lastVIndex;    //Holds the first and last vertice's index

                        for (int i = 0; i < 3; ++i)        //First three vertices (first triangle)
                        {
                            ss >> VertDef;    //Get vertex definition (vPos/vTexCoord/vNorm)

                            std::wstring vertPart;
                            int whichPart = 0;        //(vPos, vTexCoord, or vNorm)

                            //Parse this string
                            for (int j = 0; j < VertDef.length(); ++j)
                            {
                                if (VertDef[j] != '/')    //If there is no divider "/", add a char to our vertPart
                                    vertPart += VertDef[j];

                                //If the current char is a divider "/", or its the last character in the string
                                if (VertDef[j] == '/' || j == VertDef.length() - 1)
                                {
                                    std::wistringstream wstringToInt(vertPart);    //Used to convert wstring to int

                                    if (whichPart == 0)    //If vPos
                                    {
                                        wstringToInt >> vertPosIndexTemp;
                                        vertPosIndexTemp -= 1;        //subtract one since c++ arrays start with 0, and obj start with 1

                                        //Check to see if the vert pos was the only thing specified
                                        if (j == VertDef.length() - 1)
                                        {
                                            vertNormIndexTemp = 0;
                                            vertTCIndexTemp = 0;
                                        }
                                    }

                                    else if (whichPart == 1)    //If vTexCoord
                                    {
                                        if (vertPart != L"")    //Check to see if there even is a tex coord
                                        {
                                            wstringToInt >> vertTCIndexTemp;
                                            vertTCIndexTemp -= 1;    //subtract one since c++ arrays start with 0, and obj start with 1
                                        }
                                        else    //If there is no tex coord, make a default
                                            vertTCIndexTemp = 0;

                                        //If the cur. char is the second to last in the string, then
                                        //there must be no normal, so set a default normal
                                        if (j == VertDef.length() - 1)
                                            vertNormIndexTemp = 0;

                                    }
                                    else if (whichPart == 2)    //If vNorm
                                    {
                                        std::wistringstream wstringToInt(vertPart);

                                        wstringToInt >> vertNormIndexTemp;
                                        vertNormIndexTemp -= 1;        //subtract one since c++ arrays start with 0, and obj start with 1
                                    }

                                    vertPart = L"";    //Get ready for next vertex part
                                    whichPart++;    //Move on to next vertex part                    
                                }
                            }

                            //Check to make sure there is at least one subset
                            if (meshSubsets == 0)
                            {
                                subsetIndexStart.push_back(vIndex);        //Start index for this subset
                                meshSubsets++;
                            }

                            //Avoid duplicate vertices
                            bool vertAlreadyExists = false;
                            if (totalVerts >= 3)    //Make sure we at least have one triangle to check
                            {
                                //Loop through all the vertices
                                for (int iCheck = 0; iCheck < totalVerts; ++iCheck)
                                {
                                    //If the vertex position and texture coordinate in memory are the same
                                    //As the vertex position and texture coordinate we just now got out
                                    //of the obj file, we will set this faces vertex index to the vertex's
                                    //index value in memory. This makes sure we don't create duplicate vertices
                                    if (vertPosIndexTemp == vertPosIndex[iCheck] && !vertAlreadyExists)
                                    {
                                        if (vertTCIndexTemp == vertTCIndex[iCheck])
                                        {
                                            indices.push_back(iCheck);        //Set index for this vertex
                                            vertAlreadyExists = true;        //If we've made it here, the vertex already exists
                                        }
                                    }
                                }
                            }

                            //If this vertex is not already in our vertex arrays, put it there
                            if (!vertAlreadyExists)
                            {
                                vertPosIndex.push_back(vertPosIndexTemp);
                                vertTCIndex.push_back(vertTCIndexTemp);
                                vertNormIndex.push_back(vertNormIndexTemp);
                                totalVerts++;    //We created a new vertex
                                indices.push_back(totalVerts - 1);    //Set index for this vertex
                            }

                            //If this is the very first vertex in the face, we need to
                            //make sure the rest of the triangles use this vertex
                            if (i == 0)
                            {
                                firstVIndex = indices[vIndex];    //The first vertex index of this FACE

                            }

                            //If this was the last vertex in the first triangle, we will make sure
                            //the next triangle uses this one (eg. tri1(1,2,3) tri2(1,3,4) tri3(1,4,5))
                            if (i == 2)
                            {
                                lastVIndex = indices[vIndex];    //The last vertex index of this TRIANGLE
                            }
                            vIndex++;    //Increment index count
                        }

                        meshTriangles++;    //One triangle down

                        //If there are more than three vertices in the face definition, we need to make sure
                        //we convert the face to triangles. We created our first triangle above, now we will
                        //create a new triangle for every new vertex in the face, using the very first vertex
                        //of the face, and the last vertex from the triangle before the current triangle
                        for (int l = 0; l < triangleCount - 1; ++l)    //Loop through the next vertices to create new triangles
                        {
                            //First vertex of this triangle (the very first vertex of the face too)
                            indices.push_back(firstVIndex);            //Set index for this vertex
                            vIndex++;

                            //Second Vertex of this triangle (the last vertex used in the tri before this one)
                            indices.push_back(lastVIndex);            //Set index for this vertex
                            vIndex++;

                            //Get the third vertex for this triangle
                            ss >> VertDef;

                            std::wstring vertPart;
                            int whichPart = 0;

                            //Parse this string (same as above)
                            for (int j = 0; j < VertDef.length(); ++j)
                            {
                                if (VertDef[j] != '/')
                                    vertPart += VertDef[j];
                                if (VertDef[j] == '/' || j == VertDef.length() - 1)
                                {
                                    std::wistringstream wstringToInt(vertPart);

                                    if (whichPart == 0)
                                    {
                                        wstringToInt >> vertPosIndexTemp;
                                        vertPosIndexTemp -= 1;

                                        //Check to see if the vert pos was the only thing specified
                                        if (j == VertDef.length() - 1)
                                        {
                                            vertTCIndexTemp = 0;
                                            vertNormIndexTemp = 0;
                                        }
                                    }
                                    else if (whichPart == 1)
                                    {
                                        if (vertPart != L"")
                                        {
                                            wstringToInt >> vertTCIndexTemp;
                                            vertTCIndexTemp -= 1;
                                        }
                                        else
                                            vertTCIndexTemp = 0;
                                        if (j == VertDef.length() - 1)
                                            vertNormIndexTemp = 0;

                                    }
                                    else if (whichPart == 2)
                                    {
                                        std::wistringstream wstringToInt(vertPart);

                                        wstringToInt >> vertNormIndexTemp;
                                        vertNormIndexTemp -= 1;
                                    }

                                    vertPart = L"";
                                    whichPart++;
                                }
                            }

                            //Check for duplicate vertices
                            bool vertAlreadyExists = false;
                            if (totalVerts >= 3)    //Make sure we at least have one triangle to check
                            {
                                for (int iCheck = 0; iCheck < totalVerts; ++iCheck)
                                {
                                    if (vertPosIndexTemp == vertPosIndex[iCheck] && !vertAlreadyExists)
                                    {
                                        if (vertTCIndexTemp == vertTCIndex[iCheck])
                                        {
                                            indices.push_back(iCheck);            //Set index for this vertex
                                            vertAlreadyExists = true;        //If we've made it here, the vertex already exists
                                        }
                                    }
                                }
                            }

                            if (!vertAlreadyExists)
                            {
                                vertPosIndex.push_back(vertPosIndexTemp);
                                vertTCIndex.push_back(vertTCIndexTemp);
                                vertNormIndex.push_back(vertNormIndexTemp);
                                totalVerts++;                    //New vertex created, add to total verts
                                indices.push_back(totalVerts - 1);        //Set index for this vertex
                            }

                            //Set the second vertex for the next triangle to the last vertex we got        
                            lastVIndex = indices[vIndex];    //The last vertex index of this TRIANGLE

                            meshTriangles++;    //New triangle defined
                            vIndex++;
                        }
                    }
                }
                break;

            case 'm':    //mtllib - material library filename
                checkChar = fileIn.get();
                if (checkChar == 't')
                {
                    checkChar = fileIn.get();
                    if (checkChar == 'l')
                    {
                        checkChar = fileIn.get();
                        if (checkChar == 'l')
                        {
                            checkChar = fileIn.get();
                            if (checkChar == 'i')
                            {
                                checkChar = fileIn.get();
                                if (checkChar == 'b')
                                {
                                    checkChar = fileIn.get();
                                    if (checkChar == ' ')
                                    {
                                        //Store the material libraries file name
                                        fileIn >> meshMatLib;
                                    }
                                }
                            }
                        }
                    }
                }

                break;

            case 'u':    //usemtl - which material to use
                checkChar = fileIn.get();
                if (checkChar == 's')
                {
                    checkChar = fileIn.get();
                    if (checkChar == 'e')
                    {
                        checkChar = fileIn.get();
                        if (checkChar == 'm')
                        {
                            checkChar = fileIn.get();
                            if (checkChar == 't')
                            {
                                checkChar = fileIn.get();
                                if (checkChar == 'l')
                                {
                                    checkChar = fileIn.get();
                                    if (checkChar == ' ')
                                    {
                                        meshMaterialsTemp = L"";    //Make sure this is cleared

                                        fileIn >> meshMaterialsTemp; //Get next type (string)

                                        meshMaterials.push_back(meshMaterialsTemp);
                                    }
                                }
                            }
                        }
                    }
                }
                break;

            default:
                break;
            }
        }
    }
    else    //If we could not open the file
    {
        //SwapChain->SetFullscreenState(false, NULL);    //Make sure we are out of fullscreen

        //create message
        std::string message = "Could not open: ";
        std::cout << message;

        return false;
    }

    subsetIndexStart.push_back(vIndex); //There won't be another index start after our last subset, so set it here

    //sometimes "g" is defined at the very top of the file, then again before the first group of faces.
    //This makes sure the first subset does not conatain "0" indices.
    if (subsetIndexStart[1] == 0)
    {
        subsetIndexStart.erase(subsetIndexStart.begin() + 1);
        meshSubsets--;
    }

    //Make sure we have a default for the tex coord and normal
    //if one or both are not specified
    if (!hasNorm)
        out_normals.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    if (!hasTexCoord)
        out_uvs.push_back(glm::vec2(0.0f, 0.0f));

    //Close the obj file, and open the mtl file
    fileIn.close();
    fileIn.open(meshMatLib.c_str());

    std::wstring lastStringRead;
    int matCount = material.size();    //total materials

    //kdset - If our diffuse color was not set, we can use the ambient color (which is usually the same)
    //If the diffuse color WAS set, then we don't need to set our diffuse color to ambient
    bool kdset = false;

    if (fileIn)
    {
        while (fileIn)
        {
            checkChar = fileIn.get();    //Get next char

            switch (checkChar)
            {
                //Check for comment
            case '#':
                checkChar = fileIn.get();
                while (checkChar != '\n')
                    checkChar = fileIn.get();
                break;

                //Set diffuse color
            case 'K':
                checkChar = fileIn.get();
                if (checkChar == 'd')    //Diffuse Color
                {
                    checkChar = fileIn.get();    //remove space

                    fileIn >> material[matCount - 1].difColor.x;
                    fileIn >> material[matCount - 1].difColor.y;
                    fileIn >> material[matCount - 1].difColor.z;

                    kdset = true;
                }

                //Ambient Color (We'll store it in diffuse if there isn't a diffuse already)
                if (checkChar == 'a')
                {
                    checkChar = fileIn.get();    //remove space
                    if (!kdset)
                    {
                        fileIn >> material[matCount - 1].difColor.x;
                        fileIn >> material[matCount - 1].difColor.y;
                        fileIn >> material[matCount - 1].difColor.z;
                    }
                }
                break;

                //Check for transparency
            case 'T':
                checkChar = fileIn.get();
                if (checkChar == 'r')
                {
                    checkChar = fileIn.get();    //remove space
                    float Transparency;
                    fileIn >> Transparency;

                    material[matCount - 1].difColor.w = Transparency;

                    if (Transparency > 0.0f)
                        material[matCount - 1].transparent = true;
                }
                break;

                //Some obj files specify d for transparency
            case 'd':
                checkChar = fileIn.get();
                if (checkChar == ' ')
                {
                    float Transparency;
                    fileIn >> Transparency;

                    //'d' - 0 being most transparent, and 1 being opaque, opposite of Tr
                    Transparency = 1.0f - Transparency;

                    material[matCount - 1].difColor.w = Transparency;

                    if (Transparency > 0.0f)
                        material[matCount - 1].transparent = true;
                }
                break;

                //Get the diffuse map (texture)
            case 'm':
                checkChar = fileIn.get();
                if (checkChar == 'a')
                {
                    checkChar = fileIn.get();
                    if (checkChar == 'p')
                    {
                        checkChar = fileIn.get();
                        if (checkChar == '_')
                        {
                            //map_Kd - Diffuse map
                            checkChar = fileIn.get();
                            if (checkChar == 'K')
                            {
                                checkChar = fileIn.get();
                                if (checkChar == 'd')
                                {
                                    std::wstring fileNamePath;

                                    fileIn.get();    //Remove whitespace between map_Kd and file

                                    //Get the file path - We read the pathname char by char since
                                    //pathnames can sometimes contain spaces, so we will read until
                                    //we find the file extension
                                    bool texFilePathEnd = false;
                                    while (!texFilePathEnd)
                                    {
                                        checkChar = fileIn.get();

                                        fileNamePath += checkChar;

                                        if (checkChar == '.')
                                        {
                                            for (int i = 0; i < 3; ++i)
                                                fileNamePath += fileIn.get();

                                            texFilePathEnd = true;
                                        }
                                    }

                                    //check if this texture has already been loaded
                                    bool alreadyLoaded = false;
                                    for (int i = 0; i < textureNameArray.size(); ++i)
                                    {
                                        if (fileNamePath == textureNameArray[i])
                                        {
                                            alreadyLoaded = true;
                                            material[matCount - 1].texArrayIndex = i;
                                            material[matCount - 1].hasTexture = true;
                                        }
                                    }

                                    //if the texture is not already loaded, load it now
                                    if (!alreadyLoaded)
                                    {
                                        GLuint tempMeshSRV = loadAnyFile((char*)fileNamePath.c_str());

                                        if (tempMeshSRV)
                                        {
                                            textureNameArray.push_back(fileNamePath.c_str());
                                            material[matCount - 1].texArrayIndex = meshSRV.size();
                                            meshSRV.push_back(tempMeshSRV);
                                            material[matCount - 1].hasTexture = true;
                                        }
                                    }
                                }
                            }
                            //map_d - alpha map
                            else if (checkChar == 'd')
                            {
                                //Alpha maps are usually the same as the diffuse map
                                //So we will assume that for now by only enabling
                                //transparency for this material, as we will already
                                //be using the alpha channel in the diffuse map
                                material[matCount - 1].transparent = true;
                            }
                        }
                    }
                }
                break;

            case 'n':    //newmtl - Declare new material
                checkChar = fileIn.get();
                if (checkChar == 'e')
                {
                    checkChar = fileIn.get();
                    if (checkChar == 'w')
                    {
                        checkChar = fileIn.get();
                        if (checkChar == 'm')
                        {
                            checkChar = fileIn.get();
                            if (checkChar == 't')
                            {
                                checkChar = fileIn.get();
                                if (checkChar == 'l')
                                {
                                    checkChar = fileIn.get();
                                    if (checkChar == ' ')
                                    {
                                        //New material, set its defaults
                                        SurfaceMaterial tempMat;
                                        material.push_back(tempMat);
                                        fileIn >> material[matCount].matName;
                                        material[matCount].transparent = false;
                                        material[matCount].hasTexture = false;
                                        material[matCount].texArrayIndex = 0;
                                        matCount++;
                                        kdset = false;
                                    }
                                }
                            }
                        }
                    }
                }
                break;

            default:
                break;
            }
        }
    }
    else
    {
        std::wstring message = L"Could not open MTL: ";
        message += meshMatLib;

        return false;
    }

    //Set the subsets material to the index value
    //of the its material in our material array
    for (int i = 0; i < meshSubsets; ++i)
    {
        bool hasMat = false;
        for (int j = 0; j < material.size(); ++j)
        {
            if (meshMaterials[i] == material[j].matName)
            {
                subsetMaterialArray.push_back(j);
                hasMat = true;
            }
        }
        if (!hasMat)
            subsetMaterialArray.push_back(0); //Use first material in array
    }
   
    return true;
}



#ifdef USE_ASSIMP // don't use this #define, it's only for me (it AssImp fails to compile on your machine, at least all the other tutorials still work)

// Include AssImp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

bool loadAssImp(
	const char * path, 
	std::vector<unsigned short> & indices,
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals
){

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 0/*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
	if( !scene) {
		fprintf( stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

	// Fill vertices texture coordinates
	uvs.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		uvs.push_back(glm::vec2(UVW.x, UVW.y));
	}

	// Fill vertices normals
	normals.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(glm::vec3(n.x, n.y, n.z));
	}


	// Fill face indices
	indices.reserve(3*mesh->mNumFaces);
	for (unsigned int i=0; i<mesh->mNumFaces; i++){
		// Assume the model has only triangles.
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
	
	// The "scene" pointer will be deleted automatically by "importer"
	return true;
}

#endif