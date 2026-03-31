/*
**  ClanLib SDK
**  Copyright (c) 1997-2020 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Mark Page
*/

#include "precomp.h"
#include "program.h"
#include "particle.h"
#include "Demos/simple.h"
#include "Demos/circle.h"
#include "Demos/circle2.h"
#include "Demos/cmotion.h"
#include "Demos/explosion.h"
#include "Demos/msmall.h"
#include "Demos/shooting.h"
#include "Demos/usercollision.h"

#define ENABLE_VULKAN
//#define ENABLE_D3D
//#define ENABLE_OPENGL

clan::ApplicationInstance<Program> clanapp;

DemoState Program::state = DemoState::menu;

Program::Program()
{
#if defined(ENABLE_D3D)
	clan::D3DTarget::set_current();
#elif defined(ENABLE_OPENGL)
	clan::OpenGLTarget::set_current();
#else
	clan::VulkanContextDescription vk_desc;
#ifdef _DEBUG
	logger = std::make_unique<clan::ConsoleLogger>();
	clan::log_event("Testing", "Logging");
	vk_desc.set_debug(true);
#endif
	clan::VulkanTarget::set_current(vk_desc);
#endif


	window = clan::DisplayWindow("LinearParticle Example", 640, 480, false);

}

bool Program::update()
{
	DemoState current_state = state;
	if (!demo)
	{
		switch (current_state)
		{
		case DemoState::menu:
			demo = std::make_unique<Particle>(window);
			break;
		case DemoState::simple:
			demo = std::make_unique<DemoSimple>(window);
			break;
		case DemoState::circle:
			demo = std::make_unique<DemoCircle>(window);
			break;
		case DemoState::circle2:
			demo = std::make_unique<DemoCircle2>(window);
			break;
		case DemoState::msmall:
			demo = std::make_unique<DemoMSmall>(window);
			break;
		case DemoState::shooting:
			demo = std::make_unique<DemoShooting>(window);
			break;
		case DemoState::explosion:
			demo = std::make_unique<DemoExplosion>(window);
			break;
		case DemoState::cmotion:
			demo = std::make_unique<DemoCMotion>(window);
			break;
		case DemoState::usercollision:
			demo = std::make_unique<DemoUserCollision>(window);
			break;
		default:
			throw clan::Exception("Invalid State");
		}

	}

	bool result = demo->update();
	if (result == false)
	{
		if (current_state == DemoState::menu)	// Main menu quit
			return false;
		state = DemoState::menu;	// Return to main menu
	}

	if (current_state != state)
		demo.reset();

	return true;
}
