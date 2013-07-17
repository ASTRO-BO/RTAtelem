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
using namespace std;
using namespace PacketLib;

int main(int argc, char *argv[])
{
    try
    {
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
