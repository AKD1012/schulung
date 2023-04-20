#pragma once
#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <initializer_list>
#include <string>
#include <iostream>

struct AUSK {
	std::string AusNr;

	bool operator==(const AUSK& other) const{
		return AusNr == other.AusNr;
	}
	AUSK& operator=(const AUSK& other) {
		AusNr = other.AusNr;
		return *this;
	}
	AUSK (const AUSK& other) : 
		AusNr(other.AusNr){}

	AUSK () : AusNr("") {}

	AUSK (const std::string &s) : 
		AusNr(s) {};
	bool operator<(const AUSK& other) const {
		return AusNr < other.AusNr;
	}
	~AUSK () {};
};
struct AUSP {
	std::string AusNr;
	long PosNr;

	bool operator==(const AUSP& other) const{
		return AusNr == other.AusNr && PosNr == other.PosNr;
	}
	AUSP& operator=(const AUSP& other) {
		AusNr = other.AusNr;
		PosNr = other.PosNr;
		return *this;
	}
	AUSP (const AUSP& other) : 
		AusNr(other.AusNr),
		PosNr(other.PosNr) {}

	AUSP () : 
		AusNr(""), 
		PosNr() {};

	AUSP (const std::string&s, long l) : 
		AusNr(s), 
		PosNr(l) {};

	bool operator<(const AUSP& other) const {
		if (AusNr != other.AusNr) {
			return AusNr < other.AusNr;
		}
		return PosNr < other.PosNr;
	}
	~AUSP () {};

};

struct VPLP {
	long VplNr;
	std::string AUSP_AusNr;
	long AUSP_PosNr;
	long VPLK_KsNr;

	bool operator==(const VPLP& other) const{
		return VplNr == other.VplNr;
	}

	VPLP& operator=(const VPLP& other) {
		VplNr = other.VplNr;
		AUSP_AusNr = other.AUSP_AusNr;
		AUSP_PosNr = other.AUSP_PosNr;
		VPLK_KsNr = other.VPLK_KsNr;
		return *this;
	}
	VPLP (const VPLP& other) : 
		VplNr(other.VplNr),
		AUSP_AusNr(other.AUSP_AusNr),
		AUSP_PosNr(other.AUSP_PosNr),
		VPLK_KsNr(other.VPLK_KsNr)	{}

	VPLP() : 
		VplNr(0), 
		AUSP_AusNr(""), 
		AUSP_PosNr(0),
		VPLK_KsNr(0) {}
	VPLP(long vplnr, const std::string &s, long posnr, long ksnr) : 
		VplNr(vplnr),
		AUSP_AusNr(s),
		AUSP_PosNr(posnr),
		VPLK_KsNr(ksnr) {}
	
	bool operator<(const VPLP &other) const {
		return VplNr < other.VplNr;
	}
	~VPLP () {};

};


struct VPLK {
	long KsNr;

	bool operator==(const VPLK& other) const{
		return KsNr == other.KsNr;
	}
	VPLK& operator=(const VPLK& other) {
		KsNr = other.KsNr;
		return *this;
	}
	VPLK (const VPLK& other) : 
		KsNr(other.KsNr){}

	VPLK () : KsNr(0) {}

	VPLK (long lksnr) : KsNr(lksnr) {};

	bool operator<(const VPLK& other) const{
		return KsNr < other.KsNr;
	}
	~VPLK() {}
};

struct VPLG {
	long VplNr;
	std::string AUSP_AusNr;
	long AUSP_PosNr;

	bool operator==(const VPLG& other) const{
		return VplNr == other.VplNr;
	}
	VPLG& operator=(const VPLG& other) {
		VplNr = other.VplNr;
		AUSP_PosNr = other.AUSP_PosNr;
		AUSP_AusNr = other.AUSP_AusNr;
		return *this;
	}
	VPLG (const VPLG& other) : 
		VplNr(other.VplNr),
		AUSP_AusNr(other.AUSP_AusNr),
		AUSP_PosNr(other.AUSP_PosNr){}

	VPLG(long vplnr, const std::string &s, long posnr) : 
		VplNr(vplnr),
		AUSP_AusNr(s),
		AUSP_PosNr(posnr) {}

	VPLG() : 
		VplNr(0), 
		AUSP_AusNr(""), 
		AUSP_PosNr(0) {}

	bool operator<(const VPLG& other) const {
		return VplNr < other.VplNr;
	}
	~VPLG() {}
};

struct OrderData {
	AUSK tAusk;
	AUSP tAusp;
	VPLP tVplp;
	VPLK tVplk;
	VPLG tVplg;
};

#endif
