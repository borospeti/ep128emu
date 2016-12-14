
// epimgconv: Enterprise 128 image converter utility
// Copyright (C) 2008-2016 Istvan Varga <istvanv@users.sourceforge.net>
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
//
// The Enterprise 128 program files generated by this utility are not covered
// by the GNU General Public License, and can be used, modified, and
// distributed without any restrictions.

#include "epimgconv.hpp"
#include "imgwrite.hpp"
#include "compress.hpp"

#include <vector>

static const unsigned char imageDisplayCode[] = {
  0x00, 0x05, 0x9C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xF3, 0x31, 0x00, 0x01, 0x3E, 0xFF, 0xD3, 0xB2,
  0x21, 0x9E, 0x01, 0x22, 0xF8, 0xBF, 0x2E, 0x00, 0x06, 0x11, 0xAF, 0x77,
  0x2C, 0x10, 0xFC, 0x11, 0x08, 0x01, 0xD5, 0xDB, 0xB0, 0x12, 0x2A, 0x9E,
  0x02, 0x7C, 0xC6, 0x9F, 0x7D, 0xCE, 0x02, 0x07, 0x07, 0xE6, 0x03, 0x28,
  0x07, 0x21, 0xFD, 0xBF, 0x1C, 0x4F, 0xED, 0xB0, 0xE1, 0x06, 0x04, 0x7E,
  0x3C, 0x20, 0x05, 0xCD, 0xE8, 0x01, 0x18, 0x17, 0x2C, 0x10, 0xF4, 0x2E,
  0x00, 0x01, 0x71, 0x2C, 0xCB, 0x9D, 0xF7, 0x18, 0xF3, 0xB7, 0x28, 0xF6,
  0xFE, 0x7F, 0x20, 0x03, 0xF7, 0x19, 0xF3, 0x2A, 0x9C, 0x02, 0x7D, 0xD3,
  0x81, 0x7C, 0xE6, 0x1F, 0xD3, 0x80, 0xAF, 0xF5, 0xCD, 0xF6, 0x01, 0xF1,
  0x4F, 0x21, 0xA0, 0x02, 0xCC, 0xD2, 0x01, 0x79, 0xC6, 0x41, 0x30, 0xEF,
  0xAF, 0x5F, 0x3E, 0x08, 0xD3, 0xB5, 0xDB, 0xB5, 0x87, 0x87, 0x7B, 0x8F,
  0xFE, 0xFE, 0x20, 0xF1, 0x3A, 0x10, 0x01, 0xB7, 0x20, 0x33, 0x21, 0x0C,
  0x01, 0x06, 0x04, 0x7E, 0xB7, 0x28, 0x08, 0x7D, 0xC6, 0xF0, 0x4F, 0x7E,
  0xCD, 0x7E, 0x02, 0x2C, 0x10, 0xF1, 0xF3, 0x31, 0x00, 0x01, 0x3E, 0xFF,
  0xD3, 0xB2, 0x2A, 0xF4, 0xBF, 0xCB, 0xFC, 0xCB, 0xF4, 0xCD, 0xD2, 0x01,
  0x0E, 0x60, 0xF7, 0x00, 0x3E, 0x01, 0xD3, 0xB3, 0x3E, 0x06, 0xC3, 0x0D,
  0xC0, 0xF3, 0xAF, 0xD3, 0xB3, 0x3D, 0xD3, 0xB2, 0x21, 0x00, 0x80, 0x11,
  0x01, 0x80, 0x01, 0xFF, 0x3F, 0x75, 0xED, 0xB0, 0x23, 0xE9, 0x7D, 0x06,
  0x04, 0xCB, 0x3C, 0x1F, 0x10, 0xFB, 0xD3, 0x82, 0x7C, 0xD3, 0x83, 0xCB,
  0xF7, 0xD3, 0x83, 0xCB, 0xFF, 0xD3, 0x83, 0xC9, 0x3E, 0xFF, 0x32, 0x10,
  0x01, 0xE5, 0x21, 0xBD, 0x01, 0x22, 0xF8, 0xBF, 0xE1, 0xC9, 0xF6, 0xFC,
  0x4F, 0xC6, 0x0C, 0x6F, 0x26, 0x01, 0x7E, 0xB7, 0xC8, 0xB9, 0xC8, 0x11,
  0x00, 0x01, 0x06, 0x10, 0x1A, 0xB9, 0x20, 0x07, 0x7B, 0xFE, 0x08, 0x38,
  0x43, 0x18, 0x0A, 0x1C, 0x10, 0xF2, 0xCD, 0xED, 0x01, 0x7D, 0xC6, 0x04,
  0x5F, 0xDB, 0xB0, 0xBE, 0x20, 0x37, 0xE5, 0x2E, 0x00, 0x06, 0x08, 0x7E,
  0xB7, 0x20, 0x1A, 0x2C, 0x10, 0xF9, 0xCD, 0xE8, 0x01, 0xAF, 0x3D, 0x2E,
  0x00, 0x06, 0x10, 0xBE, 0x20, 0x07, 0xFE, 0xFC, 0x20, 0xF4, 0xC3, 0x84,
  0x01, 0x2C, 0x10, 0xF3, 0x21, 0x36, 0x00, 0xE1, 0x12, 0x71, 0x4F, 0x7E,
  0xCD, 0x7E, 0x02, 0x4F, 0xDB, 0xB0, 0x18, 0x2A, 0x7E, 0x12, 0x71, 0x18,
  0x25, 0x7E, 0x12, 0x71, 0xCD, 0x90, 0x02, 0xF3, 0xED, 0x73, 0x7A, 0x02,
  0x31, 0x00, 0x40, 0x21, 0x00, 0xC0, 0xC1, 0x5E, 0x71, 0x2C, 0x56, 0x70,
  0xD5, 0xD1, 0x2C, 0xC2, 0x6A, 0x02, 0x24, 0x20, 0xF1, 0x31, 0x00, 0x00,
  0x18, 0x0D, 0xCD, 0x90, 0x02, 0x21, 0x00, 0x40, 0x11, 0x00, 0xC0, 0x44,
  0x4D, 0xED, 0xB0, 0xF1, 0xC1, 0xD1, 0xE1, 0xC9, 0xE3, 0xD5, 0xC5, 0xF5,
  0xD3, 0xB1, 0x79, 0xD3, 0xB3, 0xE9, 0x00, 0x00
};

namespace Ep128ImgConv {

  bool writeEPImageAsProgram(std::FILE *f,
                             const Ep128ImgConv::ImageData& imgData,
                             bool noCompress)
  {
    std::vector< unsigned char >  buf;
    int     nLines = int(imgData[6]) | (int(imgData[7]) << 8);
    int     nChars = imgData[8];
    if (nLines < 1 || nLines > 288 || nChars < 1 || nChars > 46)
      throw Ep128Emu::Exception("invalid image size for output format");
    int     borderColor = imgData[9];
    size_t  readPos = 16;
    int     videoMode = imgData[readPos++];
    int     fixBiasValue = 0;
    int     paletteColors = 0;
    bool    interlaceMode = bool(imgData[5] & 0x80);
    bool    fixedPalette = (imgData[4] == 0x00);
    bool    attributeMode = ((videoMode & 0x0E) == 0x04);
    if ((videoMode & 0x60) == 0x40 || attributeMode) {
      fixBiasValue = imgData[readPos++];
      paletteColors = 8;
    }
    else if ((videoMode & 0x60) == 0x00) {
      paletteColors = 2;
    }
    else if ((videoMode & 0x60) == 0x20) {
      paletteColors = 4;
    }
    int     lpbCnt = (fixedPalette ? (nLines <= 256 ? 1 : 2) : nLines);
    unsigned int  lptSize = (unsigned int) (lpbCnt + 5) * 16U;
    if (nLines < 288)
      lptSize += 16U;
    if (interlaceMode)
      lptSize = lptSize * 2U;
    unsigned int  imageDataSize = (unsigned int) (nLines * nChars * 2);
    if (interlaceMode)
      imageDataSize = imageDataSize * 2U;
    imageDataSize += lptSize;
    unsigned int  imageDisplayCodeSize =
        (unsigned int) (sizeof(imageDisplayCode) / sizeof(unsigned char)) - 16U;
    unsigned int  uncompressedProgramSize =
        16U + imageDisplayCodeSize + 4U + imageDataSize;
    noCompress = noCompress || (uncompressedProgramSize <= 0xBF10U);
    if (uncompressedProgramSize > (noCompress ? 0xFD30U : 0xF96CU)) {
      throw Ep128Emu::Exception("image data size is too large for "
                                "output format");
    }
    for (int fieldNum = 0; fieldNum < (interlaceMode ? 2 : 1); fieldNum++) {
      readPos =
          imgData.getPaletteDataOffset((imgData[5] & 0x04) == 0 ? 0 : fieldNum);
      // LPT / top border
                                        // 2's complement of number of lines
      buf.push_back((unsigned char) (254 - ((288 - nLines) / 2)));
      buf.push_back(0x12);              // video mode
      buf.push_back(0x3F);              // left margin
      buf.push_back(0x00);              // right margin
      for (int i = 0; i < 12; i++)      // LD1, LD2, palette: unused
        buf.push_back(0x00);
      // LPT / display area
      int     lineNum = 0;
      for (int yc = 0; yc < lpbCnt; yc++) {
        int     lineCnt = 1;
        if (fixedPalette)
          lineCnt = ((yc + 1) < lpbCnt ? 256 : (nLines & 0xFF));
        unsigned int  offs = (unsigned int) lineNum * (unsigned int) nChars;
        unsigned int  ld1Addr =
            (unsigned int) imgData.getVideoDataOffset((imgData[5] & 0x10) == 0 ?
                                                      0 : fieldNum)
            + lptSize + (offs * 2U);
        unsigned int  ld2Addr = 0U;
        if (attributeMode) {
          ld2Addr = ld1Addr - offs;
          ld1Addr = (unsigned int) imgData.getAttributeDataOffset(
                                       (imgData[5] & 0x08) == 0 ? 0 : fieldNum)
                    + lptSize + offs;
          ld1Addr -= (unsigned int) imgData.getAttributeDataOffset(0);
          ld2Addr -= (unsigned int) imgData.getAttributeDataOffset(0);
        }
        else {
          ld1Addr -= (unsigned int) imgData.getVideoDataOffset(0);
        }
        if (fieldNum > 0 && (imgData[5] & 0x04) != 0) {
          if (ld1Addr != 0U)
            ld1Addr -= (unsigned int) (nLines * paletteColors);
          if (ld2Addr != 0U)
            ld2Addr -= (unsigned int) (nLines * paletteColors);
        }
        if (ld1Addr != 0U)
          ld1Addr += (0x0100U + imageDisplayCodeSize + 4U);
        if (ld2Addr != 0U)
          ld2Addr += (0x0100U + imageDisplayCodeSize + 4U);
        // 2's complement of number of lines
        buf.push_back((unsigned char) (256 - lineCnt));
        // video mode
        buf.push_back((unsigned char) (videoMode | 0x10));
        // left margin
        buf.push_back((unsigned char) (31 - (nChars / 2)));
        // right margin
        buf.push_back((unsigned char) (31 + ((nChars + 1) / 2)));
        // video data addr low
        buf.push_back((unsigned char) (ld1Addr & 0xFFU));
        // addr high
        buf.push_back((unsigned char) ((ld1Addr >> 8) & 0xFFU));
        // LD2 low
        buf.push_back((unsigned char) (ld2Addr & 0xFFU));
        // LD2 high
        buf.push_back((unsigned char) ((ld2Addr >> 8) & 0xFFU));
        // 8 palette colors
        for (int i = 0; i < paletteColors; i++)
          buf.push_back(imgData[readPos + i]);
        if ((yc + 1) >= lpbCnt || !fixedPalette)
          readPos = readPos + size_t(paletteColors);
        for (int i = paletteColors; i < 8; i++)
          buf.push_back(0x00);
        lineNum = lineNum + lineCnt;
      }
      // LPT / bottom border
      if (nLines < 288) {               // 2's complement of number of lines
        buf.push_back((unsigned char) (256 - ((288 - (nLines - 1)) / 2)));
        buf.push_back(0x12);            // video mode
        buf.push_back(0x3F);            // left margin
        buf.push_back(0x00);            // right margin
        for (int i = 0; i < 12; i++)    // LD1, LD2, palette: unused
          buf.push_back(0x00);
      }
      // LPT / vertical blanking
      buf.push_back(0xFD);              // 2's complement of number of lines
      buf.push_back(0x00);              // video mode
      buf.push_back(0x3F);              // left margin
      buf.push_back(0x00);              // right margin
      for (int i = 0; i < 12; i++)      // LD1, LD2, palette: unused
        buf.push_back(0x00);
      buf.push_back(0xFE);              // 2's complement of number of lines
      buf.push_back(0x00);              // video mode
                                        // left margin
      buf.push_back((unsigned char) ((interlaceMode && fieldNum == 0) ?
                                     0x20 : 0x06));
      buf.push_back(0x3F);              // right margin
      for (int i = 0; i < 12; i++)      // LD1, LD2, palette: unused
        buf.push_back(0x00);
      buf.push_back(0xFF);              // 2's complement of number of lines
      buf.push_back(0x00);              // video mode
      buf.push_back(0x3F);              // left margin
                                        // right margin
      buf.push_back((unsigned char) ((interlaceMode && fieldNum == 0) ?
                                     0x38 : 0x20));
      for (int i = 0; i < 12; i++)      // LD1, LD2, palette: unused
        buf.push_back(0x00);
                                        // 2's complement of number of lines
      buf.push_back((unsigned char) ((interlaceMode && fieldNum == 0) ?
                                     0xEF : 0xF0));
                                        // video mode
      buf.push_back((unsigned char) ((interlaceMode && fieldNum == 0) ?
                                     0x12 : 0x13));
      buf.push_back(0x06);              // left margin
      buf.push_back(0x3F);              // right margin
      for (int i = 0; i < 12; i++)      // LD1, LD2, palette: unused
        buf.push_back(0x00);
    }
    // video data
    if (!attributeMode)
      readPos = imgData.getVideoDataOffset(0);
    else
      readPos = imgData.getAttributeDataOffset(0);
    while (readPos < imgData.size()) {
      buf.push_back((unsigned char) imgData[readPos]);
      readPos++;
      if (readPos == imgData.getPaletteDataOffset(1))
        readPos += size_t(nLines * paletteColors);
    }
    {
      std::vector< unsigned char >  tmpBuf;
      unsigned int  programSize = uncompressedProgramSize - 16U;
      for (int i = 0; i < int(imageDisplayCodeSize + 16U); i++) {
        int     b = imageDisplayCode[i];
        if (i == 2)
          b = int(programSize & 0xFFU);
        else if (i == 3)
          b = int((programSize >> 8) & 0xFFU);
        tmpBuf.push_back((unsigned char) b);
      }
      tmpBuf.push_back((unsigned char) borderColor);
      tmpBuf.push_back((unsigned char) fixBiasValue);
      tmpBuf.push_back((unsigned char) ((imageDataSize >> 8) & 0xFFU));
      tmpBuf.push_back((unsigned char) (imageDataSize & 0xFFU));
      buf.insert(buf.begin(), tmpBuf.begin(), tmpBuf.end());
    }
    if (!noCompress) {
      // compress large (> 3*16K segments) program files
      buf.erase(buf.begin(), buf.begin() + 16);
      std::vector< unsigned char >  tmpBuf;
      Ep128Compress::Compressor *compressor =
          Ep128Compress::createCompressor(0, tmpBuf);
      try {
        compressor->setCompressionLevel(8);
        if (!(compressor->compressData(buf, 0x0100U, true, true))) {
          delete compressor;
          return false;
        }
      }
      catch (...) {
        delete compressor;
        throw;
      }
      delete compressor;
      buf.clear();
      Ep128Compress::addSFXModule(buf, tmpBuf, 0, false, true, false);
    }
    for (size_t i = 0; i < buf.size(); i++) {
      if (std::fputc(buf[i], f) == EOF)
        return false;
    }
    return true;
  }

  static void compressDataBlock(std::vector< unsigned char >& outBuf,
                                const std::vector< unsigned char >& inBuf,
                                int compressionType, int compressionLevel)
  {
    static const int compressionTypes[4] = {
      2, 0, 3, 5
    };
    Ep128Compress::Compressor *compress_ = (Ep128Compress::Compressor *) 0;
    try {
      Ep128Compress::Compressor::CompressionParameters  cfg;
      compressionType = compressionTypes[(compressionType - 1) & 3];
      compress_ = Ep128Compress::createCompressor(compressionType, outBuf);
      compress_->getCompressionParameters(cfg);
      if (compressionLevel >= 1 && compressionLevel <= 9) {
        cfg.setCompressionLevel(compressionLevel);
      }
      else {
        // level -1 = default "fast" setting
        // level -2 = default "maximum" setting
         if (compressionLevel >= -1)
          cfg.setCompressionLevel(compressionType == 2 ? 5 : 8);
        else
          cfg.setCompressionLevel(9);
        if (compressionType == 5) {
          cfg.minLength = 3;
          cfg.maxOffset = 32768;
        }
        compress_->setCompressionParameters(cfg);
      }
      compress_->compressData(inBuf, 0xFFFFFFFFU, true, true);
      delete compress_;
      compress_ = (Ep128Compress::Compressor *) 0;
    }
    catch (...) {
      if (compress_) {
        delete compress_;
        compress_ = (Ep128Compress::Compressor *) 0;
      }
      throw;
    }
  }

  bool writeEPImageAsIViewFile(std::FILE *f,
                               const Ep128ImgConv::ImageData& imgData,
                               int outputFormat)
  {
    size_t  offsTable[11];
    for (int i = 0; i < 2; i++) {
      offsTable[0 + (i * 5)] = imgData.getVideoModeTableOffset(i);
      offsTable[1 + (i * 5)] = imgData.getFixBiasTableOffset(i);
      offsTable[2 + (i * 5)] = imgData.getPaletteDataOffset(i);
      offsTable[3 + (i * 5)] = imgData.getAttributeDataOffset(i);
      offsTable[4 + (i * 5)] = imgData.getVideoDataOffset(i);
    }
    offsTable[10] = imgData.size();
    for (int i = 9; i >= 0; i--) {
      if (offsTable[i] == 0)
        offsTable[i] = offsTable[i + 1];
    }
    std::vector< unsigned char >  buf;
    if (outputFormat < 10) {
      for (size_t i = 0; i < 16; i++)
        buf.push_back(imgData[i]);
      buf[11] = (unsigned char) (int(bool(buf[5] & 0x1F)) + 1);
    }
    size_t  attrOffset = 0;
    for (int i = 0; i != 14; i += 5) {
      i = (i < 10 ? i : (i - 9));
      if (i == 3)
        attrOffset = buf.size();
      for (size_t j = offsTable[i]; j < offsTable[i + 1]; j++)
        buf.push_back(imgData[j]);
    }
    if (outputFormat >= 10) {
      if (buf.size() > 0xFE00) {
        throw Ep128Emu::Exception("image data size is too large for "
                                  "output format");
      }
      std::vector< unsigned char >  tmpBuf;
      std::vector< unsigned char >  tmpBuf2;
      {
        tmpBuf2.insert(tmpBuf2.end(),
                       buf.begin(), buf.begin() + attrOffset);
        compressDataBlock(tmpBuf, tmpBuf2,
                          outputFormat / 10, outputFormat % 10);
        size_t  uncompressedSize = tmpBuf2.size();
        tmpBuf2.clear();
        tmpBuf2.insert(tmpBuf2.end(),
                       buf.begin() + attrOffset, buf.end());
        buf.clear();
        for (size_t i = 0; i < 16; i++)
          buf.push_back(imgData[i]);
        buf[10] = (unsigned char) (outputFormat / 10);
        buf[11] = (unsigned char) (int(bool(buf[5] & 0x1F)) + 1);
        buf.push_back((unsigned char) (uncompressedSize & 0xFF));
        buf.push_back((unsigned char) ((uncompressedSize >> 8) & 0xFF));
        buf.push_back((unsigned char) (tmpBuf.size() & 0xFF));
        buf.push_back((unsigned char) ((tmpBuf.size() >> 8) & 0xFF));
        buf.insert(buf.end(), tmpBuf.begin(), tmpBuf.end());
        tmpBuf.clear();
      }
      {
        compressDataBlock(tmpBuf, tmpBuf2,
                          outputFormat / 10, outputFormat % 10);
        size_t  uncompressedSize = tmpBuf2.size();
        tmpBuf2.clear();
        buf.push_back((unsigned char) (uncompressedSize & 0xFF));
        buf.push_back((unsigned char) ((uncompressedSize >> 8) & 0xFF));
        buf.push_back((unsigned char) (tmpBuf.size() & 0xFF));
        buf.push_back((unsigned char) ((tmpBuf.size() >> 8) & 0xFF));
        buf.insert(buf.end(), tmpBuf.begin(), tmpBuf.end());
        tmpBuf.clear();
      }
    }
    for (size_t i = 0; i < buf.size(); i++) {
      if (std::fputc(buf[i], f) == EOF)
        return false;
    }
    return true;
  }

  bool writeEPImageAsCRFFile(std::FILE *f,
                             const Ep128ImgConv::ImageData& imgData)
  {
    if (imgData[2] != 0 || imgData[3] != 0 || imgData[5] != 0 ||
        imgData[16] != 0x32) {
      // must be non-interlaced 4-color PIXEL mode
      throw Ep128Emu::Exception("invalid video mode for output format");
    }
    if (imgData.size() > 64000) {
      throw Ep128Emu::Exception("image data size is too large for "
                                "output format");
    }
    std::vector< unsigned char >  buf;
    int     width = int(imgData[8]) * 8;
    int     height = int(imgData[6]) | (int(imgData[7]) << 8);
    buf.push_back((unsigned char) ((height - 1) & 0xFF));
    buf.push_back((unsigned char) ((height - 1) >> 8));
    buf.push_back((unsigned char) ((width - 1) & 0xFF));
    buf.push_back((unsigned char) ((width - 1) >> 8));
    buf.push_back((unsigned char) ((width / 4) & 0xFF));
    buf.push_back((unsigned char) ((width / 4) >> 8));
    size_t  pixelDataSize = size_t(width * height / 4);
    buf.push_back((unsigned char) (pixelDataSize & 0xFF));
    buf.push_back((unsigned char) (pixelDataSize >> 8));
    // compress pixel data
    {
      std::vector< unsigned short > rleLengths(pixelDataSize);
      std::vector< size_t >         flagByteCosts(256, 0);
      // find RLE sequence lengths
      size_t        rleLength = 0;
      unsigned int  rleByte = 0xFFFFFFFFU;
      for (size_t i = pixelDataSize; i-- > 0; ) {
        unsigned int  c = imgData[imgData.getVideoDataOffset(0) + i];
        if (c != rleByte) {
          rleLength = 0;
          rleByte = c;
        }
        rleLength++;
        rleLengths[i] = (unsigned short) rleLength;
      }
      // find best RLE flag byte
      for (size_t i = 0; i < pixelDataSize; i++) {
        if (rleLengths[i] < 4) {
          unsigned int  c = imgData[imgData.getVideoDataOffset(0) + i];
          flagByteCosts[c] += size_t(4 - rleLengths[i]);
        }
      }
      size_t        bestFlagByteCost = 0x7FFFFFFF;
      unsigned char flagByte = 0x00;
      for (int i = 0; i < 256; i++) {
        if (flagByteCosts[i] < bestFlagByteCost) {
          bestFlagByteCost = flagByteCosts[i];
          flagByte = (unsigned char) i;
        }
      }
      size_t  compressedSizeOffset = buf.size();
      buf.push_back(0x00);      // reserve space for compressed data size
      buf.push_back(0x00);
      buf.push_back(flagByte);
      for (size_t i = 0; i < pixelDataSize; ) {
        unsigned char c = imgData[imgData.getVideoDataOffset(0) + i];
        if (rleLengths[i] > 4 || c == flagByte) {
          buf.push_back(flagByte);
          buf.push_back(c);
          buf.push_back((unsigned char) ((rleLengths[i] - 1) & 0xFF));
          buf.push_back((unsigned char) ((rleLengths[i] - 1) >> 8));
          i = i + rleLengths[i];
        }
        else {
          buf.push_back(c);
          i++;
        }
      }
      size_t  compressedSize = buf.size() - (compressedSizeOffset + 3);
      buf[compressedSizeOffset] = (unsigned char) (compressedSize & 0xFF);
      buf[compressedSizeOffset + 1] = (unsigned char) (compressedSize >> 8);
    }
    size_t  paletteDataBegin = imgData.getPaletteDataOffset(0);
    for (int yc = 0; yc < height; yc++) {
      size_t  offs = paletteDataBegin;
      if (imgData[4] != 0)
        offs += (size_t(yc / int(imgData[4])) * 4);
      for (size_t i = 0; i < 4; i++)
        buf.push_back(imgData[offs + i]);
    }
    for (size_t i = 0; i < buf.size(); i++) {
      if (std::fputc(buf[i], f) == EOF)
        return false;
    }
    return true;
  }

  bool writeEPImageAsVLoadFile(std::FILE *f,
                               const Ep128ImgConv::ImageData& imgData)
  {
    if (imgData[2] != 0 || imgData[3] != 0 || imgData[4] != 0 ||
        imgData[5] != 0) {
      // must be non-interlaced mode with fixed palette
      throw Ep128Emu::Exception("invalid video mode for output format");
    }
    int     width = imgData[8];
    int     height = int(imgData[6]) | (int(imgData[7]) << 8);
    if (width < 1 || width > 42 || height < 9 || height > 243 ||
        (height % 9) != 0) {
      throw Ep128Emu::Exception("invalid image size for output format");
    }
    int     videoMode = (imgData[16] & 0x0E) >> 1;
    int     colorMode = (imgData[16] & 0x60) >> 5;
    if ((imgData[16] & 0x10) == 0 ||
        (videoMode != 1 && videoMode != 2 && videoMode != 7) ||
        (videoMode == 2 && colorMode != 0)) {
      // only PIXEL, LPIXEL, and ATTRIBUTE modes are supported
      throw Ep128Emu::Exception("invalid video mode for output format");
    }
    videoMode = (videoMode != 2 ? (videoMode != 7 ? videoMode : 4) : 15);
    std::vector< unsigned char >  buf;
    buf.push_back(0x00);
    buf.push_back(0xDA);
    buf.push_back((unsigned char) (height / 9));
    buf.push_back((unsigned char) (width * (videoMode == 1 ? 2 : 1)));
    buf.push_back((unsigned char) colorMode);
    buf.push_back((unsigned char) videoMode);
    buf.push_back(0x01);
    buf.push_back((unsigned char) (height / 9));
    buf.push_back(0x01);
    for (int i = 0; i < 7; i++)
      buf.push_back(0x00);
    for (int i = 0; i < 8; i++) {
      if (i < ((videoMode != 15 && colorMode != 2) ?
               (colorMode < 2 ? (1 << (colorMode + 1)) : 0) : 8)) {
        buf.push_back(imgData[imgData.getPaletteDataOffset(0) + size_t(i)]);
      }
      else {
        buf.push_back(0x00);
      }
    }
    if (videoMode == 15 || colorMode == 2)
      buf.push_back(imgData[imgData.getFixBiasTableOffset(0)] << 3);
    else
      buf.push_back(0x00);
    buf.push_back(0x00);        // reserve space for compressed data size
    buf.push_back(0x00);
    // compress video data
    {
      std::vector< unsigned char >  tmpBuf;
      size_t  pixelDataSize = size_t(width * height * (videoMode == 1 ? 2 : 1));
      for (size_t i = 0; i < pixelDataSize; i++)
        tmpBuf.push_back(imgData[imgData.getVideoDataOffset(0) + i]);
      if (videoMode == 15) {
        for (size_t i = 0; i < pixelDataSize; i++)
          tmpBuf.push_back(imgData[imgData.getAttributeDataOffset(0) + i]);
      }
      std::vector< unsigned short > rleLengths(tmpBuf.size());
      std::vector< size_t >         flagByteCosts(256, 0);
      // find RLE sequence lengths
      size_t        rleLength = 0;
      unsigned int  rleByte = 0xFFFFFFFFU;
      for (size_t i = tmpBuf.size(); i-- > 0; ) {
        unsigned int  c = tmpBuf[i];
        if (c != rleByte) {
          rleLength = 0;
          rleByte = c;
        }
        if (rleLength < 256)
          rleLength++;
        rleLengths[i] = (unsigned short) rleLength;
      }
      for (size_t i = 0; i < tmpBuf.size(); ) {
        buf.push_back(tmpBuf[i]);
        buf.push_back((unsigned char) (rleLengths[i] - 1));
        i += size_t(rleLengths[i]);
      }
      size_t  compressedSize = buf.size() - 27;
      buf[25] = (unsigned char) (compressedSize & 0xFF);
      buf[26] = (unsigned char) (compressedSize >> 8);
      if (pixelDataSize > 16384 || buf.size() > 16384) {
        std::fprintf(stderr, "WARNING: output file may be too large "
                             "to load with :VL\n");
      }
    }
    for (size_t i = 0; i < buf.size(); i++) {
      if (std::fputc(buf[i], f) == EOF)
        return false;
    }
    return true;
  }

  bool writeEPImageAsPaintBoxFile(std::FILE *f,
                                  const Ep128ImgConv::ImageData& imgData)
  {
    if (imgData[2] != 0 || imgData[3] != 0 || imgData[4] != 0 ||
        imgData[5] != 0) {
      // must be non-interlaced mode with fixed palette
      throw Ep128Emu::Exception("invalid video mode for output format");
    }
    int     width = imgData[8];
    int     height = int(imgData[6]) | (int(imgData[7]) << 8);
    if (width < 1 || width > 42 || height < 9 || height > 243 ||
        (height % 9) != 0) {
      throw Ep128Emu::Exception("invalid image size for output format");
    }
    int     videoMode = (imgData[16] & 0x0E) >> 1;
    int     colorMode = (imgData[16] & 0x60) >> 5;
    if ((imgData[16] & 0x10) == 0 ||
        (videoMode != 1 && videoMode != 2 && videoMode != 7) ||
        (videoMode == 2 && colorMode != 0)) {
      // only PIXEL, LPIXEL, and ATTRIBUTE modes are supported
      throw Ep128Emu::Exception("invalid video mode for output format");
    }
    videoMode = (videoMode != 2 ? (videoMode != 7 ? videoMode : 4) : 15);
    std::vector< unsigned char >  buf;
    buf.push_back((unsigned char) (height / 9));
    buf.push_back((unsigned char) (width * (videoMode == 1 ? 2 : 1)));
    buf.push_back((unsigned char) colorMode);
    buf.push_back((unsigned char) videoMode);
    for (int i = 0; i < 8; i++) {
      if (i < ((videoMode != 15 && colorMode != 2) ?
               (colorMode < 2 ? (1 << (colorMode + 1)) : 0) : 8)) {
        buf.push_back(imgData[imgData.getPaletteDataOffset(0) + size_t(i)]);
      }
      else {
        buf.push_back(0x00);
      }
    }
    if (videoMode == 15 || colorMode == 2) {
      std::fprintf(stderr,
                   "WARNING: PaintBox format does not include FIXBIAS, "
                   "use -bias 23, or :var 28,%d\n",
                   int(imgData[imgData.getFixBiasTableOffset(0)] << 3));
    }
    size_t  pixelDataSize = size_t(width * height * (videoMode == 1 ? 2 : 1));
    for (size_t i = 0; i < pixelDataSize; i++)
      buf.push_back(imgData[imgData.getVideoDataOffset(0) + i]);
    if (videoMode == 15) {
      for (size_t i = 0; i < pixelDataSize; i++)
        buf.push_back(imgData[imgData.getAttributeDataOffset(0) + i]);
    }
    for (size_t i = 0; i < buf.size(); i++) {
      if (std::fputc(buf[i], f) == EOF)
        return false;
    }
    return true;
  }

  bool writeEPImageAsZaxialFile(std::FILE *f,
                                const Ep128ImgConv::ImageData& imgData)
  {
    if (imgData[2] != 0 || imgData[3] != 0 || imgData[4] != 0 ||
        imgData[5] != 0) {
      // must be non-interlaced mode with fixed palette
      throw Ep128Emu::Exception("invalid video mode for output format");
    }
    int     width = imgData[8];
    int     height = int(imgData[6]) | (int(imgData[7]) << 8);
    if (width < 1 || width > 42 || height < 9 || height > 243 ||
        (height % 9) != 0) {
      throw Ep128Emu::Exception("invalid image size for output format");
    }
    int     videoMode = (imgData[16] & 0x0E) >> 1;
    int     colorMode = (imgData[16] & 0x60) >> 5;
    if ((imgData[16] & 0x10) == 0 ||
        (videoMode != 1 && videoMode != 2 && videoMode != 7) ||
        (videoMode == 2 && colorMode != 0)) {
      // only PIXEL, LPIXEL, and ATTRIBUTE modes are supported
      throw Ep128Emu::Exception("invalid video mode for output format");
    }
    videoMode = (videoMode != 2 ? (videoMode != 7 ? videoMode : 4) : 15);
    if (videoMode == 15) {
      std::fprintf(stderr,
                   "WARNING: attribute mode is not supported by Zaxial\n");
    }
    std::vector< unsigned char >  buf;
    buf.push_back(0x00);
    buf.push_back(0x0B);
    buf.push_back((unsigned char) videoMode);
    buf.push_back((unsigned char) colorMode);
    buf.push_back((unsigned char) width);
    buf.push_back((unsigned char) (height / 9));
    for (int i = 0; i < 8; i++) {
      if (i < ((videoMode != 15 && colorMode != 2) ?
               (colorMode < 2 ? (1 << (colorMode + 1)) : 0) : 8)) {
        buf.push_back(imgData[imgData.getPaletteDataOffset(0) + size_t(i)]);
      }
      else {
        buf.push_back(0x00);
      }
    }
    if (videoMode == 15 || colorMode == 2)
      buf.push_back(imgData[imgData.getFixBiasTableOffset(0)] << 3);
    else
      buf.push_back(0x00);
    buf.push_back(0x5A);
    size_t  pixelDataSize = size_t(width * 9 * (videoMode == 1 ? 2 : 1));
    for (size_t i = 0; i < size_t(height / 9); i++) {
      size_t  offs = imgData.getVideoDataOffset(0) + (i * pixelDataSize);
      for (size_t j = 0; j < pixelDataSize; j++)
        buf.push_back(imgData[offs + j]);
      if (videoMode == 15) {
        offs = imgData.getAttributeDataOffset(0) + (i * pixelDataSize);
        for (size_t j = 0; j < pixelDataSize; j++)
          buf.push_back(imgData[offs + j]);
      }
    }
    for (size_t i = 0; i < buf.size(); i++) {
      if (std::fputc(buf[i], f) == EOF)
        return false;
    }
    return true;
  }

  bool writeEPImageAsRawFile(std::FILE *f,
                             const Ep128ImgConv::ImageData& imgData)
  {
    size_t  offsTable[5];
    for (int i = 0; i < 2; i++) {
      offsTable[0 + (i * 2)] = imgData.getAttributeDataOffset(i);
      offsTable[1 + (i * 2)] = imgData.getVideoDataOffset(i);
    }
    offsTable[4] = imgData.size();
    for (int i = 3; i >= 0; i--) {
      if (offsTable[i] == 0)
        offsTable[i] = offsTable[i + 1];
    }
    std::vector< unsigned char >  buf;
    for (int i = 0; i != 5; i += 2) {
      i = (i < 4 ? i : (i - 3));
      for (size_t j = offsTable[i]; j < offsTable[i + 1]; j++)
        buf.push_back(imgData[j]);
    }
    for (size_t i = 0; i < buf.size(); i++) {
      if (std::fputc(buf[i], f) == EOF)
        return false;
    }
    return true;
  }

  static void tvcKEPCompress(std::vector< unsigned char >& outBuf,
                             const unsigned char *inBuf, int w, int h)
  {
    size_t  nBytes = size_t(w * h);
    std::vector< size_t >         compressedSizeBuf((nBytes + 1) << 2, 0);
    std::vector< unsigned char >  lenBuf(nBytes << 2);
    for (size_t i = nBytes; i-- > 0; ) {
      unsigned char c = inBuf[i];
      unsigned char maxLen = 63;
      // RLE sequences may not cross line boundaries
      if (int(maxLen) > (w - (int(i) % w)))
        maxLen = (unsigned char) (w - (int(i) % w));
      for (unsigned char m = 0; m < 4; m++) {
        size_t  bestSize =
            compressedSizeBuf[((i + 1) << 2) + ((m + 1) & 3)] + 2;
        unsigned char bestLen = 1;
        if ((c ^ (m << 6)) & 0xC0) {
          size_t  n = compressedSizeBuf[((i + 1) << 2) + m] + 1;
          if (n <= bestSize) {
            bestSize = n;
            bestLen = 0;
          }
        }
        for (unsigned char l = 2; l <= maxLen; l++) {
          if (inBuf[i + (l - 1)] != c) {
            maxLen = l - 1;
            break;
          }
          size_t  n = compressedSizeBuf[((i + l) << 2) + m] + 2;
          if (n <= bestSize) {
            bestSize = n;
            bestLen = l;
          }
        }
        compressedSizeBuf[(i << 2) + m] = bestSize;
        lenBuf[(i << 2) + m] = bestLen;
      }
    }
    unsigned char m = 0;
    for (size_t i = 0; i < nBytes; ) {
      unsigned char l = lenBuf[(i << 2) + m];
      unsigned char c = inBuf[i];
      if (!l) {
        l = 1;
      }
      else {
        outBuf.push_back((m << 6) | l);
        if (l == 1)
          m = (m + 1) & 3;
      }
      outBuf.push_back(c);
      i = i + l;
    }
  }

  bool writeTVCImageAsKEPFile(std::FILE *f,
                              const Ep128ImgConv::ImageData& imgData,
                              int outputFormat)
  {
    std::vector< unsigned char >  tmpBuf;
    std::vector< unsigned char >  tmpBuf2;
    size_t  offsTable[11];
    for (int i = 0; i < 2; i++) {
      offsTable[0 + (i * 5)] = imgData.getVideoModeTableOffset(i);
      offsTable[1 + (i * 5)] = imgData.getFixBiasTableOffset(i);
      offsTable[2 + (i * 5)] = imgData.getPaletteDataOffset(i);
      offsTable[3 + (i * 5)] = imgData.getAttributeDataOffset(i);
      offsTable[4 + (i * 5)] = imgData.getVideoDataOffset(i);
    }
    offsTable[10] = imgData.size();
    for (int i = 9; i >= 0; i--) {
      if (offsTable[i] == 0)
        offsTable[i] = offsTable[i + 1];
    }
    std::vector< unsigned char >  buf;
    unsigned char mode = (imgData[offsTable[0]] & 0x60) >> 5;
    unsigned int  width = (unsigned int) imgData[8];
    unsigned int  height =
        (unsigned int) imgData[6] | ((unsigned int) imgData[7] << 8);
    width = width << (4 - mode);
    if (outputFormat != 50 && outputFormat != 55)
      mode |= (unsigned char) (0x90 | (((outputFormat % 5) - 1) << 2));
    if (imgData[4] != 0 && !(mode & 0x02))
      mode = mode | 0xA0;
    if (imgData[5] & 0x10) {
      height = height << 1;
      mode = mode | 0xC0;
    }
    if (!(mode & 0x10))
      mode = mode | (outputFormat == 50 ? 0x08 : 0x0C);
    // write header
    buf.push_back(0x4B);                // 'K'
    buf.push_back(0x45);                // 'E'
    buf.push_back(0x50);                // 'P'
    buf.push_back(mode);                // format / compression byte
    buf.push_back(0x00);                // palette color 0
    buf.push_back(0x00);                // palette color 1
    buf.push_back(0x00);                // palette color 2
    buf.push_back(0x00);                // palette color 3
    buf.push_back((unsigned char) (width & 0xFFU));     // width LSB
    buf.push_back((unsigned char) (width >> 8));        // width MSB
    buf.push_back((unsigned char) (height & 0xFFU));    // height LSB
    buf.push_back((unsigned char) (height >> 8));       // height MSB
    buf.push_back(0x00);                // 4 unused/reserved bytes
    buf.push_back(0x00);
    buf.push_back(0x00);
    buf.push_back(0x00);
    // write palette
    if (!(mode & 0x20)) {
      // -palres 0
      for (size_t i = 0; i < 4; i++) {
        if (i >= (offsTable[3] - offsTable[2]))
          break;
        buf[i + 4] = imgData[offsTable[2] + i];
      }
    }
    else {
      // -palres 1
      if (!(mode & 0x10)) {
        for (size_t i = offsTable[2]; i < offsTable[3]; i++)
          buf.push_back(imgData[i]);
        for (size_t i = offsTable[7]; i < offsTable[8]; i++)
          buf.push_back(imgData[i]);
      }
      else {
        tmpBuf.clear();
        tmpBuf2.clear();
        for (size_t i = offsTable[2]; i < offsTable[3]; i++)
          tmpBuf.push_back(imgData[i]);
        for (size_t i = offsTable[7]; i < offsTable[8]; i++)
          tmpBuf.push_back(imgData[i]);
        compressDataBlock(tmpBuf2, tmpBuf,
                          outputFormat % 5, (outputFormat < 55 ? -1 : -2));
        buf.insert(buf.end(), tmpBuf2.begin(), tmpBuf2.end());
      }
    }
    // write pixel data
    if (!(mode & 0x14)) {
      // uncompressed format
      for (size_t i = offsTable[4]; i < offsTable[5]; i++)
        buf.push_back(imgData[i]);
      for (size_t i = offsTable[9]; i < offsTable[10]; i++)
        buf.push_back(imgData[i]);
    }
    else {
      tmpBuf.clear();
      for (size_t i = offsTable[4]; i < offsTable[5]; i++)
        tmpBuf.push_back(imgData[i]);
      for (size_t i = offsTable[9]; i < offsTable[10]; i++)
        tmpBuf.push_back(imgData[i]);
      if (!(mode & 0x10)) {
        // RLE compression
        tvcKEPCompress(buf,
                       &(tmpBuf.front()), int(imgData[8]) << 1, int(height));
      }
      else {
        // epcompress format
        tmpBuf2.clear();
        compressDataBlock(tmpBuf2, tmpBuf,
                          outputFormat % 5, (outputFormat < 55 ? -1 : -2));
        buf.insert(buf.end(), tmpBuf2.begin(), tmpBuf2.end());
      }
    }
    for (size_t i = 0; i < buf.size(); i++) {
      if (std::fputc(buf[i], f) == EOF)
        return false;
    }
    return true;
  }

  void writeConvertedImageFile(const char *fileName, const ImageData& imgData,
                               int outputFormat, bool noCompress)
  {
    if (!((outputFormat >= 0 && outputFormat <= 6) ||
          (outputFormat >= 11 && outputFormat <= 59 &&
           outputFormat != 20 && outputFormat != 30 && outputFormat != 40))) {
      throw Ep128Emu::Exception("invalid output format");
    }
    std::FILE *f = (std::FILE *) 0;
    try {
      if (fileName == (char *) 0 || fileName[0] == '\0')
        throw Ep128Emu::Exception("invalid output file name");
      f = std::fopen(fileName, "wb");
      if (!f)
        throw Ep128Emu::Exception("error opening output file");
      bool    writeSuccessful = false;
      switch (outputFormat) {
      case 0:
        writeSuccessful = writeEPImageAsProgram(f, imgData, noCompress);
        break;
      case 2:
        writeSuccessful = writeEPImageAsCRFFile(f, imgData);
        break;
      case 3:
        writeSuccessful = writeEPImageAsVLoadFile(f, imgData);
        break;
      case 4:
        writeSuccessful = writeEPImageAsPaintBoxFile(f, imgData);
        break;
      case 5:
        writeSuccessful = writeEPImageAsZaxialFile(f, imgData);
        break;
      case 6:
        writeSuccessful = writeEPImageAsRawFile(f, imgData);
        break;
      default:
        if (outputFormat >= 50)
          writeSuccessful = writeTVCImageAsKEPFile(f, imgData, outputFormat);
        else
          writeSuccessful = writeEPImageAsIViewFile(f, imgData, outputFormat);
        break;
      }
      writeSuccessful = writeSuccessful && (std::fflush(f) == 0);
      if (!writeSuccessful)
        throw Ep128Emu::Exception("error writing output file");
      std::fclose(f);
      f = (std::FILE *) 0;
    }
    catch (...) {
      if (f) {
        std::fclose(f);
        std::remove(fileName);
      }
      throw;
    }
  }

}       // namespace Ep128ImgConv

