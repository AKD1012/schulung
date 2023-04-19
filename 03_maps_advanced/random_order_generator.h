#pragma once
#ifndef _RANDOM_ORDER_GENERATOR_H_
#define _RANDOM_ORDER_GENERATOR_H_

#include <map>
#include <vector>
#include <unordered_set>
#include <set>
#include "structs.h"

namespace std {
	template<>
	struct hash<AUSK> {
		size_t operator()(const AUSK& a) const {
			return std::hash<std::string>()(a.AusNr);
		}
	};
	template<>
	struct hash<AUSP> {
		size_t operator()(const AUSP& a) const {
			size_t h1 = std::hash<std::string>()(a.AusNr);
			size_t h2 = std::hash<long>()(a.PosNr);
			return h1 ^ (h2 << 1);  // combine the hash values
		}
	};
	template<>
	struct hash<VPLP> {
		size_t operator()(const VPLP& v) const {
			return std::hash<long>()(v.VplNr);
		}
	};
	template<>
	struct hash<VPLG> {
		size_t operator()(const VPLG& v) const {
			return std::hash<long>()(v.VplNr);
		}
	};
	template<>
	struct hash<VPLK> {
		size_t operator()(const VPLK& v) const {
			return std::hash<long>()(v.KsNr);
		}
	};
}

struct OrderDataGenerator {
	
	void generateOrderData();
	std::vector<AUSK> getAllAusks();
	std::vector<AUSP> getAllAuspsForAusNr(const std::string &AusNr);
	std::vector<VPLP> getAllVplpsForAusp(const AUSP &ausp);
	std::vector<VPLG> getAllVplgsForAusp(const AUSP &ausp);
	std::vector<VPLK> getVplkForKsNr(const long ksnr);
private:
	void generateAUSPsWithVPLData(int anzAusps);
	void generateVPLPDataForAusp(const AUSP &ausp);
	std::unordered_set<AUSK, std::hash<AUSK>> ausks;
	std::unordered_set<AUSP, std::hash<AUSP>> ausps;
	std::unordered_set<VPLP, std::hash<VPLP>> vplps;
	std::unordered_set<VPLK, std::hash<VPLK>> vplks;
	std::unordered_set<VPLG, std::hash<VPLG>> vplgs;
	std::string currentAusNr;
	long seqAUSP_PosNr;
	long seqVplNr;
	long seqKsNr;
};

std::vector<OrderData> generateRandomOrderData();

#endif
