/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Oct 2004
    copyright            : (C) 2004 by Andrea Bulgarelli
    email                : bulgarelli@bo.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <stdlib.h>
#include "PacketExceptionIO.h"
#include "CTATriggeredTelescope.h"
using namespace std;
using namespace PacketLib;

#include <time.h> 

int mainR(int argc, char *argv[])
{
    try
    {
    	clock_t t;
    	RTATelem::CTATriggeredTelescope * trev = new RTATelem::CTATriggeredTelescope("conf/rta.stream", "out.raw", "");
    	
    	trev->readPacket();
    	trev->printPacket_input();
		
				
    	
    	t = clock() - t;
  		printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
        cout << "END" << endl;
        return 0;

    }
    catch(PacketExceptionIO* e)
    {
        cout << e->geterror() << endl;;
    }
    catch(PacketException* e)
    {
        cout << e->geterror() << endl;
    }
}

//mainW
int main(int argc, char *argv[])
{
    try
    {
    	clock_t t;
    	RTATelem::CTATriggeredTelescope * trev = new RTATelem::CTATriggeredTelescope("conf/rta.stream", "", "out.raw");
    	
    	for(int evnum = 0; evnum < 1; evnum++) {
    	
    		int numberOfTriggeredTelescopes = 2;
			for(int telindex = 0; telindex<numberOfTriggeredTelescopes; telindex++) {
		
				trev->setMetadata(1, 2, evnum);
		
		
				//1
				trev->setNumberOfTriggeredTelescopes(numberOfTriggeredTelescopes);
				trev->setIndexOfCurrentTriggeredTelescopes(telindex);
				trev->setTelescopeId(telindex*10);
		
				//30
				word npixels = 30;
				//5
				word nsamples = 10;
				trev->setNumberOfPixels(npixels);
		
				for(int pixelindex=0; pixelindex<npixels; pixelindex++) {
					trev->setPixelId(pixelindex, pixelindex);
					trev->setNumerOfSamples(pixelindex, nsamples);
					for(int sampleindex=0; sampleindex<nsamples; sampleindex++)
						trev->setSampleValue(pixelindex, sampleindex, 3);
				}
			
				trev->writePacket();
				
				trev->printPacket_output();
			
			}
    	}
    	
    	t = clock() - t;
  		printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
        cout << "END" << endl;
        return 0;

    }
    catch(PacketExceptionIO* e)
    {
        cout << e->geterror() << endl;;
    }
    catch(PacketException* e)
    {
        cout << e->geterror() << endl;
    }
}
