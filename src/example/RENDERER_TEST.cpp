
#include "graphic/render/RenderSystem.h"
#include "object/camera/PerspectiveCamera.h"
#include "texture/TextureManager.h"
#include "tools/GeometryFactory.h"
#include "light/DirectionLight.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"
#include "utils/MathHelper.h"
#include "object/Object3D.h"
#include "graphic/Win.h"
using namespace SRE;
using namespace Math;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Scene::ptr createScene()
{
	Scene::ptr scene = std::make_shared<Scene>();
    std::string my_file_path = std::string(SRC_PATH);
    std::string floor_path = my_file_path + "/src/assets/texture/floor.jpg";
    std::string box_path = my_file_path + "/src/assets/texture/box.jpg";
    std::string earth_path = my_file_path + "/src/assets/texture/earthmap.jpg";

	//texture
	Texture::ptr earthTex = TextureManager::Inst()->loadTexture("grass",earth_path.c_str());
	Texture::ptr boxTex = TextureManager::Inst()->loadTexture("box", box_path.c_str());
	Texture::ptr floorTex = TextureManager::Inst()->loadTexture("earth", floor_path.c_str());

	TextureUnitState::ptr earthUnit = std::make_shared<TextureUnitState>();
	earthUnit->setTexture(earthTex);
	TextureUnitState::ptr boxUnit = std::make_shared<TextureUnitState>();
	boxUnit->setTexture(boxTex);
	TextureUnitState::ptr floorUnit = std::make_shared<TextureUnitState>();
	floorUnit->setTexture(floorTex);
	//material
	Material::ptr floorMat = std::make_shared<Material>();
	floorMat->setMaterialType(Material::PhongMaterial);
	floorMat->setMap(floorUnit);
	floorMat->setCullFaceMode(CullFaceMode::DoubleSide);

	Material::ptr earthMat = std::make_shared<Material>();
	earthMat->setMap(earthUnit);
	earthMat->setMaterialType(Material::PhongMaterial);
	earthMat->setCullFaceMode(CullFaceMode::DoubleSide);

	Material::ptr boxMat = std::make_shared<Material>();
	boxMat->setMaterialType(Material::PhongMaterial);
	boxMat->setMap(boxUnit);

	//mesh
	RenderObject* floor = GeometryFactory::MakeQuad(100, 100);
	floor->setMaterial(floorMat);

	RenderObject* box1 = GeometryFactory::MakeBox(20.0, 20.0, 20.0);
	box1->setPosition(Vector3D(-25.0, 10.0, 25.0));	
	box1->setMaterial(boxMat);

	RenderObject* box2 = GeometryFactory::MakeBox(10.0, 10.0, 10.0);
	box2->setPosition(Vector3D(0.0, 5.0, -25.0));
	box2->setMaterial(boxMat);

	RenderObject* box3 = GeometryFactory::MakeBox(10.0, 10.0, 10.0);
	box3->setPosition(Vector3D(25.0, 5.0, 25.0));
	box3->setMaterial(boxMat);

	RenderObject* sphere = GeometryFactory::MakeSphere(8.0, 32, 32);
	sphere->setPosition(Vector3D(0.0, 8.0, 0.0));	
	sphere->setMaterial(earthMat);
	
	Object3D::ptr root = std::make_shared<Object3D>();

	//light
	DirectionLight* dlight = new DirectionLight();
	dlight->setPosition(Vector3D(0.0, 50.0, 50.0));
	dlight->setShadowCamera(new OrthographicCamera(-50.0, 50.0, -50.0, 50.0, 0.1, 100.0));

	PointLight* plight = new PointLight();
	plight->setPosition(Vector3D(0.0, 50.0, 0.0));
	plight->setShadowCamera(new PerspectiveCamera(MathHelper::radian(70.0), 1.0, 1.0, 200.0));

	SpotLight* spotlight = new SpotLight;
	spotlight->setPosition(Vector3D(0.0, 30.0, 0.0));
	spotlight->setAngle(M_PI/6.0);
	spotlight->setDecay(1.0);
	spotlight->setDistance(00.0);
	spotlight->setPenumbra(0.05);
	spotlight->setShadowCamera(new PerspectiveCamera(MathHelper::radian(50.0), 1.0, 1.0, 200.0));

	root->add(floor);
	root->add(box1);
	root->add(box2);
	root->add(box3);
	root->add(sphere);

	root->add(dlight);
	root->add(plight);
	root->add(spotlight);

	//TerrainTile* tt = new TerrainTile();
	//Mesh* mesh = tt->createFromRandomHeght(32, 32);
	//Mesh* mesh = tt->createMeshFromHeightmap("../../../src/Data/texture/terrain1.jpg");
	//root->add(mesh);
	//mesh->setMaterial(earthMat);
	scene->setSceneRoot(root);
	scene->setUseShadowMap(true);

	return scene;
}
// Texture::ptr loadSkybox()
// {
// 	std::string path = "../../../src/Data/texture/skybox2/";
// 	std::vector<std::string> skyboxfile = {	path + "right.tga",
// 		path + "left.tga",
// 		path + "top.tga",
// 		path + "bottom.tga",
// 		path + "back.tga",
// 		path + "front.tga"};
// 	Texture::ptr skybox = TextureManager::Inst()->loadCubeMap("skybox", skyboxfile);
// 	return skybox;
// }
// void loadModel(const char* fileName)
// {
// 	Model* model = new Model;
// 	Object * object =  model->loadModel(fileName);
// }
int main()
{
	 Win::getSingleton()->create();	
	 PerspectiveCamera::ptr camera = std::make_shared<PerspectiveCamera>(MathHelper::radian(45.0), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 500.0);
	 camera->setPosition(Vector3D(0.0f, 50.0f, -100.0));
	 camera->lookAt(0.0, 0.0, 0.0);
	
	Scene::ptr scene = createScene();
	//loadModel("../../../src/Data/model/glTF/bjw.gltf");
	//Skybox* skybox = new Skybox;
	//skybox->setTexture(loadSkybox());
	//scene->setSkybox((Skybox::ptr)skybox);
	 RenderSystem *rs = new RenderSystem(scene.get(), camera.get());
	 Win::getSingleton()->loadRenderSystem(rs);
	 Win::getSingleton()->startRenderLoop();

	delete rs;
    return 0;
}