#include <crypto/kawpow.h>

#include <crypto/ethash/helpers.hpp>
#include <crypto/ethash/include/ethash/progpow.hpp>
#include <hash.h>
#include <primitives/block.h>
#include <util/strencodings.h>
#include <uint256.h>

uint256 GetKAWPOWHeaderHash(const CBlockHeader& blockHeader)
{
    CKAWPOWInput input{blockHeader};

    return SerializeHash(input);
}

uint256 KAWPOWHash(const CBlockHeader& blockHeader, uint256& mix_hash)
{
    static ethash::epoch_context_ptr context{nullptr, nullptr};

    // Get the context from the block height
    const auto epoch_number = ethash::get_epoch_number(blockHeader.nHeight);

    if (!context || context->epoch_number != epoch_number)
        context = ethash::create_epoch_context(epoch_number);

    // Build the header_hash
    uint256 nHeaderHash = GetKAWPOWHeaderHash(blockHeader);
    const auto header_hash = to_hash256(nHeaderHash.GetHex());

    // ProgPow hash
    const auto result = progpow::hash(*context, blockHeader.nHeight, header_hash, blockHeader.nNonce64);

    mix_hash = uint256S(to_hex(result.mix_hash));
    return uint256S(to_hex(result.final_hash));
}

uint256 KAWPOWHash_OnlyMix(const CBlockHeader& blockHeader)
{
    // Build the header_hash
    uint256 nHeaderHash = GetKAWPOWHeaderHash(blockHeader);
    const auto header_hash = to_hash256(nHeaderHash.GetHex());

    // ProgPow hash
    const auto result = progpow::hash_no_verify(blockHeader.nHeight, header_hash, to_hash256(blockHeader.mixHash.GetHex()), blockHeader.nNonce64);

    return uint256S(to_hex(result));
}

uint256 HashKAWPOW(const CBlockHeader& obj)
{
    return KAWPOWHash_OnlyMix(obj);
}
