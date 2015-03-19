﻿
#ifndef __FBXOPENCPP_COMMON_H
#define __FBXOPENCPP_COMMON_H

#include <iostream>
#include <fbxsdk.h>
#include <vector>
#include <string>
#include <sstream>

void PrintObject(FbxObject* obj, const char* prefix="");

void PrintScene(FbxScene* obj, const char* prefix="");

void PrintAnimLayer(FbxAnimLayer* animLayer, const char* prefix="");
void PrintAnimStack(FbxAnimStack* animStack, const char* prefix="");
void PrintAnimCurve(FbxAnimCurve* animCurve, const char* prefix="");
void PrintAnimCurveNode(FbxAnimCurveNode* animCurveNode, const char* prefix="");
void PrintDeformer(FbxDeformer* deformer, const char* prefix="");
void PrintNode(FbxNode* node, const char* prefix="");
void PrintNodeAttribute(FbxNodeAttribute* nodeAttribute, const char* prefix="");
void PrintCamera(FbxCamera* camera, const char* prefix="");
void PrintLight(FbxLight* light, const char* prefix="");
void PrintLayerContainer(FbxLayerContainer* layerContainer, const char* prefix="");
void PrintLayer(FbxLayer* layer, const char* prefix="");
void PrintGeometryBase(FbxGeometryBase* geometryBase, const char* prefix="");
void PrintGeometry(FbxGeometry* geometry, const char* prefix="");
void PrintMesh(FbxMesh* mesh, const char* prefix="");
void PrintNull(FbxNull* null, const char* prefix="");
void PrintSkeleton(FbxSkeleton* skeleton, const char* prefix="");
void PrintPose(FbxPose* pose, const char* prefix="");
void PrintSubDeformer(FbxSubDeformer* subDeformer, const char* prefix="");
void PrintSurfaceMaterial(FbxSurfaceMaterial* surfaceMaterial, const char* prefix="");
void PrintSurfaceLambert(FbxSurfaceLambert* surfaceLambert, const char* prefix="");
void PrintSurfacePhong(FbxSurfacePhong* surfacePhong, const char* prefix="");
void PrintTexture(FbxTexture* texture, const char* prefix="");
void PrintVideo(FbxVideo* video, const char* prefix="");

void PrintProperty(FbxProperty* prop, const char* prefix="");

int CountProperties(FbxObject* obj);

std::ostream& operator<<(std::ostream& os, const FbxDouble2& value);
std::ostream& operator<<(std::ostream& os, const FbxDouble3& value);
std::ostream& operator<<(std::ostream& os, const FbxDouble4& value);

FbxScene* Load(const char* filename, FbxManager* manager=NULL);

// unit tests

void RunTests();

typedef void (*TestFunction)();

class TestFixture;

struct TestCase
{
    TestCase(const char* name, TestFunction function, TestFixture* parentFixture)
        : Name(name), Function(function), ParentFixture(parentFixture)
    {
    }

    const char* Name;
    TestFunction Function;
    TestFixture* ParentFixture;
};

class TestFixture
{
public:
    TestFixture(const char* name);

    virtual void RegisterTestCases();

    virtual void SetupFixture();
    virtual void Setup();
    virtual void TearDown();
    virtual void TearDownFixture();

    const char* Name;

    std::vector<TestCase> TestCases;
};


void _AssertEqual(int expected, int actual, const char* filename, int line);
void _AssertEqual(void* expected, void* actual, const char* filename, int line);
void _AssertEqual(FbxVector4 expected, FbxVector4 actual, const char* filename, int line);
void _AssertNotEqual(void* expected, void* actual, const char* filename, int line);
void _AssertNull(void* actual, const char* filename, int line);
void _AssertNotNull(void* actual, const char* filename, int line);
void _AssertTrue(bool condition, const char* filename, int line);

#define AssertEqual(expected, actual) _AssertEqual((expected), (actual), __FILE__, __LINE__)
#define AssertNotEqual(expected, actual) _AssertNotEqual((expected), (actual), __FILE__, __LINE__)
#define AssertNull(actual) _AssertNull((actual), __FILE__, __LINE__)
#define AssertNotNull(actual) _AssertNotNull((actual), __FILE__, __LINE__)
#define AssertTrue(condition) _AssertTrue((condition), __FILE__, __LINE__)

#define AddTestCase(name) TestCases.push_back(TestCase(#name, &name, this))

#define TestClass(name) class name : public virtual TestFixture {\
    public: name() : TestFixture(#name) { RegisterTestCases(); }\
    virtual void RegisterTestCases(); };

TestClass(NodeTest);
TestClass(SceneTest);
TestClass(LayerContainerTest);
TestClass(GeometryBaseTest);
TestClass(GeometryTest);
TestClass(MeshTest);
TestClass(FbxObjectTest);
TestClass(SurfacePhongTest);

#endif // __FBXOPENCPP_COMMON_H
