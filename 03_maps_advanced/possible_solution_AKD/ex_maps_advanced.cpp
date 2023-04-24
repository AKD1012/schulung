#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "structs.h"
#include "random_order_generator.h"
#include "ex_maps_advanced.h"
#include <algorithm>


std::ostream& operator<< (std::ostream& out, const AUSK& s) {
	return out <<"AUSK: AusNr:" << s.AusNr << "\n";
}
std::ostream& operator<< (std::ostream& out, const AUSP& s) {
	return out <<"\tAUSP: AusNr:" << s.AusNr << "/" << s.PosNr << "\n"  ;	
}
std::ostream& operator<< (std::ostream& out, const VPLK& s) {
	return out <<"\t\tVPLK: KsNr: " << s.KsNr << "\n";
}
std::ostream& operator<< (std::ostream& out, const VPLP& s) {
	return out <<"\t\t\tVPLP: VplNr: " << s.VplNr << "AUSP:" << s.AUSP_AusNr 
			<< "/" << s.AUSP_PosNr << " KsNr:" << s.VPLK_KsNr << "\n";
}
std::ostream& operator<< (std::ostream& out, const VPLG& s) {
	return out <<"\t\tVPLG: VplNr: " << s.VplNr << "AUSP:" << s.AUSP_AusNr 
			<< "/" << s.AUSP_PosNr << "\n" ;
}
std::ostream& operator<< (std::ostream& out, const OrderData& o) {
	return out << o.tAusk << o.tAusp << o.tVplp << o.tVplg;
}

void fillOrderData(std::vector<OrderData> &orderData) 
{
	orderData = generateRandomOrderData();
}

void PrintOrderDataVector(const std::vector<OrderData> &orderData)
{
	std::copy(orderData.begin(), orderData.end(), std::ostream_iterator<OrderData>(std::cout, "\n"));
}

VplDataSet::VplDataSet()
{
	std::map<VPLK, std::vector<VPLP>> mVpl;
	this->vplData_.push_back(mVpl);

	std::vector<VPLG> vplgs;
	this->vplData_.push_back(vplgs);
}

void VplDataSet::printData()
{
	for (auto data : this->vplData_) {
		if (std::holds_alternative<std::map<VPLK, std::vector<VPLP>>>(data)) {
			auto mVpl = std::get<std::map<VPLK, std::vector<VPLP>>>(data);
			for (auto [vplk, vecVplp] : mVpl) {
				std::cout << vplk;
				for (auto vplp : vecVplp) {
					std::cout << vplp;
				}
			}
			continue;
		}

		auto vecVplg = std::get<std::vector<VPLG>>(data);
		for (auto vplg : vecVplg) {
			std::cout << vplg;
		}
	}
}

void VplDataSet::setData(std::variant<std::pair<VPLK, VPLP>, VPLG> vplData)
{
	if(std::holds_alternative<VPLG>(vplData)) {
		auto vplg = std::get<VPLG>(vplData);
		for (auto &data : this->vplData_) {
			auto *vplgVec = std::get_if<std::vector<VPLG>>(&data);
			if (vplgVec != NULL) {

				vplgVec->push_back(vplg);
			}
		}
	} else {
		auto vplPair = std::get<std::pair<VPLK, VPLP>>(vplData);
		std::map<VPLK, std::vector<VPLP>> vplkMap;
		
		for (auto &data : this->vplData_) {
			auto *vplMap = std::get_if<std::map<VPLK, std::vector<VPLP>>>(&data);
			if (vplMap != NULL) { 
				auto it = vplMap->find(vplPair.first);
				if (it != vplMap->end()) {
					it->second.push_back(vplPair.second);
				} else {
					vplMap->insert(std::pair<VPLK, std::vector<VPLP>>(vplPair.first, {vplPair.second}));
				}
			}
		}
	}
}

void OrderDataSet::printData()
{
	for (auto [ausk, mapAusp] : this->orderData_) {
		std::cout << ausk;

		for (auto [ausp, vplData] : mapAusp) {
			std::cout << ausp;
			vplData.printData();
		}
	}
}

void OrderDataSet::fillDataSet(std::vector<OrderData> orderData)
{
	std::set<AUSK> ausks;
	std::set<AUSP> ausps;
	std::map<VPLK, std::vector<VPLP>> mVpl;
	std::set<VPLK> vplks;
	std::set<VPLG> vplgs;
	std::map<AUSP, std::vector<std::variant<VPLP, VPLG>>> mVplMapping;

	std::vector<VplDataSet> vplData;

	for (auto &o : orderData) {
		ausks.insert(o.tAusk);
		ausps.insert(o.tAusp);

		if (o.tVplp.VplNr > 0) {
			if(o.tVplk.KsNr > 0) {
				vplks.insert(o.tVplk);
			}
			
			if (mVplMapping.find(o.tAusp) == mVplMapping.end()) {
				mVplMapping[o.tAusp] = {o.tVplp};
			} else {
				mVplMapping[o.tAusp].push_back(o.tVplp);
			}

		} else { 
			vplgs.insert(o.tVplg);
			if (mVplMapping.find(o.tAusp) == mVplMapping.end()) {
				mVplMapping[o.tAusp] = {o.tVplg};
			} else {
				mVplMapping[o.tAusp].push_back(o.tVplg);
			}
		}
	}

	for (auto &ausk : ausks) {
		std::map<AUSP, VplDataSet> mPosData;

		for (auto &ausp : ausps)  {
			if (ausp.AusNr != ausk.AusNr) {
				continue;
			}
			VplDataSet vSet;
			for (auto VplData : mVplMapping[ausp]) {
				if (std::holds_alternative<VPLP>(VplData)) {
					auto vplp = std::get<VPLP>(VplData);			
					VPLK vplk = {};
					vplk.KsNr = vplp.VPLK_KsNr;
					auto rec = vplks.find(vplk);
					
					if (rec != vplks.end()) {
						vplk = *rec;
					}

					vSet.setData(std::pair<VPLK,VPLP>(vplk, vplp));
				} else {
					auto vplg = std::get<VPLG>(VplData);
					vSet.setData(vplg);
				}
			}

			mPosData[ausp] = vSet;
		}

		this->orderData_[ausk] = mPosData;
	}
}

int main()
{
	std::vector<OrderData> orderData;
	fillOrderData(orderData);
	PrintOrderDataVector(orderData);

	OrderDataSet orderset;
	VplDataSet vplsets;

	orderset.fillDataSet(orderData);
	orderset.printData();
 
	
	//the implemented function fillOrderData fills the std::vector orderData with random Data
	// currently we have a dataset, like we have read it from DB with a single Select-Stmt 
	// definitions of structs can be found in structs.h
	//@ToDo: Make a custom Struct to  have one single variable for one order-dataset (1AUSK, xAUSPs, xVPLKs, xVPLPs, xVPLGs)
	// hint: you need to nest std::map 
	// afterwards make your own Print-Function to print your orders.
	// Output should look like this:
	// 	AUSK: AusNr: AUSID-xxxx
	// 		AUSP: AusNr: AUSID-xxxx PosNr: x
	//			VPLK: KsNr: x
	//				VPLP: VplNr: x AusNr: AUSID-xxxxx PosNr: x KsNr: x
	//				VPLP: VplNr: x AusNr: AUSID-xxxxx PosNr: x KsNr: x
	//				VPLP: VplNr: x AusNr: AUSID-xxxxx PosNr: x KsNr: x
	//			VPLK: KsNr: x
	//				VPLP: VplNr: x AusNr: AUSID-xxxxx PosNr: x KsNr: x
	//				VPLP: VplNr: x AusNr: AUSID-xxxxx PosNr: x KsNr: x
	//			VPLG: VplNr: x AusNr: AUSID-xxxxx PosNr: x
	//			VPLG: VplNr: x AusNr: AUSID-xxxxx PosNr: x
	// 		AUSP: AusNr: AUSID-xxxx PosNr: x
	//			VPLK: KsNr: x
	//				VPLP: VplNr: x AusNr: AUSID-xxxxx PosNr: x KsNr: x
	//			VPLK: KsNr: x
	//				VPLP: VplNr: x AusNr: AUSID-xxxxx PosNr: x KsNr: x
	//				VPLP: VplNr: x AusNr: AUSID-xxxxx PosNr: x KsNr: x
	//			VPLG: VplNr: x AusNr: AUSID-xxxxx PosNr: x
	// -----------------------------------------------------------------
	// 	AUSK: AusNr: AUSID-xxxx
	// 		AUSP: AusNr: AUSID-xxxx PosNr: x
	// ...

	std::cin.get();
	return 0;
}
