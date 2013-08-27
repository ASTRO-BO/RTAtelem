/***************************************************************************
 CTACamera.h  -  description
 -------------------
 copyright            : (C) 2013 Andrea Bulgarelli
 email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
#ifndef _CTACAMERA_H
#define _CTACAMERA_H

#include "CTAPacket.h"

namespace RTATelem {

class CTACamera: public RTATelem::CTAPacket {

public:
	CTACamera(string packetConfig, string tmInputFileName = "",
			string tmOutputFileName = "");

	/// It gets the number of pixels
	word getNumberOfPixels();

	/// It sets the number of pixels
	/// \param number The number of pixels
	void setNumberOfPixels(word number);
};

}

#endif
