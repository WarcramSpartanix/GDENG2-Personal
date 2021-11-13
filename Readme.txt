Warren L. Luceñara

Instructions
- unpack zip file.
- open the project2.vcxproj through visual studio 2019.

# Important:
	- Project1 folder is an old file, use Project2 Folder
	- The default branch to be downloaded is "SceneEditor" branch. The "main" branch is deprecated.
	- The main function is located in main.cpp
# Instructions:
	- Open the DirectXGame.vcxproj or DirectXGame.sln
	- Set the C++ Standard language to ISO C++ 17 Standard
	- Make sure the following project properties have the respective values
		- VC++ Directories -> Include Directories : "extra\DirectXTex\include;extra\tinyobjloader\include;"
		- VC++ Directories -> Library Directories : "extra\DirectXTex\bin;extra\ReactPhysics3D;"
		- C/C++ -> General -> Additional Include Directories : "extra\ReactPhysics3D\include;"
		- C/C++ -> Preprocessor -> Preprocessor Definitions : "NOMINMAX;_CRT_SECURE_NO_WARNINGS;_DEBUG;_CONSOLE;"
		- Linker -> Input -> Additional Dependencies : "d3d11.lib;d3dcompiler.lib;DirectXTexD.lib;reactphysics3d.lib;"
	- Compile the code through Local Windows Debugger

# Comments:
	- Not sure what the Unreal and Unity dependencies mean so I passed my Unity scripts and scene.
	- For Unreal, I added my c++ script and the Blueprints. The FileLoaderButtons is the editor utility widget
