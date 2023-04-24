#include <random>
#include <algorithm>
#include <iterator>
#include "random_order_generator.h"
#include "generate_randomstring.h"

std::vector<OrderData> fillOrderDataWithGenerator(OrderDataGenerator &generator) {
	std::vector<OrderData> orderdata;
	std::vector<AUSK> ausks = generator.getAllAusks();
	for (AUSK &ausk : ausks) {
		std::vector<AUSP> ausps = generator.getAllAuspsForAusNr(ausk.AusNr);
		for (AUSP &ausp : ausps) {
			std::vector<VPLG> vplgs = generator.getAllVplgsForAusp(ausp);
			for (VPLG &vplg : vplgs) {
				orderdata.push_back({ausk, ausp, {}, {}, vplg});
			}
			std::vector<VPLP> vplps = generator.getAllVplpsForAusp(ausp);
			for (VPLP &vplp : vplps) {
				orderdata.push_back({ausk, ausp, vplp, {vplp.VPLK_KsNr}, {}});
			}
		}
	}
	return orderdata;
}

std::vector<OrderData> generateRandomOrderData()
{
	OrderDataGenerator generator {};
	generator.generateOrderData();
	return fillOrderDataWithGenerator(generator);
}

void OrderDataGenerator::generateOrderData()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(5, 20);
	int random_num = distr(eng);
	seqVplNr = 1;
	seqKsNr = 1;
	for (int i = 0; i < random_num; ++i) {
		currentAusNr = "AUSNR-";
		currentAusNr += randomStrGen(10);
		ausks.insert({currentAusNr});
		std::uniform_int_distribution<int> distrAUSP(1, 40);
		int anzAusps = distrAUSP(eng);
		generateAUSPsWithVPLData(anzAusps);
	}
}

void OrderDataGenerator::generateAUSPsWithVPLData(int anzAusps) 
{
	seqAUSP_PosNr = 1;
	if (vplks.find({seqKsNr}) != vplks.end()) {
		seqKsNr++;
	}
	for (int i = 0; i < anzAusps; ++i) {
		ausps.insert({currentAusNr, seqAUSP_PosNr});
		std::random_device rd;
		std::default_random_engine eng(rd());
		std::uniform_int_distribution<int> distr(1, 10);
		int anzVpl = distr(eng);
		for (int j = 0; j < anzVpl; ++j) {
			std::uniform_int_distribution<int> distrBool(0,1);
			bool bVplp = static_cast<bool>(distrBool(eng));
			if (bVplp) {
				bool bFillKsNr = static_cast<bool>(distrBool(eng));
				if (bFillKsNr) {
					vplks.insert({seqKsNr});
					vplps.insert({seqVplNr, currentAusNr, seqAUSP_PosNr, seqKsNr});
					bool bIncrementKsNr = static_cast<bool>(distrBool(eng));
					if (bIncrementKsNr)
						seqKsNr++;
				} else {
					vplps.insert({seqVplNr, currentAusNr, seqAUSP_PosNr, 0});
				}
			} else {
				vplgs.insert({seqVplNr, currentAusNr, seqAUSP_PosNr});
			}
			seqVplNr++;
		}
		seqAUSP_PosNr++;
	}
}

std::vector<AUSK> OrderDataGenerator::getAllAusks()
{
	std::vector<AUSK> ausks(std::begin(this->ausks), std::end(this->ausks));
	return ausks;
}

std::vector<AUSP> OrderDataGenerator::getAllAuspsForAusNr(const std::string &AusNr)
{
	std::vector<AUSP> ausps;
	std::copy_if(std::begin(this->ausps), std::end(this->ausps), 
			std::back_inserter(ausps), [&](const AUSP &ausp){
				return ausp.AusNr == AusNr;
			});
	return ausps;
}

std::vector<VPLP> OrderDataGenerator::getAllVplpsForAusp(const AUSP &ausp)
{
	std::vector<VPLP> vplps;
	std::copy_if(std::begin(this->vplps), std::end(this->vplps), 
			std::back_inserter(vplps), [&](const VPLP &vplp){
				return vplp.AUSP_AusNr == ausp.AusNr && vplp.AUSP_PosNr == ausp.PosNr;
			});
	return vplps;
}

std::vector<VPLG> OrderDataGenerator::getAllVplgsForAusp(const AUSP &ausp)
{
	std::vector<VPLG> vplgs;
	std::copy_if(std::begin(this->vplgs), std::end(this->vplgs), 
			std::back_inserter(vplgs), [&](const VPLG &vplg){
				return vplg.AUSP_AusNr == ausp.AusNr && vplg.AUSP_PosNr == ausp.PosNr;
			});
	return vplgs;
}

