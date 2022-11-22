// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CRYPTO_X16R_H
#define CRYPTO_X16R_H

#include <serialize.h>
#include <uint256.h>
#include <version.h>

class CBlockHeader;

uint256 HashX16R(const CBlockHeader& obj);
uint256 HashX16RV2(const CBlockHeader& obj);

#endif // CRYPTO_X16R_H
