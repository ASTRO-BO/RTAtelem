/***************************************************************************
                          main.cpp  -  description
                             -------------------
    copyright            : (C) 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
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
#include "CTAPedestalHigh.h"
using namespace std;
using namespace PacketLib;

#include <time.h> 

/// Reading the Packet
/// If used, remove the R from mainR
int mainR(int argc, char *argv[])
{
    try
    {

    	clock_t t;

    	/// The Packet containing the FADC value of each triggered telescope 
        RTATelem::CTATriggeredTelescope * trtel = new RTATelem::CTATriggeredTelescope("conf/rta_fadc.stream", "out_fadc.raw", "");

        /// The Packet containing the pedestal high values for each telescope 
    	RTATelem::CTAPedestalHigh * pedhigh = new RTATelem::CTAPedestalHigh("conf/rta_ped_high.stream", "out_pedhigh.raw", "");
    	
    	byte* b_trtel = trtel->readPacket();
    	while(b_trtel != 0) {
    		if(b_trtel) {
    			trtel->printPacket_input();
    			cout << "--" << endl;
                        byte arrayID;
    			word runNumberID;
    			dword eventNumberID;
    			trtel->getMetadata(arrayID, runNumberID, eventNumberID);
    			cout << "ssc: " << trtel->getSSC() << endl;
    			cout << "metadata " << arrayID << " " << runNumberID << " " << eventNumberID << endl;
    			cout << "Telescope Time " << trtel->getTelescopeTime() << endl;
    			cout << "triggered telescopes: " << trtel->getNumberOfTriggeredTelescopes() << endl;
    			cout << "IndexOfCurrentTriggeredTelescopes " << trtel->getIndexOfCurrentTriggeredTelescopes() << endl;
    			cout << "TelescopeId " << trtel->getTelescopeId() << endl;
    			cout << "NumberOfPixels " << trtel->getNumberOfPixels() << endl;
    			cout << "PixelId " << trtel->getPixelId(0) << endl;
    			//cout << "NumberOfSamples " << trtel->getNumberOfSamples(0) << endl;
    			cout << "SampleValue " << trtel->getSampleValue(0, 0) << endl;
    		}
    		b_trtel = trtel->readPacket();
    		
    	}
						
    	byte* b_pedhigh = pedhigh->readPacket();
    	while(b_pedhigh != 0) {
    		if(b_pedhigh) {
    			pedhigh->printPacket_input();
    			cout << "--" << endl;
                        byte arrayID;
    			pedhigh->getMetadata(arrayID);
    			cout << "ssc: " << pedhigh->getSSC() << endl;
    			cout << "metadata " << arrayID << endl;
    			cout << "Number of telescopes: " << pedhigh->getNumberOfTelescopes() << endl;
    			cout << "IndexOfCurrentTelescope " << pedhigh->getIndexOfCurrentTelescopes() << endl;
    			cout << "TelescopeId " << pedhigh->getTelescopeId() << endl;
    			cout << "NumberOfPixels " << pedhigh->getNumberOfPixels() << endl;
    			cout << "PixelId " << pedhigh->getPixelId(0) << endl;
    			cout << "Pedestal High Value " << pedhigh->getPedestalHighValue(0) << endl;
    		}
    		b_pedhigh = pedhigh->readPacket();
    		
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

/// Writing the Packet
/// If used, remove the W from mainW
int main(int argc, char *argv[])
{
    try
    {
    	clock_t t;

    	/// The Packet containing the FADC value of each triggered telescope 
    	RTATelem::CTATriggeredTelescope * trtel = new RTATelem::CTATriggeredTelescope("conf/rta_fadc.stream", "", "out_fadc.raw");

    	/// The Packet containing the pedestal high values for each telescope 
    	RTATelem::CTAPedestalHigh * pedhigh = new RTATelem::CTAPedestalHigh("conf/rta_ped_high.stream", "", "out_pedhigh.raw");

    	/// The attribute stores the event number
    	int evnum=10;
    	/// The attribute stores the trigger time
    	long trig_time=100;
    	
    	/// The attribute stores the number of triggered telescopes
    	int numberOfTriggeredTelescopes = 1;
		for(int telindex = 0; telindex<numberOfTriggeredTelescopes; telindex++) {
	
			trtel->setSSC(0);
			trtel->setMetadata(1, 2, evnum);
	
			trtel->setTelescopeTime(1500);
	
			trtel->setNumberOfTriggeredTelescopes(numberOfTriggeredTelescopes);
			trtel->setIndexOfCurrentTriggeredTelescopes(telindex);
			trtel->setTelescopeId(telindex*10+5);
	
	    	/// The attribute stores the number of pixels
			word npixels = 1141;
	    	/// The attribute stores the number of samples
			word nsamples = 40;
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
	
    	/// The attribute stores the total number of telescopes
		int numberOfTelescopes = 62;
		for(int telindex = 0; telindex<numberOfTelescopes; telindex++) {
	
			pedhigh->setSSC(0);
			pedhigh->setMetadata(1);
	
			pedhigh->setNumberOfTelescopes(numberOfTelescopes);
			pedhigh->setIndexOfCurrentTelescopes(telindex);
			pedhigh->setTelescopeId(telindex*10+5);
	
	    	/// The attribute stores the total number of pixels
			word npixels = 1141;

			pedhigh->setNumberOfPixels(npixels);
	
			for(int pixelindex=0; pixelindex<npixels; pixelindex++) {
				pedhigh->setPixelId(pixelindex, pixelindex);
                                pedhigh->setPedestalHighValue(pixelindex, 2);
			}
		
			pedhigh->writePacket();
			
			pedhigh->printPacket_output();
		
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
