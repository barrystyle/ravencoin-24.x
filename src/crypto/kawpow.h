// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CRYPTO_KAWPOW_H
#define CRYPTO_KAWPOW_H

#include <serialize.h>
#include <uint256.h>
#include <version.h>

class CBlockHeader;

uint256 KAWPOWHash(const CBlockHeader& blockHeader, uint256& mix_hash);
uint256 KAWPOWHash_OnlyMix(const CBlockHeader& blockHeader);
uint256 HashKAWPOW(const CBlockHeader& obj);

#endif // CRYPTO_KAWPOW_H
