#include "MenuScreen.h"
#include "UIManager.h"
#include "CreditsScreen.h"
#include "ColorPickerScreen.h"
#include "GameObjectManager.h"
#include "Cube.h"
#include "Plane.h"
#include "TexturedCube.h"
#include "MeshObject.h"
#include "RigidCube.h"
#include "RigidPlane.h"
#include "ActionHistory.h"
#include "FileManager.h"
#include "PhysicsComponent.h"

MenuScreen::MenuScreen() : AUIScreen(ScreenNames::MENU_SCREEN)
{
	saveDialog = ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
	saveDialog.SetTitle("Save Path");
	saveDialog.SetTypeFilters({ ".level", ".txt"});

	loadDialog.SetTitle("Load Path");
	loadDialog.SetTypeFilters({ ".level", ".txt"});
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::Undo()
{
	EditorAction* temp = ActionHistory::getInstance()->undoAction();
	if (temp == nullptr)
		return;
	
	AGameObject* obj = GameObjectManager::getInstance()->findObjectByName(temp->m_name);
	if (obj == nullptr)
		return;

	ActionHistory::getInstance()->recordRedo(obj);

	obj->setPosition(temp->m_localPosition);
	obj->setScale(temp->m_localScale);
	obj->setRotation(temp->m_localRotation);
}

void MenuScreen::Redo()
{
	EditorAction* temp = ActionHistory::getInstance()->redoAction();
	if (temp == nullptr)
		return;

	AGameObject* obj = GameObjectManager::getInstance()->findObjectByName(temp->m_name);
	if (obj == nullptr)
		return;

	ActionHistory::getInstance()->recordUndo(obj);

	obj->setPosition(temp->m_localPosition);
	obj->setScale(temp->m_localScale);
	obj->setRotation(temp->m_localRotation);
}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save"))
				{
					saveDialog.Open();
				}
				if (ImGui::MenuItem("Load"))
				{
					loadDialog.Open();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Primitives"))
			{
				if (ImGui::MenuItem("Cube"))
				{
					GameObjectManager::getInstance()->addObject(new Cube("Cube"));
				}
				if (ImGui::MenuItem("Plane"))
				{
					GameObjectManager::getInstance()->addObject(new Plane("Plane"));
				}
				if (ImGui::MenuItem("Sphere"))
				{
					AGameObject* sphere = new MeshObject("Sphere", L"Obj\\sphere.obj", L"textures\\brick.png");
					sphere->setType(PrimitiveType::SPHERE);
					GameObjectManager::getInstance()->addObject(sphere);
				}
				if (ImGui::MenuItem("Capsule"))
				{
					AGameObject* capsule = new MeshObject("Capsule", L"Obj\\Capsule.obj", L"textures\\brick.png");
					capsule->setType(PrimitiveType::CAPSULE);
					GameObjectManager::getInstance()->addObject(capsule);
				}
				if (ImGui::MenuItem("Textured Cube"))
				{
					GameObjectManager::getInstance()->addObject(new TexturedCube("TexturedCube"));
				}
				if (ImGui::MenuItem("RigidCube"))
				{
					GameObjectManager::getInstance()->addObject(new RigidCube("RigidCube"));
				}
				if (ImGui::MenuItem("RigidCubeX50"))
				{
					srand(time(0));
					for (int i = 0; i < 50; i++)
					{
						Vector3D newPos = Vector3D(rand() % 6 - 3, rand() % 3, rand() % 6 - 3);
						Cube* rigidCube = new Cube("RigidCube");
						rigidCube->setPosition(newPos);
						rigidCube->addComponent(new PhysicsComponent("PhysicsComponent" + std::to_string(i), rigidCube));

						GameObjectManager::getInstance()->addObject(rigidCube);
					}
				}
				if (ImGui::MenuItem("RigidPlane"))
				{
					GameObjectManager::getInstance()->addObject(new RigidPlane("RigidPlane"));
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Meshes"))
			{
				if (ImGui::MenuItem("Teapot"))
				{
					GameObjectManager::getInstance()->addObject(new MeshObject("Teapot", L"Obj\\teapot.obj", L"textures\\brick.png"));
				}
				if (ImGui::MenuItem("Bunny"))
				{
					GameObjectManager::getInstance()->addObject(new MeshObject("Bunny", L"Obj\\bunny.obj", nullptr));
				}
				if (ImGui::MenuItem("Armadillo"))
				{
					GameObjectManager::getInstance()->addObject(new MeshObject("Armadillo", L"Obj\\armadillo.obj", nullptr));
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Actions"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z"))
			{
				Undo();
			}
			if (ImGui::MenuItem("Redo", "CTRL+Y"))
			{
				Redo();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("About"))
		{
			if (ImGui::MenuItem("Credits"))
			{
				UIManager::getInstance()->addScreen("CreditsScreen", new CreditsScreen());
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();



		saveDialog.Display();

		if (saveDialog.HasSelected())
		{
			std::cout << "Selected filename" << saveDialog.GetSelected().string() << std::endl;
			FileManager::getInstance()->save(saveDialog.GetSelected().string());

			saveDialog.ClearSelected();
			saveDialog.Close();
		}

		loadDialog.Display();

		if (loadDialog.HasSelected())
		{
			std::cout << "Selected filename" << loadDialog.GetSelected().string() << std::endl;
			FileManager::getInstance()->load(loadDialog.GetSelected().string());

			loadDialog.ClearSelected();
			loadDialog.Close();
		}
		
	}
}
