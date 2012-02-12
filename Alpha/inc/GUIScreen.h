#ifndef GUISCREEN_H
#define GUISCREEN_H

#include <string>

namespace Kaotic_Alpha
{
	class GUIScreen
	{
	public:
		virtual void Update(){}
		virtual void Render(){}

		GUIScreen(std::string name)
		{
			m_Name = name;
		}
		virtual ~GUIScreen(){}

		std::string m_Name;

	private:

	};
}

#endif