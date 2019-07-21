#pragma once

enum StatusEnum
{
	level = 0x01,
	expPts = 0x02,
	str = 0x03,
	dex = 0x04,
	con = 0x05,
	intel = 0x06,
	wit = 0x07,
	men = 0x08,
	currHP = 0x09,
	maxHP = 0x0a,
	currMP = 0x0b,
	maxMP = 0x0c,
	/*54	    public static final int SP = 0x0d,
	55	    public static final int CUR_LOAD = 0x0e,
	56	    public static final int MAX_LOAD = 0x0f,
	57
	58	    public static final int P_ATK = 0x11,
	59	    public static final int ATK_SPD = 0x12,
	60	    public static final int P_DEF = 0x13,
	61	    public static final int EVASION = 0x14,
	62	    public static final int ACCURACY = 0x15,
	63	    public static final int CRITICAL = 0x16,
	64	    public static final int M_ATK = 0x17,
	65	    public static final int CAST_SPD = 0x18,
	66	    public static final int M_DEF = 0x19,
	67	    public static final int PVP_FLAG = 0x1a,
	68	    public static final int KARMA = 0x1b,
	*/
	currCP = 0x21,
	maxCP = 0x22,
};