#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include "structs.h"
#include "random_order_generator.h"


std::ostream& operator<< (std::ostream& out, const AUSK& s) {
	return out <<"AUSK: AusNr:" << s.AusNr << "\n";
}
std::ostream& operator<< (std::ostream& out, const AUSP& s) {
	return out <<"\tAUSP: AusNr:" << s.AusNr << "/" << s.PosNr << "\n"  ;	
};
std::ostream& operator<< (std::ostream& out, const VPLP& s) {
	return out <<"\t\tVPLP: VplNr: " << s.VplNr << "AUSP:" << s.AUSP_AusNr 
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
int main()
{
	std::vector<OrderData> orderData;
	fillOrderData(orderData);
	PrintOrderDataVector(orderData);
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
