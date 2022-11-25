// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>

#include <chainparams.h>
#include <crypto/kawpow.h>
#include <crypto/x16r.h>
#include <hash.h>
#include <tinyformat.h>

uint256 CBlockHeader::GetHash() const
{
    const Consensus::Params& params = Params().GetConsensus();

    if (nTime < params.fActivationX16RV2) {
        return HashX16R(*this);
    } else if (nTime < params.fActivationKAWPOW) {
        return HashX16RV2(*this);
    }

    return HashKAWPOW(*this);
}

uint256 CBlockHeader::GetGenesisHash() const
{
    return HashX16R(*this);
}

bool CBlockHeader::IsKAWPOW() const
{
    const Consensus::Params& params = Params().GetConsensus();

    return nTime >= params.fActivationKAWPOW;
}

std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}
