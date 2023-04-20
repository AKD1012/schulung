#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <variant>
#include "structs.h"
#include "random_order_generator.h"

using VplDataSet = std::set<std::variant<std::map<VPLK, std::set<VPLP>>, std::set<VPLG>>>;
using OrderDataMap = std::map<AUSK, std::map <AUSP, VplDataSet>>;

std::ostream& operator<< (std::ostream& out, const AUSK& s) {
	return out <<"AUSK: AusNr: [" << s.AusNr << "]\n";
}
std::ostream& operator<< (std::ostream& out, const AUSP& s) {
	return out <<"\tAUSP: AusNr [:" << s.AusNr << "/" << s.PosNr << "]\n"  ;	
};
std::ostream& operator<< (std::ostream& out, const VPLK& s) {
	if (s.KsNr == 0) {
		return out;
	}
	return out <<"\t\tVPLK: KsNr: ["<< s.KsNr << "]\n";
}
std::ostream& operator<< (std::ostream& out, const VPLP& s) {
	if (s.VPLK_KsNr == 0) {
		return out <<"\t\tVPLP: VplNr: [" << s.VplNr << "] AUSP: [" << s.AUSP_AusNr 
				<< "/" << s.AUSP_PosNr << "] KsNr: [" << s.VPLK_KsNr << "]\n";
	} 
	return out <<"\t\t\tVPLP: VplNr: [" << s.VplNr << "] AUSP: [" << s.AUSP_AusNr 
			<< "/" << s.AUSP_PosNr << "] KsNr: [" << s.VPLK_KsNr << "]\n";
}
std::ostream& operator<< (std::ostream& out, const VPLG& s) {
	return out <<"\t\tVPLG: VplNr: [" << s.VplNr << "] AUSP: [" << s.AUSP_AusNr 
			<< "/" << s.AUSP_PosNr << "]\n" ;
}
std::ostream& operator<< (std::ostream& out, const OrderData& o) {
	return out << o.tAusk << o.tAusp << o.tVplp << o.tVplg;
}

std::ostream& operator<< (std::ostream& out, const OrderDataMap& o) {
	// Split first Level using structured bindings and loop over Data 
	for (auto [ausk,auspdata] : o) { // ausk has Type AUSK, auspdata has Type std::map <AUSP, VplDataSet>
		// Add ausk to stream
		out << ausk;
		// Split std::map<AUSP, VplDataSet> and loop over Data
		for (auto [ausp, vpldataset] : auspdata) {
			// Add ausp to stram
			out << ausp;
			// print VPLKs and VPLPs first
			// loop over vpldataset
			for (auto vpldata : vpldataset) {
				// check if our std::variant-entry has type std::map<VPLK, std::set<VPLP>> 
				auto *pMap = std::get_if<std::map<VPLK, std::set<VPLP>>>(&vpldata);
				if (pMap != NULL) {
					// split std::map<VPLK, std::set<VPLP> and loop over Data
					for (auto [vplk, vplps] : *pMap) {
						// Add vplk to stream
						out << vplk;
						// loop over vplps
						for (auto vplp : vplps) {
							// Add vplp to stream
							out << vplp;
						}
					}
				}
			}
			// print VPLGs afterwards
			for (auto vpldata : vpldataset) {
				// check if our std::varaint-entry has type std::set<VPLG>
				auto *pSet = std::get_if<std::set<VPLG>>(&vpldata);
				if (pSet != NULL) {
					// loop over vplgs
					for (auto vplg : *pSet) {
						// Add vplg to stream
						out << vplg;
					}
				}

			}
		}
	}
	return out;
}

void fillOrderData(std::vector<OrderData> &orderData) 
{
	orderData = generateRandomOrderData();
}

void PrintOrderDataVector(const std::vector<OrderData> &orderData)
{
	std::copy(orderData.begin(), orderData.end(), std::ostream_iterator<OrderData>(std::cout, "\n"));
}

	
int main()
{
	std::vector<OrderData> orderData;
	fillOrderData(orderData);
	PrintOrderDataVector(orderData);
	OrderDataMap o {};
	std::set<AUSK> setAusk;
	std::set<AUSP> setAusp;
	std::map<AUSP, std::set<VPLP>> mAuspVplp;
	std::map<AUSP, std::set<VPLG>> mAuspVplg;
	std::set<VPLK> setVplk;

	// split Data into several helper containers
	for (auto &rec : orderData) {
		// make Ausk, Ausp and Vplk data unique by inserting them into std::set
		setAusk.insert(rec.tAusk);
		setAusp.insert(rec.tAusp);
		setVplk.insert(rec.tVplk);
		
		// check if VPLP or VPLG
		if (rec.tVplp.VplNr > 0) {
			// check if there is already an existing entry for our AUSP in map<AUSP, std::set<VPLP>>
			if(mAuspVplp.find(rec.tAusp) == mAuspVplp.end()) {
				// no entry exists --> create a new one
				mAuspVplp[rec.tAusp] = {rec.tVplp};
			} else {
				// entry exists --> insert VPLP
				mAuspVplp[rec.tAusp].insert(rec.tVplp);
			}
		} else { 
			// check if there is already an existing entry for our AUSP in map<AUSP, std::set<VPLG>>
			if(mAuspVplg.find(rec.tAusp) == mAuspVplg.end()) {
				// no entry exists --> create a new one
				mAuspVplg[rec.tAusp] = {rec.tVplg};
			} else {
				// entry exists --> insert VPLG
				mAuspVplg[rec.tAusp].insert(rec.tVplg);
			}
		}
	}
	// Build OrderDataMap
	for (auto &ausk : setAusk) {
		for (auto &ausp :setAusp) {
			// AUSK.AusNr and AUSP.AusNr must equal in Map
			if (ausk.AusNr != ausp.AusNr) {
				continue;
			}
			VplDataSet vplData;
			// check if there are VPLPs for our AUSP using std::map<AUSP, std::set<VPLP>>
			auto itVplp = mAuspVplp.find(ausp);
			if (itVplp != mAuspVplp.end()) {
				// AUSP has linked VPLPs --> Build VplkVplp-Map
				std::map<VPLK, std::set<VPLP>> mVplkVplp;
				// loop through all VPLPs for our AUSP
				for (auto &vplp : itVplp->second) {
					// check if KsNr is valid (VPLK-Set has to have an entry for VPLP's KsNr)
					auto itVplk = setVplk.find({vplp.VPLK_KsNr});
					if (itVplk != setVplk.end()) {
						// check if there is an existing entry for our VPLK in our std::map<VPLK, std::set<VPLP>>
						if (mVplkVplp.count(*itVplk) > 0) {
							// entry exists --> insert VPLP
							mVplkVplp[*itVplk].insert(vplp);
						} else {
							// no entry exists --> create a new one
							mVplkVplp[*itVplk] = {vplp};
						}
					}
				}
				// insert map into vplDataSet
				vplData.insert(mVplkVplp);
			}
			// check if VPLGs exists for our AUSP
			auto itVplg = mAuspVplg.find(ausp);
			if (itVplg != mAuspVplg.end()) {
				// VPLGs exists --> insert the set from std::map<AUSP, std::set<VPLG>> ito vplDataSet
				vplData.insert(mAuspVplg[ausp]);
			}
			// create OrderDataMap-Entry for our current workingData
			o[ausk][ausp] = vplData;
		}
	}
	// print OrderDataMap using overloaded ostream-operator
	std::cout << o ;

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
