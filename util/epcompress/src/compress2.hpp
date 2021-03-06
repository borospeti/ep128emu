
// compressor utility for Enterprise 128 programs
// Copyright (C) 2007-2016 Istvan Varga <istvanv@users.sourceforge.net>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef EPCOMPRESS_COMPRESS2_HPP
#define EPCOMPRESS_COMPRESS2_HPP

#include "ep128emu.hpp"
#include "compress.hpp"
#include "comprlib.hpp"

#include <vector>

namespace Ep128Compress {

  class Compressor_M2 : public Compressor {
   private:
    static const size_t minRepeatDist = 1;
    static const size_t maxRepeatDist = 524288;
    static const size_t minRepeatLen = 1;
    static const size_t maxRepeatLen = 512;
    static const unsigned int lengthMaxValue = 65535U;
    static const size_t lengthNumSlots = 8;
    static const size_t lengthPrefixSizeTable[lengthNumSlots];
    static const unsigned int offs1MaxValue = 4096U;
    static const size_t offs1NumSlots = 4;
    static const size_t offs1PrefixSize = 2;
    static const unsigned int offs2MaxValue = 16384U;
    static const size_t offs2NumSlots = 8;
    static const size_t offs2PrefixSize = 3;
    static const unsigned int offs3MaxValue = (unsigned int) maxRepeatDist;
    static const size_t offs3SlotCntTable[4];
    static const size_t literalSequenceMinLength = lengthNumSlots + 9;
    // --------
    struct LZMatchParameters {
      unsigned int  d;
      unsigned int  len;
      LZMatchParameters()
        : d(0),
          len(1)
      {
      }
      LZMatchParameters(const LZMatchParameters& r)
        : d(r.d),
          len(r.len)
      {
      }
      ~LZMatchParameters()
      {
      }
      inline LZMatchParameters& operator=(const LZMatchParameters& r)
      {
        d = r.d;
        len = r.len;
        return (*this);
      }
      inline void clear()
      {
        d = 0;
        len = 1;
      }
    };
    struct SplitOptimizationBlock {
      size_t  startPos;
      size_t  nBytes;
    };
    // --------
    EncodeTable   lengthEncodeTable;
    EncodeTable   offs1EncodeTable;
    EncodeTable   offs2EncodeTable;
    EncodeTable   offs3EncodeTable;
    size_t        offs3NumSlots;
    size_t        offs3PrefixSize;
    LZSearchTable *searchTable;
    size_t        savedOutBufPos;
    unsigned char outputShiftReg;
    int           outputBitCnt;
    // --------
    void writeRepeatCode(std::vector< unsigned int >& buf, size_t d, size_t n);
    inline size_t getRepeatCodeLength(size_t d, size_t n) const;
    void optimizeMatches_noStats(LZMatchParameters *matchTable,
                                 size_t *bitCountTable,
                                 size_t offs, size_t nBytes);
    void optimizeMatches(LZMatchParameters *matchTable,
                         size_t *bitCountTable, uint64_t *offsSumTable,
                         size_t offs, size_t nBytes);
    size_t compressData_(std::vector< unsigned int >& tmpOutBuf,
                         const std::vector< unsigned char >& inBuf,
                         size_t offs, size_t nBytes, bool firstPass,
                         bool fastMode = false);
    bool compressData(std::vector< unsigned int >& tmpOutBuf,
                      const std::vector< unsigned char >& inBuf,
                      unsigned int startAddr, bool isLastBlock,
                      size_t offs = 0, size_t nBytes = 0x7FFFFFFFUL,
                      bool fastMode = false);
   public:
    Compressor_M2(std::vector< unsigned char >& outBuf_);
    virtual ~Compressor_M2();
    // if 'startAddr' is 0xFFFFFFFF, it is not stored in the compressed data
    virtual bool compressData(const std::vector< unsigned char >& inBuf,
                              unsigned int startAddr, bool isLastBlock,
                              bool enableProgressDisplay = false);
  };

}       // namespace Ep128Compress

#endif  // EPCOMPRESS_COMPRESS2_HPP

