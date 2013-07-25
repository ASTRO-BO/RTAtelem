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

//mainR
int main(int argc, char *argv[])
{
    try
    {

    	clock_t t;
    	RTATelem::CTATriggeredTelescope * trtel = new RTATelem::CTATriggeredTelescope("conf/rta.stream", "out.raw", "");
    	
    	byte* b = trtel->readPacket();
    	while(b != 0) {
    		if(b) {
    			trtel->printPacket_input();
    			cout << "--" << endl;
    			word arrayID, runNumberID, eventNumberID;
    			trtel->getMetadata(arrayID, runNumberID, eventNumberID);
    			cout << "metadata " << arrayID << " " << runNumberID << " " << eventNumberID << endl;
    			cout << "triggered telescopes: " << trtel->getNumberOfTriggeredTelescopes() << endl;
    			cout << "IndexOfCurrentTriggeredTelescopes " << trtel->getIndexOfCurrentTriggeredTelescopes() << endl;
    			cout << "TelescopeId " << trtel->getTelescopeId() << endl;
    			cout << "NumberOfPixels " << trtel->getNumberOfPixels() << endl;
    			cout << "PixelId " << trtel->getPixelId(0) << endl;
    			cout << "NumberOfSamples " << trtel->getNumberOfSamples(0) << endl;
    			cout << "SampleValue " << trtel->getSampleValue(0, 0) << endl;
    		}
    		b = trtel->readPacket();
    		
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

//mainW
int mainW(int argc, char *argv[])
{
    try
    {
    	clock_t t;
    	RTATelem::CTATriggeredTelescope * trtel = new RTATelem::CTATriggeredTelescope("conf/rta.stream", "", "out.raw");
    	
    	for(int evnum = 0; evnum < 1; evnum++) {
    	
    		int numberOfTriggeredTelescopes = 2;
			for(int telindex = 0; telindex<numberOfTriggeredTelescopes; telindex++) {
		
				trtel->setMetadata(1, 2, evnum);
		
		
				//1
				trtel->setNumberOfTriggeredTelescopes(numberOfTriggeredTelescopes);
				trtel->setIndexOfCurrentTriggeredTelescopes(telindex);
				trtel->setTelescopeId(telindex*10);
		
				//30
				word npixels = 30;
				//5
				word nsamples = 10;
				trtel->setNumberOfPixels(npixels);
		
				for(int pixelindex=0; pixelindex<npixels; pixelindex++) {
					trtel->setPixelId(pixelindex, pixelindex);
					trtel->setNumberOfSamples(pixelindex, nsamples);
					for(int sampleindex=0; sampleindex<nsamples; sampleindex++)
						trtel->setSampleValue(pixelindex, sampleindex, 3);
				}
			
				trtel->writePacket();
				
				trtel->printPacket_output();
			
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
