/*
 *   KONNEX/EIB-Protocol-Stack.
 *
 *  (C) 2007-2010 by Christoph Schueler <chris@konnex-tools.de,
 *                                       cpu12.gems@googlemail.com>
 *
 *   All Rights Reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
*/
#include "knx_disp.h"

PMSG_Buffer MSG_ScratchBuffer;


void KNXDispDispatchLayer(const uint8 LayerID,const KNXLayerServicesType *ServiceTable)
{
    uint8 entry;

    do {
        MSG_ScratchBuffer=MSG_Get(LayerID);

        if (MSG_ScratchBuffer!=(PMSG_Buffer)NULL) {
            entry=MSG_ScratchBuffer->service-ServiceTable->LayerOffset;
            if (entry<ServiceTable->NumServices) {
                /* todo: _ASSERT() Function-Pointer!=NULL !!! */
                ServiceTable->Functions[entry]();
            } else {
                (void)MSG_ReleaseBuffer(MSG_ScratchBuffer);     /* Release invalid Message - todo: Error-Handling!? */
            }
        }
    } while (MSG_ScratchBuffer!=(PMSG_Buffer)NULL);
}
