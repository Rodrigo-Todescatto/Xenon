// Copyright 2025 Xenon Emulator Project

#pragma once

// Xenos Registers by ID, multiply the ID by 4 to get the register offset.
enum class XeRegister {
  RBBM_RTL_RELEASE = 0x0000,
  RBBM_PATCH_RELEASE = 0x0001,
  RBBM_AUXILIARY_CONFIG = 0x0002,

  BIOS_0_SCRATCH = 0x0004,
  BIOS_1_SCRATCH = 0x0005,
  BIOS_2_SCRATCH = 0x0006,
  BIOS_3_SCRATCH = 0x0007,
  BIOS_4_SCRATCH = 0x0008,
  BIOS_5_SCRATCH = 0x0009,
  BIOS_6_SCRATCH = 0x000A,
  BIOS_7_SCRATCH = 0x000B,

  MH_MMU_CONFIG = 0x0040,
  MH_MMU_VA_RANGE = 0x0041,
  MH_MMU_PT_BASE = 0x0042,
  MH_MMU_PAGE_FAULT = 0x0043,
  MH_MMU_TRAN_ERROR = 0x0044,
  MH_MMU_INVALIDATE = 0x0045,
  MH_MMU_MPU_BASE = 0x0046,
  MH_MMU_MPU_END = 0x0047,
  BIF_PERFCOUNTER0_SELECT = 0x48,
  BIF_PERFCOUNTER0_HI = 0x49,
  BIF_PERFCOUNTER0_LOW = 0x4a,

  SCRATCH_REG0 = 0x578,
  SCRATCH_REG1 = 0x579,
  SCRATCH_REG2 = 0x57a,
  SCRATCH_REG3 = 0x57b,
  CALLBACK_ADDRESS = 0x57c,
  CALLBACK_CONTEXT = 0x57d,
  SCRATCH_REG6 = 0x57e,
  SCRATCH_REG7 = 0x57f,

  WAIT_UNTIL = 0x05c8,
  RBBM_ISYNC_CNTL = 0x5c9,

  MC0_PERFCOUNTER0_SELECT = 0x0815,
  MC0_PERFCOUNTER0_HI = 0x0816,
  MC0_PERFCOUNTER0_LOW = 0x0817,

  MC1_PERFCOUNTER0_SELECT = 0x0855,
  MC1_PERFCOUNTER0_HI = 0x0856,
  MC1_PERFCOUNTER0_LOW = 0x0857,

  HZ_PERFCOUNTER0_SELECT = 0x1004,
  HZ_PERFCOUNTER0_HI = 0x1005,
  HZ_PERFCOUNTER0_LOW = 0x1006,
  HZ_PERFCOUNTER1_SELECT = 0x1007,
  HZ_PERFCOUNTER1_HI = 0x1008,
  HZ_PERFCOUNTER1_LOW = 0x1009,

  D1MODE_MASTER_UPDATE_LOCK = 0x1838,

  D1GRPH_ENABLE = 0x1840,
  D1GRPH_CONTROL = 0x1841,
  D1GRPH_LUT_SEL = 0x1842,

  D1GRPH_PRIMARY_SURFACE_ADDRESS = 0x1844,

  D1GRPH_PITCH = 0x1848,
  D1GRPH_SURFACE_OFFSET_X = 0x1849,
  D1GRPH_SURFACE_OFFSET_Y = 0x184a,
  D1GRPH_X_START = 0x184b,
  D1GRPH_Y_START = 0x184c,
  D1GRPH_X_END = 0x184d,
  D1GRPH_Y_END = 0x184e,

  D1GRPH_UPDATE = 0x1851,
  D1GRPH_FLIP_CONTROL = 0x1852,

  RB_SURFACE_INFO = 0x2000,
  RB_COLOR_INFO = 0x2001,
  RB_DEPTH_INFO = 0x2002,
  RB_COLOR1_INFO = 0x2003,
  RB_COLOR2_INFO = 0x2004,
  RB_COLOR3_INFO = 0x2005,
  COHER_DEST_BASE_0 = 0x2006,
  COHER_DEST_BASE_1 = 0x2007,
  COHER_DEST_BASE_2 = 0x2008,
  COHER_DEST_BASE_3 = 0x2009,
  COHER_DEST_BASE_4 = 0x200A,
  COHER_DEST_BASE_5 = 0x200B,
  COHER_DEST_BASE_6 = 0x200C,
  COHER_DEST_BASE_7 = 0x200D,
  PA_SC_SCREEN_SCISSOR_TL = 0x200e,
  PA_SC_SCREEN_SCISSOR_BR = 0x200f,

  PA_SC_WINDOW_OFFSET = 0x2080,
  PA_SC_WINDOW_SCISSOR_TL = 0x2081,
  PA_SC_WINDOW_SCISSOR_BR = 0x2082,

  VGT_MAX_VTX_INDX = 0x2100,
  VGT_MIN_VTX_INDX = 0x2101,
  VGT_INDX_OFFSET = 0x2102,
  VGT_MULTI_PRIM_IB_RESET_INDX = 0x2103,
  RB_COLOR_MASK = 0x2104,
  RB_BLEND_RED = 0x2105,
  RB_BLEND_GREEN = 0x2106,
  RB_BLEND_BLUE = 0x2107,
  RB_BLEND_ALPHA = 0x2108,
  RB_FOG_COLOR_RED = 0x2109,
  RB_FOG_COLOR_GREEN = 0x210A,
  RB_FOG_COLOR_BLUE = 0x210B,
  RB_STENCILREFMASK_BF = 0x210C,
  RB_STENCILREFMASK = 0x210D,
  RB_ALPHA_REF = 0x210E,
  PA_CL_VPORT_XSCALE = 0x210F,
  PA_CL_VPORT_XOFFSET = 0x2110,
  PA_CL_VPORT_YSCALE = 0x2111,
  PA_CL_VPORT_YOFFSET = 0x2112,
  PA_CL_VPORT_ZSCALE = 0x2113,
  PA_CL_VPORT_ZOFFSET = 0x2114,

  SQ_PROGRAM_CNTL = 0x2180,
  SQ_CONTEXT_MISC = 0x2181,
  SQ_INTERPOLATOR_CNTL = 0x2182,
  SQ_WRAPPING_0 = 0x2183,
  SQ_WRAPPING_1 = 0x2184,

  VGT_EVENT_INITIATOR = 0x21F9,
  VGT_DMA_BASE = 0x21FA,
  VGT_DMA_SIZE = 0x21FB,
  VGT_DRAW_INITIATOR = 0x21FC,
  VGT_IMMED_DATA = 0x21FD,

  RB_DEPTHCONTROL = 0x2200,
  RB_BLENDCONTROL0 = 0x2201,
  RB_COLORCONTROL = 0x2202,
  RB_HIZCONTROL = 0x2203,
  PA_CL_CLIP_CNTL = 0x2204,
  PA_SU_SC_MODE_CNTL = 0x2205,
  PA_CL_VTE_CNTL = 0x2206,
  VGT_CURRENT_BIN_ID_MIN = 0x2207,
  RB_MODECONTROL = 0x2208,
  RB_BLENDCONTROL1 = 0x2209,
  RB_BLENDCONTROL2 = 0x220A,
  RB_BLENDCONTROL3 = 0x220B,

  PA_SU_POINT_SIZE = 0x2280,
  PA_SU_POINT_MINMAX = 0x2281,
  PA_SU_LINE_CNTL = 0x2282,
  PA_SC_LINE_STIPPLE = 0x2283,
  VGT_OUTPUT_PATH_CNTL = 0x2284,
  VGT_HOS_CNTL = 0x2285,
  VGT_HOS_MAX_TESS_LEVEL = 0x2286,
  VGT_HOS_MIN_TESS_LEVEL = 0x2287,
  VGT_HOS_REUSE_DEPTH = 0x2288,
  VGT_GROUP_PRIM_TYPE = 0x2289,
  VGT_GROUP_FIRST_DECR = 0x228A,
  VGT_GROUP_DECR = 0x228B,
  VGT_GROUP_VECT_0_CNTL = 0x228C,
  VGT_GROUP_VECT_1_CNTL = 0x228D,
  VGT_GROUP_VECT_0_FMT_CNTL = 0x228E,
  VGT_GROUP_VECT_1_FMT_CNTL = 0x228F,

  PA_SC_MPASS_PS_CNTL = 0x2292,
  PA_SC_VIZ_QUERY = 0x2293,
  VGT_ENHANCE = 0x2294,

  PA_SC_LINE_CNTL = 0x2300,
  PA_SC_AA_CONFIG = 0x2301,
  PA_SU_VTX_CNTL = 0x2302,
  PA_CL_GB_VERT_CLIP_ADJ = 0x2303,
  PA_CL_GB_VERT_DISC_ADJ = 0x2304,
  PA_CL_GB_HORZ_CLIP_ADJ = 0x2305,
  PA_CL_GB_HORZ_DISC_ADJ = 0x2306,
  SQ_VS_CONST = 0x2307,
  SQ_PS_CONST = 0x2308,
  SQ_DEBUG_MISC_0 = 0x2309,
  SQ_DEBUG_MISC_1 = 0x230A,

  PA_SC_AA_MASK = 0x2312,

  SQ_CF_PROGRAM_SIZE = 0x2315,
  VGT_VERTEX_REUSE_BLOCK_CNTL = 0x2316,
  VGT_OUT_DEALLOC_CNTL = 0x2317,
  RB_COPY_CONTROL = 0x2318,
  RB_COPY_DEST_BASE = 0x2319,
  RB_COPY_DEST_PITCH = 0x231A,
  RB_COPY_DEST_INFO = 0x231B,
  RB_HIZ_CLEAR = 0x231C,
  RB_DEPTH_CLEAR = 0x231D,
  RB_COLOR_CLEAR = 0x231E,
  RB_COLOR_CLEAR_LO = 0x231F,
  RB_COPY_FUNC = 0x2320,
  RB_COPY_REF = 0x2321,
  RB_COPY_MASK = 0x2322,
  RB_COPY_SURFACE_SLICE = 0x2323,
  RB_SAMPLE_COUNT_CTL = 0x2324,
  RB_SAMPLE_COUNT_ADDR = 0x2325
};
