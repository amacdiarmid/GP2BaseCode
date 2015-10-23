#ifndef FBXLoader_H
#define FBXLoader_H

#include "Common.h"
#include "Mesh.h"
#include "Vertex.h"
#include <fbxsdk.h>

bool loadFBXFromFile(const string& filename, MeshData *MeshData);

void processNode(FbxNode *node, MeshData *meshData);
void processAttribute(FbxNodeAttribute *attribute, MeshData *meshDate);
void processMesh(FbxMesh *mesh, MeshData *meshData);
void processMeshTextureCoords(FbxMesh *mesh, Vertex *verts, int numVerts);

#endif