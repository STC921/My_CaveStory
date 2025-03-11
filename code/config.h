#ifndef CONFIG_H
#define CONFIG_H

namespace config{
	enum GraphicsQuality{
		HIGH_QUALITY,
		ORIGINAL_QUALITY,
	};

	GraphicsQuality getGraphicsQuality();
}

#endif