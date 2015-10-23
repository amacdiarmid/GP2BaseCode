#include "FBXLoader.h"

int level = 0;

void PrintTabs()
{
	for (int i = 0; i < level; i++)
	{
		printf("\t");
	}
}

//return a string based representation based on the attribute type
FbxString GetAttributeTypeName(FbxNodeAttribute::EType type)
{
	switch (type)
	{
	case fbxsdk::FbxNodeAttribute::eUnknown:
		return "unidentified";
		break;
	case fbxsdk::FbxNodeAttribute::eNull:
		return "null";
		break;
	case fbxsdk::FbxNodeAttribute::eMarker:
		return "marker";
		break;
	case fbxsdk::FbxNodeAttribute::eSkeleton:
		return "skeleton";
		break;
	case fbxsdk::FbxNodeAttribute::eMesh:
		return "mesh";
		break;
	case fbxsdk::FbxNodeAttribute::eNurbs:
		return "nurbs";
		break;
	case fbxsdk::FbxNodeAttribute::ePatch:
		return "patch";
		break;
	case fbxsdk::FbxNodeAttribute::eCamera:
		return "camera";
		break;
	case fbxsdk::FbxNodeAttribute::eCameraStereo:
		return "camera stereo";
		break;
	case fbxsdk::FbxNodeAttribute::eCameraSwitcher:
		return "camera switcher";
		break;
	case fbxsdk::FbxNodeAttribute::eLight:
		return "light";
		break;
	case fbxsdk::FbxNodeAttribute::eOpticalReference:
		return "optical reference";
		break;
	case fbxsdk::FbxNodeAttribute::eOpticalMarker:
		return "optical marker";
		break;
	case fbxsdk::FbxNodeAttribute::eNurbsCurve:
		return "nurbs curve";
		break;
	case fbxsdk::FbxNodeAttribute::eTrimNurbsSurface:
		return "trim nurbs surface";
		break;
	case fbxsdk::FbxNodeAttribute::eBoundary:
		return "boundary";
		break;
	case fbxsdk::FbxNodeAttribute::eNurbsSurface:
		return "nurbs surface";
		break;
	case fbxsdk::FbxNodeAttribute::eShape:
		return "shape";
		break;
	case fbxsdk::FbxNodeAttribute::eLODGroup:
		return "lod group";
		break;
	case fbxsdk::FbxNodeAttribute::eSubDiv:
		return "sub div";
		break;
	case fbxsdk::FbxNodeAttribute::eCachedEffect:
		return "cached effect";
		break;
	case fbxsdk::FbxNodeAttribute::eLine:
		return "line";
		break;
	default:
		return "unknown";
		break;
	}
}

bool loadFBXFromFile(const string& filename, MeshData *meshData)
{
	level = 0;
	//initalize the SDKmanager. this handes memory management 
	FbxManager* ISdkManager = FbxManager::Create();

	//create the IO settings object 
	FbxIOSettings* ios = FbxIOSettings::Create(ISdkManager, IOSROOT);
	ISdkManager->SetIOSettings(ios);

	//create an importer using SDK manager
	FbxImporter* iImporter = FbxImporter::Create(ISdkManager, "");

	//call the initalise method	which will load the contents of the FBX file
	if (!iImporter->Initialize(filename.c_str(), -1, ISdkManager->GetIOSettings()))
	{
		return false;
	}

	//create a new scene so that it can be populated by the imported file 
	FbxScene* iScene = FbxScene::Create(ISdkManager, "myScene");
	//import the contents of the file into the scene
	iImporter->Import(iScene);

	//process node 
	FbxNode* iRootNode = iScene->GetRootNode();
	if (iRootNode)
	{
		cout << "root node " << iRootNode->GetName() << endl;
		for (int i = 0; i < iRootNode->GetChildCount(); i++)
		{
			processNode(iRootNode->GetChild(i), meshData);
		}
	}

	iImporter->Destroy();
	return true;
}

void processNode(FbxNode *node, MeshData *meshData)
{
	PrintTabs();
	const char* nodeName = node->GetName();
	FbxDouble3 translation = node->LclTranslation.Get();
	FbxDouble3 rotation = node->LclRotation.Get();
	FbxDouble3 scaling = node->LclScaling.Get();

	cout << "node " << nodeName
		<< " position " << translation[0] << " " << translation[1] << " " << translation[2] << " "
		<< " rotation " << rotation[0] << " " << rotation[1] << " " << rotation[2] << " "
		<< " scale " << scaling[0] << " " << scaling[1] << " " << scaling[2] << endl;

	level++;
	//print the nodes attributes 
	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
	{
		processAttribute(node->GetNodeAttributeByIndex(i), meshData);
	}

	//reclursively print the children 
	for (int i = 0; i < node->GetChildCount(); i++)
	{
		processNode(node->GetChild(i), meshData);
	}

	level--;
	PrintTabs();
}

void processAttribute(FbxNodeAttribute *attribute, MeshData *meshData)
{
	if (!attribute)
	{
		return;
	}
	FbxString typeName = GetAttributeTypeName(attribute->GetAttributeType());
	FbxString arrName = attribute->GetName();
	PrintTabs();
	cout << "attribute " << typeName.Buffer() << " name " << arrName << endl;
	switch (attribute->GetAttributeType())
	{
	case FbxNodeAttribute::eMesh:
		processMesh(attribute->GetNode()->GetMesh(), meshData);
	case FbxNodeAttribute::eCamera:
		return;
	case FbxNodeAttribute::eLight:
		return;
	default:
		break;
	}
}

void processMesh(FbxMesh *mesh, MeshData *meshData)
{
	int numVerts = mesh->GetControlPointsCount();
	int numIndices = mesh->GetPolygonCount();

	Vertex* pVerts = new Vertex[numVerts];
	int *pIndices = mesh->GetPolygonVertices();

	for (int i = 0; i < numVerts; i++)
	{
		FbxVector4 currentVert = mesh->GetControlPointAt(i);
		pVerts[i].position = vec3(currentVert[0], currentVert[1], currentVert[2]);
		pVerts[i].colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		pVerts[i].texCoords = vec2(0.0f, 0.0f);
	}

	processMeshTextureCoords(mesh, pVerts, numVerts);

	for (int i = 0; i < numVerts; i++)
	{
		meshData->vertices.push_back(pVerts[i]);
	}
	for (int i = 0; i < numIndices; i++)
	{
		meshData->indices.push_back(pIndices[i]);
	}
	cout << "vertices " << numVerts << " indices " << numIndices << endl;

	if (pVerts)
	{
		delete[] pVerts;
		pVerts = NULL;
	}
}

void processMeshTextureCoords(FbxMesh *mesh, Vertex *verts, int numVerts)
{
	for (int iPolygon = 0; iPolygon < mesh->GetPolygonCount(); iPolygon++)
	{
		for (unsigned iPolygonVertex = 0; iPolygonVertex < 3; iPolygonVertex++)
		{
			int fbxCornerIndex = mesh->GetPolygonVertex(iPolygon, iPolygonVertex);
			FbxVector2 fbxUV = FbxVector2(0.0, 0.0);
			FbxLayerElementUV* fbxLayerUV = mesh->GetLayer(0)->GetUVs();
			//get texture coords
			if (fbxLayerUV)
			{
				int iUVindex = 0;
				switch (fbxLayerUV->GetMappingMode())
				{
				case FbxLayerElement::eByControlPoint:
					iUVindex = fbxCornerIndex;
					break;
				case FbxLayerElement::eByPolygonVertex:
					iUVindex = mesh->GetTextureUVIndex(iPolygon, iPolygonVertex, FbxLayerElement::eTextureDiffuse);
					break;
				case FbxLayerElement::eByPolygon:
					iUVindex = iPolygon;
					break;
				default:
					break;
				}

				fbxUV = fbxLayerUV->GetDirectArray().GetAt(iUVindex);
				verts[fbxCornerIndex].texCoords.x = fbxUV[0];
				verts[fbxCornerIndex].texCoords.y = 1.0f - fbxUV[1];
			}
		}
	}
}