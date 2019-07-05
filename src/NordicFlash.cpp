///////////////////////////////////////////////////////////////////////////////
// BOSSA
//
// Copyright (c) 2015, Arduino LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <exception>

#include "Samba.h"
#include "NordicFlash.h"


/* This class is designed specifically for SAM Dxx architecture in mind */
NordicFlash::NordicFlash(Samba& samba,
                   const std::string& name,
                   uint32_t addr,
                   uint32_t pages,
                   uint32_t size,
                   uint32_t planes,
                   uint32_t lockRegions,
                   uint32_t user,
                   uint32_t stack)
    : Flash(samba, name, addr, pages, size, planes, lockRegions, user, stack)
{
}

NordicFlash::~NordicFlash()
{
}

void
NordicFlash::eraseAll()
{
    // Leave the first 8KB, where bootloader resides, erase the rest.
    // Row is a concept used for convinence. When writing you have to write
    // page(s). When erasing you have to erase row(s).

    if (_samba.isChipEraseAvailable())
    {
        // If extended chip erase is available...

        _samba.chipErase(_addr);
        return;
    }
}

void
NordicFlash::eraseAuto(bool enable)
{
}

bool
NordicFlash::isLocked()
{
    return false;
}

// Returns true if locked, false otherwise.
bool
NordicFlash::getLockRegion(uint32_t region)
{
    return false;
}

// Locks a given region number.
void
NordicFlash::setLockRegion(uint32_t region, bool enable)
{
    throw FlashRegionError();
}


// Read the security bit, returns true if set, false otherwise.
bool
NordicFlash::getSecurity()
{
    return false;
}

// Set's the security bit.
void
NordicFlash::setSecurity()
{
    throw NordicFlashCmdError("Error when setting security bit: not supported");
}

// Enable/disable the Bod. The values are lost on target reset.
void
NordicFlash::setBod(bool enable)
{
}

bool
NordicFlash::getBod()
{
    return false;
}

bool
NordicFlash::getBor()
{
    return false;
}

void
NordicFlash::setBor(bool enable)
{
}


bool
NordicFlash::getBootFlash()
{
    // Always boots from flash. No ROM boot available.
    return true;
}

void
NordicFlash::setBootFlash(bool enable)
{
    printf("Ignoring set boot from flash flag.\n");
}

void
NordicFlash::writePage(uint32_t page)
{
}

void
NordicFlash::readPage(uint32_t page, uint8_t* buf)
{
    throw FlashPageError();
}
