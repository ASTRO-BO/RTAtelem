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
    	t = clock() - t;
  		printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
        cout << "END" << endl;
        return 0;

    }
    catch(PacketExceptionIO* e)
    {
        cout << e->geterror();
    }
    catch(PacketException* e)
    {
        cout << e->geterror();
    }
}
