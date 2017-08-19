// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//
// Main network
//

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xd3;
        pchMessageStart[1] = 0xa4;
        pchMessageStart[2] = 0xe5;
        pchMessageStart[3] = 0xf6;
        nDefaultPort = 20028;
        nRPCPort = 20029;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        // Hashed MainNet Genesis Block Output
        // block.hashMerkleRoot == 4061031e449231be3cff61fb1fa4ef59fd0fd82c49f402704f22e7f2bad319c8
        // block.nTime = 1499734800
        // block.nNonce = 36733
        // block.GetHash = 000000bdc8a6e91c3bb3c3fd28242b78ccf537367d6971844910a0c5a5aee995
        //
        const char* pszTimestamp = "Quantum Computers vs Bitcoin – How Worried Should We Be? | Dariusz | July 10, 2017";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1499734800, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1499734800;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 36733;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000000bdc8a6e91c3bb3c3fd28242b78ccf537367d6971844910a0c5a5aee995"));
        assert(genesis.hashMerkleRoot == uint256("0x4061031e449231be3cff61fb1fa4ef59fd0fd82c49f402704f22e7f2bad319c8"));

        vFixedSeeds.clear();
        vSeeds.clear();

        /** REQUIRED IN QT 5.6+  (To compile on Qt5.5.1 and lower comment out below) */
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,122);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,124);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x50)(0xE7)(0xFC)(0x0A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x50)(0x9E)(0x4)(0x2F).convert_to_container<std::vector<unsigned char> >();

        // RoyalEmpireCoin dns seeds
         // vSeeds.push_back(CDNSSeedData("Seed01",  "127.0.0.1"));
         // vSeeds.push_back(CDNSSeedData("Seed02",  "127.0.0.1"));

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 0x7fffffff;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xea;
        pchMessageStart[1] = 0xf4;
        pchMessageStart[2] = 0xa0;
        pchMessageStart[3] = 0x35;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        nDefaultPort = 20063;
        nRPCPort = 20062;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1499734800+120; // Sat, 11 Mar 2017 01:28:20 GMT
        genesis.nNonce = 26;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.

        //Hashed TestNet Genesis Block Output
       // block.hashMerkleRoot == 4061031e449231be3cff61fb1fa4ef59fd0fd82c49f402704f22e7f2bad319c8
       // block.nTime = 1499734920
       // block.nNonce = 26
       // block.GetHash = 00fc73a14388221c851ba0acc4fdd552939dc6ae14256f3b2873a7f30e69594b




        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00fc73a14388221c851ba0acc4fdd552939dc6ae14256f3b2873a7f30e69594b"));

        vFixedSeeds.clear();
        vSeeds.clear();

        /** REQUIRED IN QT 5.6+  (To compile on Qt5.5.1 and lower comment out below) */
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,123);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,50);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,23);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x1D)(0x9B)(0x7F)(0x74).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x1D)(0xC0)(0xFC)(0x28).convert_to_container<std::vector<unsigned char> >();

        // RoyalEmpireCoin dns seeds
        // vSeeds.push_back(CDNSSeedData("Seed01",  "0.0.0.0"));
        // vSeeds.push_back(CDNSSeedData("Seed02",  "0.0.0.0"));

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xd2;
        pchMessageStart[3] = 0xf7;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1499734800+90;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 20087;
        strDataDir = "regtest";

        /** Genesis Block RegNet */

       // Hashed RegNet Genesis Block Output
       // block.hashMerkleRoot == 4061031e449231be3cff61fb1fa4ef59fd0fd82c49f402704f22e7f2bad319c8
       // block.nTime = 1499734890
       // block.nNonce = 8
       // block.GetHash = 3d1fed59dab8409a64f9abb919eeeed20d78f508c2ec87849e7b16abf20eec75


        assert(hashGenesisBlock == uint256("0x3d1fed59dab8409a64f9abb919eeeed20d78f508c2ec87849e7b16abf20eec75"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
