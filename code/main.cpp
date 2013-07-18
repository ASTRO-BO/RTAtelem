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
#include "CTATriggeredEvent.h"
using namespace std;
using namespace PacketLib;

#include <time.h> 

int main(int argc, char *argv[])
{
    try
    {
    	clock_t t;
    	RTATelem::CTATriggeredEvent * trev = new RTATelem::CTATriggeredEvent("conf/rta.stream", "", "out.raw");
    	
    	trev->setMetadata(1, 2, 3);
    	trev->setNumberOfTelescopes(1);
    	
    	word telescopeIndex = 0;
    	
    	trev->setTelescopeId(telescopeIndex, 10);
    	    	
    	word npixels = 30;
    	word nsamples = 5;
    	trev->setNumberOfPixels(telescopeIndex, npixels);
    	
    	for(int i=0; i<npixels; i++) {
    		trev->setNumerOfSamples(telescopeIndex, i, nsamples);
    		trev->setPixelId(telescopeIndex, i, i);
    	}

    	for(int i=0; i<npixels; i++)
    		for(int j=0; j<nsamples; j++)
    			trev->setSampleValue(0, i, j, 3);
    	
    	trev->printPacket_output();
    		
    	trev->writePacket();
    	
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
