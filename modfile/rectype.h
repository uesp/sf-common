#ifndef __SFWIKI_RECTYPE_H
#define __SFWIKI_RECTYPE_H


#include "moddefs.h"
#include "common/file.h"


namespace sfwiki {

	 /* Name field size */
	const int RECTYPE_SIZE = 4;

#pragma pack(push, 1)

  /* Standard record/sub-record name field */
	union rectype_t {

		char  Name[RECTYPE_SIZE];
		dword Value;

		/* Constructors */
		rectype_t(const dword Val = 0) { Value = Val; }
		rectype_t(const char* pString) { Value = *(dword *)pString; }

		/* Conversion Operators */
		operator const char* (void) const { return (Name); }
		operator const dword(void) const { return (Value); }

		const rectype_t& operator= (const char* pString)
		{
			Value = *(const dword *)pString;
			Name[0] = ::toupper(Name[0]);
			Name[1] = ::toupper(Name[1]);
			Name[2] = ::toupper(Name[2]);
			Name[3] = ::toupper(Name[3]);
			return (*this);
		}

		const rectype_t& operator= (const dword InValue)
		{
			Value = InValue; return (*this);
		}

		bool operator <(const rectype_t &s)
		{
			return strnicmp(this->Name, s.Name, RECTYPE_SIZE) < 0;
		}

	};

#pragma pack(pop)

	


	
	  /* Special names */
	extern const rectype_t NAME_NULL;
	extern const rectype_t NAME_all;
	extern const rectype_t NAME_SCRI;

	/* Special group name */
	extern const rectype_t NAME_GRUP;

	/* Known record names */
	extern const rectype_t NAME_AACT;
	extern const rectype_t NAME_ACHR;
	extern const rectype_t NAME_ACTI;
	extern const rectype_t NAME_ADDN;
	extern const rectype_t NAME_ALCH;
	extern const rectype_t NAME_AMMO;
	extern const rectype_t NAME_ANIO;
	extern const rectype_t NAME_APPA;
	extern const rectype_t NAME_ARMA;
	extern const rectype_t NAME_ARMO;
	extern const rectype_t NAME_ARTO;
	extern const rectype_t NAME_ASPC;
	extern const rectype_t NAME_ASTP;
	extern const rectype_t NAME_AVIF;
	extern const rectype_t NAME_BIOM;
	extern const rectype_t NAME_BOOK;
	extern const rectype_t NAME_BPTD;
	extern const rectype_t NAME_CAMS;
	extern const rectype_t NAME_CELL;
	extern const rectype_t NAME_CLAS;
	extern const rectype_t NAME_CLFM;
	extern const rectype_t NAME_CLMT;
	extern const rectype_t NAME_COBJ;
	extern const rectype_t NAME_COLL;
	extern const rectype_t NAME_CONT;
	extern const rectype_t NAME_CPTH;
	extern const rectype_t NAME_CSTY;
	extern const rectype_t NAME_DEBR;
	extern const rectype_t NAME_DIAL;
	extern const rectype_t NAME_DLBR;
	extern const rectype_t NAME_DLVW;
	extern const rectype_t NAME_DOBJ;
	extern const rectype_t NAME_DOOR;
	extern const rectype_t NAME_DUAL;
	extern const rectype_t NAME_ECZN;
	extern const rectype_t NAME_EFSH;
	extern const rectype_t NAME_ENCH;
	extern const rectype_t NAME_EQUP;
	extern const rectype_t NAME_EXPL;
	extern const rectype_t NAME_EYES;
	extern const rectype_t NAME_FACT;
	extern const rectype_t NAME_FLOR;
	extern const rectype_t NAME_FLST;
	extern const rectype_t NAME_FSTP;
	extern const rectype_t NAME_FSTS;
	extern const rectype_t NAME_FURN;
	extern const rectype_t NAME_GLOB;
	extern const rectype_t NAME_GMST;
	extern const rectype_t NAME_GRAS;
	extern const rectype_t NAME_HAZD;
	extern const rectype_t NAME_HDPT;
	extern const rectype_t NAME_IAD;
	extern const rectype_t NAME_IDLE;
	extern const rectype_t NAME_IDLM;
	extern const rectype_t NAME_IMAD;
	extern const rectype_t NAME_IMGS;
	extern const rectype_t NAME_INFO;
	extern const rectype_t NAME_INGR;
	extern const rectype_t NAME_IPCT;
	extern const rectype_t NAME_IPDS;
	extern const rectype_t NAME_KEYM;
	extern const rectype_t NAME_KYWD;
	extern const rectype_t NAME_LAND;
	extern const rectype_t NAME_LCRT;
	extern const rectype_t NAME_LCTN;
	extern const rectype_t NAME_LGTM;
	extern const rectype_t NAME_LIGH;
	extern const rectype_t NAME_LSCR;
	extern const rectype_t NAME_LTEX;
	extern const rectype_t NAME_LVLI;
	extern const rectype_t NAME_LVLN;
	extern const rectype_t NAME_LVSP;
	extern const rectype_t NAME_MATO;
	extern const rectype_t NAME_MATT;
	extern const rectype_t NAME_MESG;
	extern const rectype_t NAME_MGEF;
	extern const rectype_t NAME_MISC;
	extern const rectype_t NAME_MOVT;
	extern const rectype_t NAME_MSTT;
	extern const rectype_t NAME_MUSC;
	extern const rectype_t NAME_MUST;
	extern const rectype_t NAME_NAVI;
	extern const rectype_t NAME_NAVM;
	extern const rectype_t NAME_NPC_;
	extern const rectype_t NAME_OTFT;
	extern const rectype_t NAME_PACK;
	extern const rectype_t NAME_PERK;
	extern const rectype_t NAME_PGRE;
	extern const rectype_t NAME_PHZD;
	extern const rectype_t NAME_PROJ;
	extern const rectype_t NAME_QUST;
	extern const rectype_t NAME_RACE;
	extern const rectype_t NAME_REFR;
	extern const rectype_t NAME_REGN;
	extern const rectype_t NAME_RELA;
	extern const rectype_t NAME_REVB;
	extern const rectype_t NAME_RFCT;
	extern const rectype_t NAME_SCEN;
	extern const rectype_t NAME_SCRL;
	extern const rectype_t NAME_SHOU;
	extern const rectype_t NAME_SLGM;
	extern const rectype_t NAME_SMBN;
	extern const rectype_t NAME_SMEN;
	extern const rectype_t NAME_SMQN;
	extern const rectype_t NAME_SNCT;
	extern const rectype_t NAME_SNDR;
	extern const rectype_t NAME_SOPM;
	extern const rectype_t NAME_SOUN;
	extern const rectype_t NAME_SPEL;
	extern const rectype_t NAME_SPGD;
	extern const rectype_t NAME_STAT;
	extern const rectype_t NAME_STDT;
	extern const rectype_t NAME_SUNP;
	extern const rectype_t NAME_TACT;
	extern const rectype_t NAME_TES4;
	extern const rectype_t NAME_TREE;
	extern const rectype_t NAME_TXST;
	extern const rectype_t NAME_VTYP;
	extern const rectype_t NAME_WATR;
	extern const rectype_t NAME_WEAP;
	extern const rectype_t NAME_WOOP;
	extern const rectype_t NAME_WRLD;
	extern const rectype_t NAME_WTHR;


	/* Known sub-records */
	extern const rectype_t NAME_00TX;
	extern const rectype_t NAME_10TX;
	extern const rectype_t NAME_20TX;
	extern const rectype_t NAME_30TX;
	extern const rectype_t NAME_40TX;
	extern const rectype_t NAME_50TX;
	extern const rectype_t NAME_60TX;
	extern const rectype_t NAME_70TX;
	extern const rectype_t NAME_80TX;
	extern const rectype_t NAME_90TX;
	extern const rectype_t NAME_A0TX;
	extern const rectype_t NAME_ACBS;
	extern const rectype_t NAME_AHCF;
	extern const rectype_t NAME_AHCM;
	extern const rectype_t NAME_AIAD;
	extern const rectype_t NAME_AIDT;
	extern const rectype_t NAME_ALCA;
	extern const rectype_t NAME_ALCL;
	extern const rectype_t NAME_ALCO;
	extern const rectype_t NAME_ALDN;
	extern const rectype_t NAME_ALEA;
	extern const rectype_t NAME_ALED;
	extern const rectype_t NAME_ALEQ;
	extern const rectype_t NAME_ALFA;
	extern const rectype_t NAME_ALFC;
	extern const rectype_t NAME_ALFD;
	extern const rectype_t NAME_ALFE;
	extern const rectype_t NAME_ALFI;
	extern const rectype_t NAME_ALFL;
	extern const rectype_t NAME_ALFR;
	extern const rectype_t NAME_ALID;
	extern const rectype_t NAME_ALLS;
	extern const rectype_t NAME_ALNA;
	extern const rectype_t NAME_ALNT;
	extern const rectype_t NAME_ALPC;
	extern const rectype_t NAME_ALRT;
	extern const rectype_t NAME_ALSP;
	extern const rectype_t NAME_ALST;
	extern const rectype_t NAME_ALUA;
	extern const rectype_t NAME_ANAM;
	extern const rectype_t NAME_ATKD;
	extern const rectype_t NAME_ATKE;
	extern const rectype_t NAME_ATKR;
	extern const rectype_t NAME_ATXT;
	extern const rectype_t NAME_AVFL;
	extern const rectype_t NAME_AVSK;
	extern const rectype_t NAME_B0TX;
	extern const rectype_t NAME_BAMT;
	extern const rectype_t NAME_BFCB;
	extern const rectype_t NAME_BIAD;
	extern const rectype_t NAME_BIDS;
	extern const rectype_t NAME_BNAM;
	extern const rectype_t NAME_BODT;
	extern const rectype_t NAME_BPND;
	extern const rectype_t NAME_BPNI;
	extern const rectype_t NAME_BPNN;
	extern const rectype_t NAME_BPNT;
	extern const rectype_t NAME_BPTN;
	extern const rectype_t NAME_BTXT;
	extern const rectype_t NAME_C0TX;
	extern const rectype_t NAME_CIAD;
	extern const rectype_t NAME_CIS1;
	extern const rectype_t NAME_CIS2;
	extern const rectype_t NAME_CITC;
	extern const rectype_t NAME_CNAM;
	extern const rectype_t NAME_CNTO;
	extern const rectype_t NAME_COCT;
	extern const rectype_t NAME_COED;
	extern const rectype_t NAME_CRDT;
	extern const rectype_t NAME_CRGR;
	extern const rectype_t NAME_CRIF;
	extern const rectype_t NAME_CRVA;
	extern const rectype_t NAME_CSCR;
	extern const rectype_t NAME_CSDC;
	extern const rectype_t NAME_CSDI;
	extern const rectype_t NAME_CSDT;
	extern const rectype_t NAME_CSFL;
	extern const rectype_t NAME_CSGD;
	extern const rectype_t NAME_CSLR;
	extern const rectype_t NAME_CSMD;
	extern const rectype_t NAME_CSME;
	extern const rectype_t NAME_CTDA;
	extern const rectype_t NAME_D0TX;
	extern const rectype_t NAME_DALC;
	extern const rectype_t NAME_DATA;
	extern const rectype_t NAME_DEMO;
	extern const rectype_t NAME_DESC;
	extern const rectype_t NAME_DEST;
	extern const rectype_t NAME_DEVA;
	extern const rectype_t NAME_DFTF;
	extern const rectype_t NAME_DFTM;
	extern const rectype_t NAME_DIAD;
	extern const rectype_t NAME_DMAX;
	extern const rectype_t NAME_DMDL;
	extern const rectype_t NAME_DMDS;
	extern const rectype_t NAME_DMDT;
	extern const rectype_t NAME_DMIN;
	extern const rectype_t NAME_DNAM;
	extern const rectype_t NAME_DODT;
	extern const rectype_t NAME_DOFT;
	extern const rectype_t NAME_DPLT;
	extern const rectype_t NAME_DSTD;
	extern const rectype_t NAME_DSTF;
	extern const rectype_t NAME_E0TX;
	extern const rectype_t NAME_EAMT;
	extern const rectype_t NAME_ECOR;
	extern const rectype_t NAME_EDID;
	extern const rectype_t NAME_EFID;
	extern const rectype_t NAME_EFIT;
	extern const rectype_t NAME_EIAD;
	extern const rectype_t NAME_EITM;
	extern const rectype_t NAME_ENAM;
	extern const rectype_t NAME_ENIT;
	extern const rectype_t NAME_EPF2;
	extern const rectype_t NAME_EPF3;
	extern const rectype_t NAME_EPFD;
	extern const rectype_t NAME_EPFT;
	extern const rectype_t NAME_ESCE;
	extern const rectype_t NAME_ETYP;
	extern const rectype_t NAME_F0TX;
	extern const rectype_t NAME_FCHT;
	extern const rectype_t NAME_FIAD;
	extern const rectype_t NAME_FLMV;
	extern const rectype_t NAME_FLTR;
	extern const rectype_t NAME_FLTV;
	extern const rectype_t NAME_FNAM;
	extern const rectype_t NAME_FNMK;
	extern const rectype_t NAME_FNPR;
	extern const rectype_t NAME_FPRT;
	extern const rectype_t NAME_FTSF;
	extern const rectype_t NAME_FTSM;
	extern const rectype_t NAME_FTST;
	extern const rectype_t NAME_FULL;
	extern const rectype_t NAME_G0TX;
	extern const rectype_t NAME_GIAD;
	extern const rectype_t NAME_GNAM;
	extern const rectype_t NAME_H0TX;
	extern const rectype_t NAME_HCLF;
	extern const rectype_t NAME_HEAD;
	extern const rectype_t NAME_HEDR;
	extern const rectype_t NAME_HIAD;
	extern const rectype_t NAME_HNAM;
	extern const rectype_t NAME_HTID;
	extern const rectype_t NAME_I0TX;
	extern const rectype_t NAME_ICO2;
	extern const rectype_t NAME_ICON;
	extern const rectype_t NAME_IDLA;
	extern const rectype_t NAME_IDLC;
	extern const rectype_t NAME_IDLF;
	extern const rectype_t NAME_IDLT;
	extern const rectype_t NAME_IIAD;
	extern const rectype_t NAME_IMSP;
	extern const rectype_t NAME_INAM;
	extern const rectype_t NAME_INDX;
	extern const rectype_t NAME_INTV;
	extern const rectype_t NAME_ITXT;
	extern const rectype_t NAME_J0TX;
	extern const rectype_t NAME_JAIL;
	extern const rectype_t NAME_JIAD;
	extern const rectype_t NAME_JNAM;
	extern const rectype_t NAME_JOUT;
	extern const rectype_t NAME_K0TX;
	extern const rectype_t NAME_KIAD;
	extern const rectype_t NAME_KNAM;
	extern const rectype_t NAME_KSIZ;
	extern const rectype_t NAME_KWDA;
	extern const rectype_t NAME_L0TX;
	extern const rectype_t NAME_LCEC;
	extern const rectype_t NAME_LCEP;
	extern const rectype_t NAME_LCID;
	extern const rectype_t NAME_LCPR;
	extern const rectype_t NAME_LCSR;
	extern const rectype_t NAME_LCUN;
	extern const rectype_t NAME_LIAD;
	extern const rectype_t NAME_LLCT;
	extern const rectype_t NAME_LNAM;
	extern const rectype_t NAME_LTMP;
	extern const rectype_t NAME_LVLD;
	extern const rectype_t NAME_LVLF;
	extern const rectype_t NAME_LVLG;
	extern const rectype_t NAME_LVLO;
	extern const rectype_t NAME_MAST;
	extern const rectype_t NAME_MCHT;
	extern const rectype_t NAME_MDOB;
	extern const rectype_t NAME_MHDT;
	extern const rectype_t NAME_MIAD;
	extern const rectype_t NAME_MICO;
	extern const rectype_t NAME_MNAM;
	extern const rectype_t NAME_MO2S;
	extern const rectype_t NAME_MO2T;
	extern const rectype_t NAME_MO3S;
	extern const rectype_t NAME_MO3T;
	extern const rectype_t NAME_MO4S;
	extern const rectype_t NAME_MO4T;
	extern const rectype_t NAME_MO5T;
	extern const rectype_t NAME_MOD2;
	extern const rectype_t NAME_MOD3;
	extern const rectype_t NAME_MOD4;
	extern const rectype_t NAME_MOD5;
	extern const rectype_t NAME_MODL;
	extern const rectype_t NAME_MODS;
	extern const rectype_t NAME_MODT;
	extern const rectype_t NAME_MPAI;
	extern const rectype_t NAME_MPAV;
	extern const rectype_t NAME_MPRT;
	extern const rectype_t NAME_MTNM;
	extern const rectype_t NAME_MTYP;
	extern const rectype_t NAME_NAM0;
	extern const rectype_t NAME_NAM1;
	extern const rectype_t NAME_NAM2;
	extern const rectype_t NAME_NAM3;
	extern const rectype_t NAME_NAM4;
	extern const rectype_t NAME_NAM5;
	extern const rectype_t NAME_NAM6;
	extern const rectype_t NAME_NAM7;
	extern const rectype_t NAME_NAM8;
	extern const rectype_t NAME_NAM9;
	extern const rectype_t NAME_NAMA;
	extern const rectype_t NAME_NAME;
	extern const rectype_t NAME_NEXT;
	extern const rectype_t NAME_NIAD;
	extern const rectype_t NAME_NNAM;
	extern const rectype_t NAME_NVER;
	extern const rectype_t NAME_NVMI;
	extern const rectype_t NAME_NVNM;
	extern const rectype_t NAME_NVPP;
	extern const rectype_t NAME_OBND;
	extern const rectype_t NAME_OFST;
	extern const rectype_t NAME_OIAD;
	extern const rectype_t NAME_ONAM;
	extern const rectype_t NAME_PDTO;
	extern const rectype_t NAME_PFIG;
	extern const rectype_t NAME_PFO2;
	extern const rectype_t NAME_PFOR;
	extern const rectype_t NAME_PFPC;
	extern const rectype_t NAME_PHTN;
	extern const rectype_t NAME_PHWT;
	extern const rectype_t NAME_PIAD;
	extern const rectype_t NAME_PKC2;
	extern const rectype_t NAME_PKCU;
	extern const rectype_t NAME_PKDT;
	extern const rectype_t NAME_PKID;
	extern const rectype_t NAME_PLCN;
	extern const rectype_t NAME_PLDT;
	extern const rectype_t NAME_PLVD;
	extern const rectype_t NAME_PNAM;
	extern const rectype_t NAME_POBA;
	extern const rectype_t NAME_POCA;
	extern const rectype_t NAME_POEA;
	extern const rectype_t NAME_PRCB;
	extern const rectype_t NAME_PRKC;
	extern const rectype_t NAME_PRKE;
	extern const rectype_t NAME_PRKF;
	extern const rectype_t NAME_PRKR;
	extern const rectype_t NAME_PRKZ;
	extern const rectype_t NAME_PSDT;
	extern const rectype_t NAME_PTDA;
	extern const rectype_t NAME_QIAD;
	extern const rectype_t NAME_QNAM;
	extern const rectype_t NAME_QOBJ;
	extern const rectype_t NAME_QSDT;
	extern const rectype_t NAME_QSTA;
	extern const rectype_t NAME_QTGL;
	extern const rectype_t NAME_QUAL;
	extern const rectype_t NAME_RCLR;
	extern const rectype_t NAME_RDAT;
	extern const rectype_t NAME_RDMO;
	extern const rectype_t NAME_RDMP;
	extern const rectype_t NAME_RDOT;
	extern const rectype_t NAME_RDSA;
	extern const rectype_t NAME_RDWT;
	extern const rectype_t NAME_RIAD;
	extern const rectype_t NAME_RNAM;
	extern const rectype_t NAME_RNMV;
	extern const rectype_t NAME_RPLD;
	extern const rectype_t NAME_RPLI;
	extern const rectype_t NAME_RPRF;
	extern const rectype_t NAME_RPRM;
	extern const rectype_t NAME_SCDA;
	extern const rectype_t NAME_SCHR;
	extern const rectype_t NAME_SCRO;
	extern const rectype_t NAME_SCTX;
	extern const rectype_t NAME_SDSC;
	extern const rectype_t NAME_SHRT;
	extern const rectype_t NAME_SIAD;
	extern const rectype_t NAME_SLCP;
	extern const rectype_t NAME_SNAM;
	extern const rectype_t NAME_SNDD;
	extern const rectype_t NAME_SNMV;
	extern const rectype_t NAME_SOFT;
	extern const rectype_t NAME_SOUL;
	extern const rectype_t NAME_SPCT;
	extern const rectype_t NAME_SPED;
	extern const rectype_t NAME_SPIT;
	extern const rectype_t NAME_SPLO;
	extern const rectype_t NAME_SPOR;
	extern const rectype_t NAME_STOL;
	extern const rectype_t NAME_SWMV;
	extern const rectype_t NAME_TCLT;
	extern const rectype_t NAME_TIAD;
	extern const rectype_t NAME_TIAS;
	extern const rectype_t NAME_TIFC;
	extern const rectype_t NAME_TINC;
	extern const rectype_t NAME_TIND;
	extern const rectype_t NAME_TINI;
	extern const rectype_t NAME_TINL;
	extern const rectype_t NAME_TINP;
	extern const rectype_t NAME_TINT;
	extern const rectype_t NAME_TINV;
	extern const rectype_t NAME_TIRS;
	extern const rectype_t NAME_TNAM;
	extern const rectype_t NAME_TPIC;
	extern const rectype_t NAME_TPLT;
	extern const rectype_t NAME_TRDT;
	extern const rectype_t NAME_TVDT;
	extern const rectype_t NAME_TWAT;
	extern const rectype_t NAME_TX00;
	extern const rectype_t NAME_TX01;
	extern const rectype_t NAME_TX02;
	extern const rectype_t NAME_TX03;
	extern const rectype_t NAME_TX04;
	extern const rectype_t NAME_TX05;
	extern const rectype_t NAME_TX07;
	extern const rectype_t NAME_UNAM;
	extern const rectype_t NAME_UNES;
	extern const rectype_t NAME_VCLR;
	extern const rectype_t NAME_VENC;
	extern const rectype_t NAME_VEND;
	extern const rectype_t NAME_VENV;
	extern const rectype_t NAME_VHGT;
	extern const rectype_t NAME_VMAD;
	extern const rectype_t NAME_VNAM;
	extern const rectype_t NAME_VNML;
	extern const rectype_t NAME_VTCK;
	extern const rectype_t NAME_VTXT;
	extern const rectype_t NAME_WAIT;
	extern const rectype_t NAME_WAM2;
	extern const rectype_t NAME_WBDT;
	extern const rectype_t NAME_WCTR;
	extern const rectype_t NAME_WGEN;
	extern const rectype_t NAME_WKMV;
	extern const rectype_t NAME_WLST;
	extern const rectype_t NAME_WNAM;
	extern const rectype_t NAME_XACT;
	extern const rectype_t NAME_XALP;
	extern const rectype_t NAME_XAPD;
	extern const rectype_t NAME_XAPR;
	extern const rectype_t NAME_XCAS;
	extern const rectype_t NAME_XCCM;
	extern const rectype_t NAME_XCIM;
	extern const rectype_t NAME_XCLC;
	extern const rectype_t NAME_XCLL;
	extern const rectype_t NAME_XCLR;
	extern const rectype_t NAME_XCLW;
	extern const rectype_t NAME_XCMO;
	extern const rectype_t NAME_XCNT;
	extern const rectype_t NAME_XCVL;
	extern const rectype_t NAME_XCWT;
	extern const rectype_t NAME_XCZA;
	extern const rectype_t NAME_XCZC;
	extern const rectype_t NAME_XEMI;
	extern const rectype_t NAME_XESP;
	extern const rectype_t NAME_XEZN;
	extern const rectype_t NAME_XFVC;
	extern const rectype_t NAME_XHOR;
	extern const rectype_t NAME_XHTW;
	extern const rectype_t NAME_XILL;
	extern const rectype_t NAME_XIS2;
	extern const rectype_t NAME_XLCM;
	extern const rectype_t NAME_XLCN;
	extern const rectype_t NAME_XLIB;
	extern const rectype_t NAME_XLIG;
	extern const rectype_t NAME_XLKR;
	extern const rectype_t NAME_XLOC;
	extern const rectype_t NAME_XLRM;
	extern const rectype_t NAME_XLRT;
	extern const rectype_t NAME_XLTW;
	extern const rectype_t NAME_XMBO;
	extern const rectype_t NAME_XMBP;
	extern const rectype_t NAME_XMBR;
	extern const rectype_t NAME_XMRK;
	extern const rectype_t NAME_XNAM;
	extern const rectype_t NAME_XNDP;
	extern const rectype_t NAME_XOCP;
	extern const rectype_t NAME_XOWN;
	extern const rectype_t NAME_XPOD;
	extern const rectype_t NAME_XPPA;
	extern const rectype_t NAME_XPRD;
	extern const rectype_t NAME_XPRM;
	extern const rectype_t NAME_XPWR;
	extern const rectype_t NAME_XRDS;
	extern const rectype_t NAME_XRGB;
	extern const rectype_t NAME_XRGD;
	extern const rectype_t NAME_XRMR;
	extern const rectype_t NAME_XRNK;
	extern const rectype_t NAME_XSCL;
	extern const rectype_t NAME_XSPC;
	extern const rectype_t NAME_XTEL;
	extern const rectype_t NAME_XTNM;
	extern const rectype_t NAME_XTRI;
	extern const rectype_t NAME_XWCN;
	extern const rectype_t NAME_XWCS;
	extern const rectype_t NAME_XWCU;
	extern const rectype_t NAME_XWEM;
	extern const rectype_t NAME_XXXX;
	extern const rectype_t NAME_YNAM;
	extern const rectype_t NAME_ZNAM;

	/* Custom names for internal use */
	extern const rectype_t NAME_psec;		/* Perk section */
	extern const rectype_t NAME_pssc;		/* Perk subsection */



		/* Comparison operators */
	inline bool operator== (const rectype_t Name, const char* pString) { return (Name.Value == *(dword *)pString); }
	inline bool operator== (const rectype_t Name, const dword Value) { return (Name.Value == Value); }
	inline bool operator== (const rectype_t Name1, const rectype_t Name2) { return (Name1.Value == Name2.Value); }
	inline bool operator!= (const rectype_t Name, const char* pString) { return (Name.Value != *(dword *)pString); }
	inline bool operator!= (const rectype_t Name, const dword Value) { return (Name.Value != Value); }
	inline bool operator!= (const rectype_t Name1, const rectype_t Name2) { return (Name1.Value != Name2.Value); }

	/* Read/write functions */
	bool ReadRecType(CFile& File, rectype_t& Name);
	bool WriteRecType(CFile& File, const rectype_t Name);

	
}

template <>
struct std::hash<sfwiki::rectype_t>
{
	std::size_t operator()(const sfwiki::rectype_t& k) const
	{
		return (k.Value);
	}
};
#endif

