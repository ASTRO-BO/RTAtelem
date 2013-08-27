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
#include "CTAPedestal.h"
#include "CTAPacket.h"

using namespace std;
using namespace PacketLib;

#include <time.h>

/// Reading the Packet
/// If used, remove the R from mainR
int main(int argc, char *argv[])
{
    try
    {

        clock_t t;

        /// The Packet containing the FADC value of each triggered telescope
        RTATelem::CTATriggeredTelescope * trtel = new RTATelem::CTATriggeredTelescope("conf/rta_fadc.stream", "out_fadc.raw", "");


        /// The Packet containing the pedestal high values for each telescope
        RTATelem::CTAPedestal * pedestal = new RTATelem::CTAPedestal("conf/rta_ped.stream", "out_pedestal.raw", "");

        byte* b_trtel = trtel->readPacket();

        while(b_trtel != 0) {
            if(b_trtel) {
                trtel->printPacket_input();
                cout << "--" << endl;
                word arrayID;
                word runNumberID;

                trtel->header->getMetadata(arrayID, runNumberID);
                cout << "APID: " << trtel->header->getAPID() << endl;
                cout << "ssc: " << trtel->header->getSSC() << endl;
                cout << "metadata " << arrayID << " " << runNumberID << " " << endl;
                cout << "eventNumber:" << trtel->getEventNumber() << endl;
                cout << "Telescope Time " << trtel->header->getTime() << endl;
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

        cout << "decode pedestal packet" << endl;

        byte* b_pedestal = pedestal->readPacket();
        while(b_pedestal != 0) {
            if(b_pedestal) {
                pedestal->printPacket_input();
                cout << "--" << endl;
                word arrayID;
                word runNumber;
                pedestal->header->getMetadata(arrayID, runNumber);
                cout << "APID: " << trtel->header->getAPID() << endl;
                cout << "ssc: " << pedestal->header->getSSC() << endl;
                cout << "metadata " << arrayID << endl;
                cout << "TelescopeId " << pedestal->getTelescopeId() << endl;
                cout << "channel " << pedestal->getChannel() << endl;
                cout << "pedestal run " << pedestal->getPedestalRun() << endl;
                cout << "NumberOfPixels " << pedestal->getNumberOfPixels() << endl;
                cout << "PixelId " << pedestal->getPixelId(0) << endl;
                cout << "Pedestal High Value " << pedestal->getPedestalValue(0) << endl;
            }
            b_pedestal = pedestal->readPacket();

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
int mainW(int argc, char *argv[])
{
    try
    {
        clock_t t;
		 
        /// The Packet containing the FADC value of each triggered telescope
        RTATelem::CTATriggeredTelescope * trtel = new RTATelem::CTATriggeredTelescope("conf/rta_fadc.stream", "", "out_fadc.raw");
        //RTATelem::CTATriggeredTelescope * trtel = new RTATelem::CTATriggeredTelescope("conf_ASTRI_S21/STRUCT.stream", "out_fadc.raw", "");
        /// The Packet containing the pedestal high values for each telescope
       	RTATelem::CTAPedestal * pedestal = new RTATelem::CTAPedestal("conf/rta_ped.stream", "", "out_pedestal.raw");

		

        /// The attribute stores the event number
        int evnum=10;
        /// The attribute stores the trigger time
        long trig_time=100;

        /// The attribute stores the number of triggered telescopes
        int numberOfTriggeredTelescopes = 1;
        for(int telindex = 0; telindex<numberOfTriggeredTelescopes; telindex++) {

        	trtel->header->setAPID(10);
            trtel->header->setSSC(0);
            trtel->header->setMetadata(1, 2);

            trtel->header->setTime(1500);

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
        int numberOfTelescopes = 1;
        for(int telindex = 0; telindex<numberOfTelescopes; telindex++) {

        	trtel->header->setAPID(11);
            pedestal->header->setSSC(0);
            pedestal->header->setMetadata(1, 2);
            pedestal->setChannel(1);
            pedestal->setPedestalRun(0);
            pedestal->setTelescopeId(telindex*10+5);

            /// The attribute stores the total number of pixels
            word npixels = 1141;

            pedestal->setNumberOfPixels(npixels);

            for(int pixelindex=0; pixelindex<npixels; pixelindex++) {
                pedestal->setPixelId(pixelindex, pixelindex);
                pedestal->setPedestalValue(pixelindex, 2);
            }

            pedestal->writePacket();

            pedestal->printPacket_output();

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
