// Copyright (c) 2012- PPSSPP Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0 or later versions.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official git repository and contact information can be found at
// https://github.com/hrydgard/ppsspp and http://www.ppsspp.org/.

#pragma once

#include "../Globals.h"
#include "ge_constants.h"

struct GPUgstate
{
	// Getting rid of this ugly union in favor of the accessor functions
	// might be a good idea....
	union
	{
		u32 cmdmem[256];
		struct
		{
			u32 nop,
				vaddr,
				iaddr,
				pad00,
				prim,
				bezier,
				spline,
				boundBox,
				jump,
				bjump,
				call,
				ret,
				end,
				pad01,
				signal,
				finish,
				base,
				pad02,
				vertType,
				offsetAddr,
				origin,
				region1,
				region2,
				lightingEnable,
				lightEnable[4],
				clipEnable,
				cullfaceEnable,
				textureMapEnable,
				fogEnable,
				ditherEnable,
				alphaBlendEnable,
				alphaTestEnable,
				zTestEnable,
				stencilTestEnable,
				antiAliasEnable,
				patchCullEnable,
				colorTestEnable,
				logicOpEnable,
				pad03,
				boneMatrixNumber,
				boneMatrixData,
				morphwgt[8], //dont use
				pad04[2],
				patchdivision,
				patchprimitive,
				patchfacing,
				pad04_a,

				worldmtxnum,  // 0x3A
				worldmtxdata, // 0x3B
				viewmtxnum,   // 0x3C
				viewmtxdata,  // 0x3D
				projmtxnum,   // 0x3E
				projmtxdata,  // 0x3F
				texmtxnum,    // 0x40
				texmtxdata,   // 0x41

				viewportx1,           // 0x42
				viewporty1,           // 0x43
				viewportz1,           // 0x44
				viewportx2,           // 0x45
				viewporty2,           // 0x46
				viewportz2,           // 0x47
				texscaleu,            // 0x48
				texscalev,            // 0x49
				texoffsetu,           // 0x4A
				texoffsetv,           // 0x4B
				offsetx,              // 0x4C
				offsety,              // 0x4D
				pad111[2],
				shademodel,           // 0x50
				reversenormals,       // 0x51
				pad222,
				materialupdate,       // 0x53
				materialemissive,     // 0x54
				materialambient,      // 0x55
				materialdiffuse,      // 0x56
				materialspecular,     // 0x57
				materialalpha,        // 0x58
				pad333[2],
				materialspecularcoef, // 0x5B
				ambientcolor,         // 0x5C
				ambientalpha,         // 0x5D
				lmode,                // 0x5E
				ltype[4],             // 0x5F-0x62
				lpos[12],             // 0x63-0x6E
				ldir[12],             // 0x6F-0x7A
				latt[12],             // 0x7B-0x86
				lconv[4],             // 0x87-0x8A
				lcutoff[4],           // 0x8B-0x8E
				lcolor[12],           // 0x8F-0x9A
				cullmode,             // 0x9B
				fbptr,                // 0x9C
				fbwidth,              // 0x9D
				zbptr,                // 0x9E
				zbwidth,              // 0x9F
				texaddr[8],           // 0xA0-0xA7
				texbufwidth[8],       // 0xA8-0xAF
				clutaddr,             // 0xB0
				clutaddrupper,        // 0xB1
				transfersrc,          // 0xB2
				transfersrcw,         // 0xB3
				transferdst,          // 0xB4
				transferdstw,         // 0xB5
				padxxx[2],
				texsize[8],           // 0xB8-BF
				texmapmode,           // 0xC0
				texshade,             // 0xC1
				texmode,              // 0xC2
				texformat,            // 0xC3
				loadclut,             // 0xC4
				clutformat,           // 0xC5
				texfilter,            // 0xC6
				texwrap,              // 0xC7
				texlevel,             // 0xC8
				texfunc,              // 0xC9
				texenvcolor,          // 0xCA
				texflush,             // 0xCB
				texsync,              // 0xCC
				fog1,                 // 0xCD
				fog2,                 // 0xCE
				fogcolor,             // 0xCF
				texlodslope,          // 0xD0
				padxxxxxx,            // 0xD1
				framebufpixformat,    // 0xD2
				clearmode,            // 0xD3
				scissor1,
				scissor2,
				minz,
				maxz,
				colortest,
				colorref,
				colormask,
				alphatest,
				stenciltest,
				stencilop,
				ztestfunc,
				blend,
				blendfixa,
				blendfixb,
				dith1,
				dith2,
				dith3,
				dith4,
				lop,                  // 0xE6
				zmsk,
				pmskc,
				pmska,
				transferstart,
				transfersrcpos,
				transferdstpos,
				pad99,
				transfersize;  // 0xEE

			u32 pad05[0xFF- 0xEE];
		};
	};

	float worldMatrix[12];
	float viewMatrix[12];
	float projMatrix[16];
	float tgenMatrix[12];
	float boneMatrix[12 * 8];  // Eight bone matrices.

	// Pixel Pipeline
	bool isModeClear()   const { return clearmode & 1; }
	bool isFogEnabled() const { return fogEnable & 1; }
	
	// Cull 
	bool isCullEnabled() const { return cullfaceEnable & 1; }
	int getCullMode()   const { return cullmode & 1; }
	bool isClearModeDepthWriteEnabled() const { return (clearmode&0x400) != 0; }
	bool isClearModeColorMask() const { return (clearmode&0x100) != 0; }
	bool isClearModeAlphaMask() const { return (clearmode&0x200) != 0; }
	
	// Blend
	int getBlendFuncA() const { return blend & 0xF; }
	u32 getFixA() const { return blendfixa & 0xFFFFFF; }
	u32 getFixB() const { return blendfixb & 0xFFFFFF; }
	int getBlendFuncB() const { return (blend >> 4) & 0xF; }
	int getBlendEq()    const { return (blend >> 8) & 0x7; }
	bool isAlphaBlendEnabled() const { return alphaBlendEnable & 1; }
	
	// Dither
	bool isDitherEnabled() const { return ditherEnable & 1; }

	// Color Mask
	u32 getColorMask() const { return (pmskc & 0xFFFFFF) | ((pmska & 0xFF) << 24); }
	bool isLogicOpEnabled() const { return logicOpEnable & 1; }
	GELogicOp getLogicOp() const { return static_cast<GELogicOp>(lop & 0xF); }
	
	// Depth Test
	bool isDepthTestEnabled() const { return zTestEnable & 1; }
	bool isDepthWriteEnabled() const { return !(zmsk & 1); }
	int getDepthTestFunc() const { return ztestfunc & 0x7; }
	u16 getDepthRangeMin() const { return minz & 0xFFFF; }
	u16 getDepthRangeMax() const { return maxz & 0xFFFF; }
	
	// Stencil Test
	bool isStencilTestEnabled() const { return stencilTestEnable & 1; }
	GEComparison getStencilTestFunction() const { return static_cast<GEComparison>(stenciltest & 0x7); }
	int getStencilTestRef() const { return (stenciltest>>8) & 0xFF; }
	int getStencilTestMask() const { return (stenciltest>>16) & 0xFF; }
	GEStencilOp getStencilOpSFail() const { return static_cast<GEStencilOp>(stencilop & 0x7); }
	GEStencilOp getStencilOpZFail() const { return static_cast<GEStencilOp>((stencilop>>8) & 0x7); }
	GEStencilOp getStencilOpZPass() const { return static_cast<GEStencilOp>((stencilop>>16) & 0x7); }

	// Alpha Test
	bool isAlphaTestEnabled() const { return alphaTestEnable & 1; }
	GEComparison getAlphaTestFunction() { return static_cast<GEComparison>(alphatest & 0x7); }
	int getAlphaTestRef() const { return (alphatest >> 8) & 0xFF; }
	int getAlphaTestMask() const { return (alphatest >> 16) & 0xFF; }
	
	// Color Test
	bool isColorTestEnabled() const { return colorTestEnable & 1; }
	GEComparison getColorTestFunction() { return static_cast<GEComparison>(colortest & 0x3); }
	u32 getColorTestRef() const { return colorref & 0xFFFFFF; }
	u32 getColorTestMask() const { return colormask & 0xFFFFFF; }

	// Texturing
	int getTextureWidth(int level) const { return 1 << (texsize[level] & 0xf);}
	int getTextureHeight(int level) const { return 1 << ((texsize[level] >> 8) & 0xf);}
	bool isTextureMapEnabled() const { return textureMapEnable & 1; }
	GETexFunc getTextureFunction() const { return static_cast<GETexFunc>(texfunc & 0x7); }
	bool isColorDoublingEnabled() const { return (texfunc & 0x10000) != 0; }
	GETextureFormat getTextureFormat() const { return static_cast<GETextureFormat>(texformat & 0xF); }
	bool isTextureFormatIndexed() const { return (texformat & 4) != 0; } // GE_TFMT_CLUT4 - GE_TFMT_CLUT32 are 0b1xx.
	int getTextureEnvColR() const { return texenvcolor&0xFF; }
	int getTextureEnvColG() const { return (texenvcolor>>8)&0xFF; }
	int getTextureEnvColB() const { return (texenvcolor>>16)&0xFF; }
	GEPaletteFormat getClutPaletteFormat() { return static_cast<GEPaletteFormat>(clutformat & 3); }
	int getClutIndexShift() const { return (clutformat >> 2) & 0x1F; }
	int getClutIndexMask() const { return (clutformat >> 8) & 0xFF; }
	int getClutIndexStartPos() const { return ((clutformat >> 16) & 0x1F) << 4; }
	bool isClutIndexSimple() const { return (clutformat & ~3) == 0xC500FF00; } // Meaning, no special mask, shift, or start pos.

	// Lighting
	bool isLightingEnabled() const { return lightingEnable & 1; }
	bool isLightChanEnabled(int chan) const { return lightEnable[chan] & 1; }
	GELightComputation getLightComputation(int chan) const { return static_cast<GELightComputation>(ltype[chan] & 0x3); }
	bool isUsingPoweredDiffuseLight(int chan) const { return getLightComputation(chan) == GE_LIGHTCOMP_BOTHWITHPOWDIFFUSE; }
	bool isUsingSpecularLight(int chan) const { return getLightComputation(chan) != GE_LIGHTCOMP_ONLYDIFFUSE; }
	bool isUsingSecondaryColor() const { return lmode & 1; }
	GELightType getLightType(int chan) const { return static_cast<GELightType>((ltype[chan] >> 8) & 3); }
	bool isDirectionalLight(int chan) const { return getLightType(chan) == GE_LIGHTTYPE_DIRECTIONAL; }
	bool isPointLight(int chan) const { return getLightType(chan) == GE_LIGHTTYPE_POINT; }
	bool isSpotLight(int chan) const { return getLightType(chan) == GE_LIGHTTYPE_SPOT; }
	unsigned int getAmbientR() const { return ambientcolor&0xFF; }
	unsigned int getAmbientG() const { return (ambientcolor>>8)&0xFF; }
	unsigned int getAmbientB() const { return (ambientcolor>>16)&0xFF; }
	unsigned int getAmbientA() const { return ambientalpha&0xFF; }
	unsigned int getMaterialAmbientR() const { return materialambient&0xFF; }
	unsigned int getMaterialAmbientG() const { return (materialambient>>8)&0xFF; }
	unsigned int getMaterialAmbientB() const { return (materialambient>>16)&0xFF; }
	unsigned int getMaterialAmbientA() const { return materialalpha&0xFF; }
	unsigned int getMaterialDiffuseR() const { return materialdiffuse&0xFF; }
	unsigned int getMaterialDiffuseG() const { return (materialdiffuse>>8)&0xFF; }
	unsigned int getMaterialDiffuseB() const { return (materialdiffuse>>16)&0xFF; }
	unsigned int getMaterialEmissiveR() const { return materialemissive&0xFF; }
	unsigned int getMaterialEmissiveG() const { return (materialemissive>>8)&0xFF; }
	unsigned int getMaterialEmissiveB() const { return (materialemissive>>16)&0xFF; }
	unsigned int getMaterialSpecularR() const { return materialspecular&0xFF; }
	unsigned int getMaterialSpecularG() const { return (materialspecular>>8)&0xFF; }
	unsigned int getMaterialSpecularB() const { return (materialspecular>>16)&0xFF; }
	unsigned int getLightAmbientColorR(int chan) const { return lcolor[chan*3]&0xFF; }
	unsigned int getLightAmbientColorG(int chan) const { return (lcolor[chan*3]>>8)&0xFF; }
	unsigned int getLightAmbientColorB(int chan) const { return (lcolor[chan*3]>>16)&0xFF; }
	unsigned int getDiffuseColorR(int chan) const { return lcolor[1+chan*3]&0xFF; }
	unsigned int getDiffuseColorG(int chan) const { return (lcolor[1+chan*3]>>8)&0xFF; }
	unsigned int getDiffuseColorB(int chan) const { return (lcolor[1+chan*3]>>16)&0xFF; }
	unsigned int getSpecularColorR(int chan) const { return lcolor[2+chan*3]&0xFF; }
	unsigned int getSpecularColorG(int chan) const { return (lcolor[2+chan*3]>>8)&0xFF; }
	unsigned int getSpecularColorB(int chan) const { return (lcolor[2+chan*3]>>16)&0xFF; }

	// UV gen
	int getUVGenMode() const { return texmapmode & 3;}   // 2 bits
	int getUVProjMode() const { return (texmapmode >> 8) & 3;}   // 2 bits
	int getUVLS0() const { return texshade & 0x3; }  // 2 bits
	int getUVLS1() const { return (texshade >> 8) & 0x3; }  // 2 bits
	int getScissorX1() const { return scissor1 & 0x3FF; }
	int getScissorY1() const { return (scissor1 >> 10) & 0x3FF; }
	int getScissorX2() const { return scissor2 & 0x3FF; }
	int getScissorY2() const { return (scissor2 >> 10) & 0x3FF; }
	int getRegionX1() const { return region1 & 0x3FF; }
	int getRegionY1() const { return (region1 >> 10) & 0x3FF; }
	int getRegionX2() const { return (region2 & 0x3FF); }
	int getRegionY2() const { return ((region2 >> 10) & 0x3FF); }

	// Vertex type
	bool isModeThrough() const { return (vertType & GE_VTYPE_THROUGH) != 0; }
	int getWeightMask() const { return vertType & GE_VTYPE_WEIGHT_MASK; }
	int getNumBoneWeights() const { return 1 + ((vertType & GE_VTYPE_WEIGHTCOUNT_MASK) >> GE_VTYPE_WEIGHTCOUNT_SHIFT); }

// Real data in the context ends here
};

enum SkipDrawReasonFlags {
	SKIPDRAW_SKIPFRAME = 1,
	SKIPDRAW_NON_DISPLAYED_FB = 2,   // Skip drawing to FBO:s that have not been displayed.
	SKIPDRAW_BAD_FB_TEXTURE = 4,
};

// The rest is cached simplified/converted data for fast access.
// Does not need to be saved when saving/restoring context.

struct UVScale {
	float uScale, vScale;
	float uOff, vOff;
};

struct GPUStateCache
{
	u32 vertexAddr;
	u32 indexAddr;

	u32 offsetAddr;

	bool textureChanged;
	bool textureFullAlpha;
	bool framebufChanged;

	int skipDrawReason;

	UVScale uv;
	bool flipTexture;

	float zMin, zMax;
	float lightpos[4][3];
	float lightdir[4][3];
	float lightatt[4][3];
	float lightColor[3][4][3];  // Ambient Diffuse Specular
	float lightangle[4]; // spotlight cone angle (cosine)
	float lightspotCoef[4]; // spotlight dropoff
	float morphWeights[8];

	u32 curTextureWidth;
	u32 curTextureHeight;
	u32 actualTextureHeight;

	float vpWidth;
	float vpHeight;

	u32 curRTWidth;
	u32 curRTHeight;

	u32 getRelativeAddress(u32 data) const;
	int gpuVendor;
};

// TODO: Implement support for these.
struct GPUStatistics {
	void Reset() {
		// Never add a vtable :)
		memset(this, 0, sizeof(*this));
	}
	void ResetFrame() {
		numDrawCalls = 0;
		numCachedDrawCalls = 0;
		numVertsSubmitted = 0;
		numCachedVertsDrawn = 0;
		numUncachedVertsDrawn = 0;
		numTrackedVertexArrays = 0;
		numTextureInvalidations = 0;
		numTextureSwitches = 0;
		numShaderSwitches = 0;
		numFlushes = 0;
		numTexturesDecoded = 0;
		msProcessingDisplayLists = 0;
		vertexGPUCycles = 0;
		otherGPUCycles = 0;
	}

	// Per frame statistics
	int numDrawCalls;
	int numCachedDrawCalls;
	int numFlushes;
	int numVertsSubmitted;
	int numCachedVertsDrawn;
	int numUncachedVertsDrawn;
	int numTrackedVertexArrays;
	int numTextureInvalidations;
	int numTextureSwitches;
	int numShaderSwitches;
	int numTexturesDecoded;
	double msProcessingDisplayLists;
	int vertexGPUCycles;
	int otherGPUCycles;

	// Total statistics, updated by the GPU core in UpdateStats
	int numVBlanks;
	int numFlips;
	int numTextures;
	int numVertexShaders;
	int numFragmentShaders;
	int numShaders;
	int numFBOs;
};

void GPU_Init();
void GPU_Shutdown();

void InitGfxState();
void ShutdownGfxState();
void ReapplyGfxState();

// PSP uses a curious 24-bit float - it's basically the top 24 bits of a regular IEEE754 32-bit float.
// This is used for light positions, transform matrices, you name it.
inline float getFloat24(unsigned int data)
{
	data <<= 8;
	float f;
	memcpy(&f, &data, 4);
	return f;
}

// in case we ever want to generate PSP display lists...
inline unsigned int toFloat24(float f) {
	unsigned int i;
	memcpy(&i, &f, 4);
	return i >> 8;
}

class GPUInterface;

extern GPUgstate gstate;
extern GPUStateCache gstate_c;
extern GPUInterface *gpu;
extern GPUStatistics gpuStats;

inline u32 GPUStateCache::getRelativeAddress(u32 data) const {
	u32 baseExtended = ((gstate.base & 0x0F0000) << 8) | data;
	return (gstate_c.offsetAddr + baseExtended) & 0x0FFFFFFF;
}
